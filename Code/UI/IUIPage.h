// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "UI/UIManager.h"
#include <CrySystem/Scaleform/IFlashUI.h>

class IUIPage
{
public:
	IUIPage(const char* name) { this->m_Name = name; }
public:
	virtual void Init() = 0;
	virtual void LoadPage() = 0;
	virtual void UnloadPage() = 0;
	virtual void ShowPage() = 0;
	virtual void HidePage() = 0;
	virtual void ReloadPage() = 0;
	virtual const char* GetName() { return this->m_Name; };
	virtual IUIElement* GetUIElement() { return this->pElement; };
private:
	const char* m_Name;
public:
	IUIElement* pElement;
};