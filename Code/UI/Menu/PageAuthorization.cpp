// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#include "StdAfx.h"
#include "PageAuthorization.h"

void CPageAuthorizationEventListener::OnUIEvent(IUIElement * pSender, const SUIEventDesc & event, const SUIArguments & args)
{
	CryLog("[UIEvents] <%s> event called from flash", event.sDisplayName);

	if (strcmp(event.sDisplayName, "OnLogin") == 0)
	{
		string login;
		string password;

		if (args.GetArg(0, login) && args.GetArg(1, password))
		{
			gEnv->pFireNetCore->Authorization(login.c_str(), password.c_str());
		}
	}
	else if (strcmp(event.sDisplayName, "OnRegister") == 0)
	{
		string login;
		string password;

		if (args.GetArg(0, login) && args.GetArg(1, password))
		{
			gEnv->pFireNetCore->Registration(login.c_str(), password.c_str());
		}
	}
	else if (strcmp(event.sDisplayName, "OnExit") == 0)
	{
		gEnv->pSystem->Quit();
	}
}
