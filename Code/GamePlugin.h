// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include <CrySystem/ICryPlugin.h>

#include <CryGame/IGameFramework.h>
#include <CryEntitySystem/IEntityClass.h>

#include <FireNet>

class CGamePlugin 
	: public ICryPlugin
	, public ISystemEventListener
	, public IFireNetListener
{
public:
	CRYINTERFACE_SIMPLE(ICryPlugin)
	CRYGENERATE_SINGLETONCLASS(CGamePlugin, "EasyShooter_Plugin", 0x8E1DC2F5933642E1, 0x8F42F40C965DCA8D)

	virtual ~CGamePlugin();

	// ICryPlugin
	virtual const char* GetName() const override { return "EasyShooter"; }
	virtual const char* GetCategory() const override { return "Game"; }
	virtual bool Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;
	virtual void OnPluginUpdate(EPluginUpdateType updateType) override {}
	// ~ICryPlugin

	// ISystemEventListener
	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
	// ~ISystemEventListener

	// IFireNetEventListener
	virtual void OnFireNetEvent(EFireNetEvents event, SFireNetEventArgs& args = SFireNetEventArgs());
	// ~IFireNetEventListener
private:
	bool        InitFireNet();
public:
	template<class T>
	struct CObjectCreator : public IGameObjectExtensionCreatorBase
	{
		IGameObjectExtension* Create(IEntity* pEntity)
		{
			return pEntity->CreateComponentClass<T>();
		}

		void GetGameObjectExtensionRMIData(void** ppRMI, size_t* nCount)
		{
			*ppRMI = nullptr;
			*nCount = 0;
		}
	};

	template<class T>
	static void RegisterEntityWithDefaultComponent(const char *name, const char* category = nullptr, const char* icon = nullptr, bool iconOnTop = false)
	{
		IEntityClassRegistry::SEntityClassDesc clsDesc;
		clsDesc.sName = name;

		clsDesc.editorClassInfo.sCategory = category;
		clsDesc.editorClassInfo.sIcon = icon;
		clsDesc.editorClassInfo.bIconOnTop = iconOnTop;

		static CObjectCreator<T> _creator;

		gEnv->pGameFramework->GetIGameObjectSystem()->RegisterExtension(name, &_creator, &clsDesc);
	}

	template<class T>
	static void RegisterEntityComponent(const char *name)
	{
		static CObjectCreator<T> _creator;

		gEnv->pGameFramework->GetIGameObjectSystem()->RegisterExtension(name, &_creator, nullptr);
		T::SetExtensionId(gEnv->pGameFramework->GetIGameObjectSystem()->GetID(name));
	}
};

struct IEntityRegistrator
{
	IEntityRegistrator()
	{
		if (g_pFirst == nullptr)
		{
			g_pFirst = this;
			g_pLast = this;
		}
		else
		{
			g_pLast->m_pNext = this;
			g_pLast = g_pLast->m_pNext;
		}
	}

	virtual void Register() = 0;
	virtual void Unregister() = 0;

public:
	IEntityRegistrator *m_pNext;

	static IEntityRegistrator *g_pFirst;
	static IEntityRegistrator *g_pLast;
};