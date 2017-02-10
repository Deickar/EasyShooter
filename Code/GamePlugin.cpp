// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

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

		break;
	}
	case ESYSTEM_EVENT_GAME_FRAMEWORK_INIT_DONE:
	{
		if (!gEnv->IsDedicated())
		{
			// Load UI Manager
			pEnv->pUIManager = new CUIManager();				
		}

		// Start connect to FireNet
		if (gEnv->pFireNet && gEnv->IsClient())
		{
			gEnv->pFireNet->pFireNetCore->RegisterFireNetListener(this);
			gEnv->pFireNet->pFireNetCore->ConnectToMasterServer();
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
	case FIRENET_EVENT_MASTER_SERVER_START_CONNECTION:
	{
		pEnv->pUIManager->pPageLoading->SetLoadingText("@connecting_to_master_server");
		pEnv->pUIManager->LoadPage("LoadingPage");
		break;
	}
	case FIRENET_EVENT_MASTER_SERVER_CONNECTED:
	{
		pEnv->pUIManager->UnloadPage("LoadingPage");
		pEnv->pUIManager->LoadPage("AuthorizationPage");
		break;
	}
	case FIRENET_EVENT_MASTER_SERVER_CONNECTION_ERROR:
	{
		pEnv->pUIManager->UnloadAll();
		pEnv->pUIManager->LoadPage("ErrorPage");

		int reason = args.GetInt();
		auto pElement = pEnv->pUIManager->GetUIElement("ErrorPage");

		if (pElement)
		{
			SUIArguments errorString;

			if (reason == 0)
				errorString.AddArgument("@ui_connection_timeout");
			else if (reason == 1)
				errorString.AddArgument("@ui_cant_spawn_network_thread");


			pElement->CallFunction("SetErrorText", errorString);
		}

		break;
	}
	case FIRENET_EVENT_MASTER_SERVER_DISCONNECTED:
	{
		pEnv->pUIManager->UnloadAll();
		pEnv->pUIManager->LoadPage("ErrorPage");

		auto pElement = pEnv->pUIManager->GetUIElement("ErrorPage");

		if (pElement)
		{
			SUIArguments errorString;
			errorString.AddArgument("@ui_lose_connection_with_master_server");
			pElement->CallFunction("SetErrorText", errorString);
		}

		break;
	}
	case FIRENET_EVENT_AUTHORIZATION_COMPLETE:
	{
		pEnv->pUIManager->UnloadPage("AuthorizationPage");
		pEnv->pUIManager->LoadPage("ProfilePage");
		break;
	}
	case FIRENET_EVENT_AUTHORIZATION_COMPLETE_WITH_PROFILE : 
	{
		pEnv->pUIManager->UnloadPage("AuthorizationPage");
		pEnv->pUIManager->LoadPage("MainPage");
		break;
	}
	case FIRENET_EVENT_AUTHORIZATION_FAILED:
	{
		int reason = args.GetInt();
		auto pElement = pEnv->pUIManager->GetUIElement("AuthorizationPage");

		if (pElement)
		{
			SUIArguments errorString;

			if (reason == 0)
				errorString.AddArgument("@ui_login_not_found");
			else if (reason == 1)
				errorString.AddArgument("@ui_account_blocked");
			else if (reason == 2)
				errorString.AddArgument("@ui_incorrect_password");
			else if (reason == 3)
				errorString.AddArgument("@ui_double_authorization");

			pElement->CallFunction("SetServerResultText", errorString);
		}

		break;
	}
	case FIRENET_EVENT_REGISTRATION_COMPLETE:
	{
		auto pElement = pEnv->pUIManager->GetUIElement("AuthorizationPage");

		if (pElement)
		{
			pElement->CallFunction("ShowLoginPage");

			SUIArguments resultString;
			resultString.AddArgument("@ui_registration_complete");

			pElement->CallFunction("SetServerResultText", resultString);
		}

		break;
	}
	case FIRENET_EVENT_REGISTRATION_FAILED:
	{
		int reason = args.GetInt();
		auto pElement = pEnv->pUIManager->GetUIElement("AuthorizationPage");

		if (pElement)
		{
			SUIArguments errorString;

			if (reason == 0)
				errorString.AddArgument("@ui_login_alredy_register");
			else if (reason == 1)
				errorString.AddArgument("@ui_cant_create_account");
			else if (reason == 2)
				errorString.AddArgument("@ui_double_registration");

			pElement->CallFunction("SetServerResultText", errorString);
		}

		break;
	}
	case FIRENET_EVENT_UPDATE_PROFILE:
		break;
	case FIRENET_EVENT_CREATE_PROFILE_COMPLETE:
		break;
	case FIRENET_EVENT_CREATE_PROFILE_FAILED:
		break;
	case FIRENET_EVENT_GET_PROFILE_COMPLETE:
		break;
	case FIRENET_EVENT_GET_PROFILE_FAILED:
		break;
	case FIRENET_EVENT_GET_SHOP_COMPLETE:
		break;
	case FIRENET_EVENT_GET_SHOP_FAILED:
		break;
	case FIRENET_EVENT_BUY_ITEM_COMPLETE:
		break;
	case FIRENET_EVENT_BUY_ITEM_FAILED:
		break;
	case FIRENET_EVENT_REMOVE_ITEM_COMPLETE:
		break;
	case FIRENET_EVENT_REMOVE_ITEM_FAILED:
		break;
	case FIRENET_EVENT_SEND_INVITE_COMPLETE:
		break;
	case FIRENET_EVENT_SEND_INVITE_FAILED:
		break;
	case FIRENET_EVENT_DECLINE_INVITE_COMPLETE:
		break;
	case FIRENET_EVENT_DECLINE_INVITE_FAILED:
		break;
	case FIRENET_EVENT_ACCEPT_INVITE_COMPLETE:
		break;
	case FIRENET_EVENT_ACCEPT_INVITE_FAILED:
		break;
	case FIRENET_EVENT_REMOVE_FRIEND_COMPLETE:
		break;
	case FIRENET_EVENT_REMOVE_FRIEND_FAILED:
		break;
	case FIRENET_EVENT_SEND_CHAT_MSG_COMPLETE:
		break;
	case FIRENET_EVENT_SEND_CHAT_MSG_FAILED:
		break;
	case FIRENET_EVENT_GET_GAME_SERVER_COMPLETE:
		break;
	case FIRENET_EVENT_GET_GAME_SERVER_FAILED:
		break;
	case FIRENET_EVENT_GLOBAL_CHAT_MSG_RECEIVED:
		break;
	case FIRENET_EVENT_PRIVATE_CHAT_MSG_RECEIVED:
		break;
	case FIRENET_EVENT_CLAN_CHAT_MSG_RECEIVED:
		break;
	case FIRENET_EVENT_CONSOLE_COMMAND_RECEIVED:
		break;
	case FIRENET_EVENT_SERVER_MESSAGE_RECEIVED:
		break;
	case FIRENET_EVENT_GAME_SERVER_START_CONNECTION:
		break;
	case FIRENET_EVENT_GAME_SERVER_CONNECTED:
		break;
	case FIRENET_EVENT_GAME_SERVER_CONNECTION_ERROR:
		break;
	case FIRENET_EVENT_GAME_SERVER_DISCONNECTED:
		break;
	default:
		break;
	}
}

CRYREGISTER_SINGLETON_CLASS(CGamePlugin)