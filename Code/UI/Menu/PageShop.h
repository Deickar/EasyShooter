// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "UI/IUIPage.h"

class CPageShopEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageShop : public IUIPage
{
public:
	CPageShop(const char* name) : IUIPage(name, &m_EventListener) {}
public:
	// IUIPage
	virtual void OnLoadPage(bool loaded) override
	{
		if (loaded)
		{
			// Call load background function
			SUIArguments args;
			args.AddArgument("backgrounds/error.png");
			pElement->CallFunction("LoadBackground", args);
		}
	}
	// ~IUIPage
private:
	CPageShopEventListener m_EventListener;
};