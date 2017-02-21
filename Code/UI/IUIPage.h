// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "UI/UIManager.h"
#include <CrySystem/Scaleform/IFlashUI.h>

class IUIPage
{
public:
	IUIPage(const char* name, IUIElementEventListener* eventListener = nullptr) : pElement(nullptr)
		, pEventListener(eventListener)
	{
		this->m_Name = name;

		Init();
	}
public:
	virtual void Init()
	{
		CryLog("[UIPage] Init page (%s)", m_Name);

		if (gEnv->pFlashUI)
		{
			pElement = gEnv->pFlashUI->GetUIElement(m_Name);

			if (pElement)
			{
				if (pEventListener)
				{
					pElement->AddEventListener(pEventListener, "EventListener");
					CryLog("[UIPage] Success init page (%s)", m_Name);

					OnInitPage(true);
				}
				else
				{
					CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Page (%s) loaded, but event listener not register!", m_Name);

					OnInitPage(false);
				}
			}
			else
			{
				CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed init page (%s). UIElement not found", m_Name);

				OnInitPage(false);
			}
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed init page (UIPage). Flash not loaded", m_Name);

			OnInitPage(false);
		}
	}
	virtual void LoadPage()
	{
		CryLog("[UIPage] Loading page (%s)", m_Name);

		if (pElement && !gEnv->pSystem->IsQuitting())
		{
			pElement->SetVisible(true);

			OnLoadPage(true);
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed load page (%s). UIElement not found", m_Name);

			OnLoadPage(false);
		}
	}
	virtual void UnloadPage()
	{
		CryLog("[UIPage] Unloading page (%s)", m_Name);

		if (gEnv->pSystem->IsQuitting())
			return;

		if (pElement)
		{
			pElement->SetVisible(false);
			pElement->Unload();

			OnUnloadPage(true);
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed unload page (%s). UIElement not found", m_Name);

			OnUnloadPage(false);
		}
	}
	virtual void ShowPage()
	{
		CryLog("[UIPage] Show page (%s)", m_Name);

		if (pElement && !gEnv->pSystem->IsQuitting())
		{
			pElement->SetVisible(true);

			OnShowPage(true);
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed show page (%s). UIElement not found", m_Name);

			OnShowPage(false);
		}
	}
	virtual void HidePage()
	{
		CryLog("[UIPage] Hide page (%s)", m_Name);

		if (pElement && !gEnv->pSystem->IsQuitting())
		{
			pElement->SetVisible(false);

			OnHidePage(true);
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed hide page (%s). UIElement not found", m_Name);

			OnHidePage(false);
		}
	}
	virtual void ReloadPage()
	{
		CryLog("[UIPage] Reloading page (%s)", m_Name);

		if (pElement && !gEnv->pSystem->IsQuitting())
		{
			pElement->Reload(true);

			OnReloadPage(true);
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[UIPage] Failed reload page (%s). UIElement not found", m_Name);

			OnReloadPage(false);
		}
	}
public:
	virtual void OnInitPage(bool init) {}
	virtual void OnLoadPage(bool loaded) {}
	virtual void OnUnloadPage(bool unloaded) {}
	virtual void OnShowPage(bool show) {}
	virtual void OnHidePage(bool hide) {}
	virtual void OnReloadPage(bool reloaded) {}
public:
	virtual const char* GetName() { return this->m_Name; };
	virtual IUIElement* GetUIElement() { return this->pElement; };
private:
	const char* m_Name;
public:
	IUIElement* pElement;
	IUIElementEventListener* pEventListener;
};