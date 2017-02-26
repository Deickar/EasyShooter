// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#define TITLE "[GamePlugin] "

class CUIManager;

struct SPluginEnv
{
	SPluginEnv()
	{
		pUIManager = nullptr;

		bInGame = false;
	}

	CUIManager* pUIManager;

	bool bInGame;
};

extern SPluginEnv* mEnv;