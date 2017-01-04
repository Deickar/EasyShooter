#pragma once

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

extern SPluginEnv* pEnv;