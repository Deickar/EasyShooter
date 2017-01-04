#include "StdAfx.h"
#include "PageInGame.h"

CPageInGame::~CPageInGame()
{
	UnloadPage();

	SAFE_DELETE(pElement);
}

void CPageInGame::Init()
{
	CryLog("[%s] Init()", GetName());

	if (gEnv->pFlashUI)
	{
		pElement = gEnv->pFlashUI->GetUIElement(GetName());

		if (pElement)
		{
			pElement->AddEventListener(&m_EventListener, "EventListener");

			CryLog("[%s] Success init page", GetName());
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed init. UIElement not found", GetName());
		}
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed init. Flash not loaded", GetName());
	}
}

void CPageInGame::LoadPage()
{
	CryLog("[%s] LoadPage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(true);

		// Call load background function
		SUIArguments args;
		args.AddArgument("backgrounds/main_menu.png");
		pElement->CallFunction("LoadBackground", args);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed load page. UIElement not found", GetName());
	}
}

void CPageInGame::UnloadPage()
{
	CryLog("[%s] UnloadPage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(false);
		pElement->RemoveEventListener(&m_EventListener);
		pElement->Unload();
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed load page. UIElement not found", GetName());
	}
}

void CPageInGame::ShowPage()
{
	CryLog("[%s] ShowPage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(true);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed show page. UIElement not found", GetName());
	}
}

void CPageInGame::HidePage()
{
	CryLog("[%s] HidePage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(false);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed hide page. UIElement not found", GetName());
	}
}

void CPageInGame::ReloadPage()
{
	CryLog("[%s] ReloadPage()", GetName());

	if (pElement)
	{
		pElement->Reload(true);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed reload page. UIElement not found", GetName());
	}
}

void CPageInGameEventListener::OnUIEvent(IUIElement * pSender, const SUIEventDesc & event, const SUIArguments & args)
{
	CryLog("[UIEvents] <%s> event called from flash", event.sDisplayName);

	if (strcmp(event.sDisplayName, "OnResume") == 0)
	{
	}
}