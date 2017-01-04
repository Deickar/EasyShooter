#include "StdAfx.h"
#include "PageAuthorization.h"

CPageAuthorization::~CPageAuthorization()
{
	UnloadPage();

	SAFE_DELETE(pElement);
}

void CPageAuthorization::Init()
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

void CPageAuthorization::LoadPage()
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

void CPageAuthorization::UnloadPage()
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

void CPageAuthorization::ShowPage()
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

void CPageAuthorization::HidePage()
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

void CPageAuthorization::ReloadPage()
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

void CPageAuthorizationEventListener::OnUIEvent(IUIElement * pSender, const SUIEventDesc & event, const SUIArguments & args)
{
	CryLog("[UIEvents] <%s> event called from flash", event.sDisplayName);

	if (strcmp(event.sDisplayName, "OnLogin") == 0)
	{
		string login;
		string password;

		if (args.GetArg(0, login) && args.GetArg(1, password))
		{
			CryLog("Try authorization by login (%s) and password (%s)", login, password);

			// TODO
		}
	}
	else if (strcmp(event.sDisplayName, "OnRegister") == 0)
	{
		string login;
		string password;

		if (args.GetArg(0, login) && args.GetArg(1, password))
		{
			CryLog("Try registration by login (%s) and password (%s)", login, password);

			// TODO
		}
	}
	else if (strcmp(event.sDisplayName, "OnExit") == 0)
	{
		gEnv->pSystem->Quit();
	}
}