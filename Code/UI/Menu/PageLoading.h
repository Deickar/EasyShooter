// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "UI/IUIPage.h"

class CPageLoading : public IUIPage
{
public:
	CPageLoading(const char* name) : IUIPage(name) 
	{
		m_Background = "backgrounds/loading.png";
		m_LoadingText = "@ui_level_loading";
	}
public:
	// IUIPage
	virtual void OnLoadPage(bool loaded)
	{
		if (loaded && pElement)
		{
			// Call set loading text
			SUIArguments load_args;
			load_args.AddArgument(m_LoadingText);
			pElement->CallFunction("SetLoadingStatus", load_args);

			// Call load background function
			SUIArguments bg_args;
			bg_args.AddArgument(m_Background);
			pElement->CallFunction("LoadBackground", bg_args);
		}
	}
	// ~IUIPage
	void SetBackground(const char* name) { m_Background = name; };
	void SetLoadingText(const char* text) { m_LoadingText = text; };
private:
	const char* m_Background;
	const char* m_LoadingText;
};