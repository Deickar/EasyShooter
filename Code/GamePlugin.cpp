#include "StdAfx.h"
#include "GamePlugin.h"
#include "UI/UIManager.h"
#include "UI/Menu/PageLoading.h"

#include <CryCore/Platform/platform_impl.inl>

IEntityRegistrator *IEntityRegistrator::g_pFirst = nullptr;
IEntityRegistrator *IEntityRegistrator::g_pLast = nullptr;

CGamePlugin::~CGamePlugin()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);

	IEntityRegistrator* pTemp = IEntityRegistrator::g_pFirst;
	while (pTemp != nullptr)
	{
		pTemp->Unregister();
		pTemp = pTemp->m_pNext;
	}
}

bool CGamePlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this);

	return true;
}

void CGamePlugin::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{
	case ESYSTEM_EVENT_GAME_POST_INIT:
	{
		// Register entities
		IEntityRegistrator* pTemp = IEntityRegistrator::g_pFirst;
		while (pTemp != nullptr)
		{
			pTemp->Register();
			pTemp = pTemp->m_pNext;
		}

		if (gEnv->pFireNet)
		{
			gEnv->pFireNet->RegisterFireNetListener(this);
			gEnv->pFireNet->ConnectToMasterServer("127.0.0.1", 3322);
		}

		break;
	}
	case ESYSTEM_EVENT_GAME_FRAMEWORK_INIT_DONE:
	{
		if (!gEnv->IsDedicated())
		{
			// Load UI Manager
			pEnv->pUIManager = new CUIManager();				
		}

		break;
	}

	// Show loading page on level loading and unload page when level loaded
	case ESYSTEM_EVENT_LEVEL_LOAD_START_LOADINGSCREEN:
	{
		if (!gEnv->IsEditor() && !gEnv->IsDedicated())
		{
			pEnv->pUIManager->pPageLoading->SetLoadingText("@ui_level_loading");
			pEnv->pUIManager->LoadPage("LoadingPage");
		}
		break;
	}

	case ESYSTEM_EVENT_LEVEL_GAMEPLAY_START:
	{
		if (!gEnv->IsEditor() && !gEnv->IsDedicated())
		{
			pEnv->pUIManager->UnloadPage("LoadingPage");
			pEnv->bInGame = true;
		}
		else if (!gEnv->IsDedicated())
		{
			// Load HUD
			pEnv->pUIManager->LoadPage("HUDPage");
		}
		break;
	}

	// Show loading page on level unloading and unload page when level unloaded
	case ESYSTEM_EVENT_LEVEL_UNLOAD :
	{
		if (!gEnv->IsEditor() && !gEnv->IsDedicated())
		{
			// Unload HUD
			pEnv->pUIManager->UnloadPage("HUDPage");
			// Load loading page
			pEnv->pUIManager->pPageLoading->SetLoadingText("@ui_level_unloading");
			pEnv->pUIManager->LoadPage("LoadingPage");
		}
		break;
	}
	case ESYSTEM_EVENT_LEVEL_POST_UNLOAD:
	{
		if (!gEnv->IsEditor() && !gEnv->IsDedicated())
		{
			pEnv->pUIManager->UnloadPage("LoadingPage");
			// Load main menu after level unload
			pEnv->pUIManager->LoadPage("MainPage");
			pEnv->bInGame = false;
		}
		break;
	}

	case ESYSTEM_EVENT_GAME_PAUSED:
	{
		if (!gEnv->IsDedicated())
		{
			// Hide HUD page
			pEnv->pUIManager->HidePage("HUDPage");
		}
		break;
	}
	case ESYSTEM_EVENT_GAME_RESUMED:
	{
		if (!gEnv->IsDedicated())
		{
			// Unhide HUD page
			pEnv->pUIManager->ShowPage("HUDPage");
		}
		break;
	}

	break;
	}
}

void CGamePlugin::OnFireNetEvent(EFireNetEvents event, SFireNetEventArgs& args)
{
	switch (event)
	{
	case FIRENET_EVENT_MASTER_SERVER_CONNECTED:
	{
		CryLog("[FireNet] OnEvent : Connected");
		break;
	}
	case FIRENET_EVENT_MASTER_SERVER_DISCONNECTED:
	{
		break;
	}
	default:
		break;
	}
}

CRYREGISTER_SINGLETON_CLASS(CGamePlugin)