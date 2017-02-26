// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#include "StdAfx.h"
#include "PageAuthorization.h"
#include "GamePlugin.h"

void CPageAuthorizationEventListener::OnUIEvent(IUIElement * pSender, const SUIEventDesc & event, const SUIArguments & args)
{
	CryLog(TITLE "<%s> event called from flash", event.sDisplayName);

	if (strcmp(event.sDisplayName, "OnLogin") == 0)
	{
		string login;
		string password;

		if (!gFireNet || !gFireNet->pCore)
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, TITLE "Can't authorizate - FireNet-Core plugin not init!");
			return;
		}

		if (args.GetArg(0, login) && args.GetArg(1, password))
			gFireNet->pCore->Authorization(login.c_str(), password.c_str());
	}
	else if (strcmp(event.sDisplayName, "OnRegister") == 0)
	{
		string login;
		string password;

		if (!gFireNet || !gFireNet->pCore)
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, TITLE "Can't register - FireNet-Core plugin not init!");
			return;
		}

		if (args.GetArg(0, login) && args.GetArg(1, password))
		{
			gFireNet->pCore->Registration(login.c_str(), password.c_str());
		}
	}
	else if (strcmp(event.sDisplayName, "OnExit") == 0)
	{
		mEnv->pUIManager->pPageAuthorization->UnloadPage();

		gEnv->pSystem->Quit();
	}
}
