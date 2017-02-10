// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "UI/IUIPage.h"

class CPageMainEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageMain : public IUIPage
{
public:
	CPageMain(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageMain();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	//
private:
	CPageMainEventListener m_EventListener;
};