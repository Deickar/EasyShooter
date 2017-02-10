// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include <CrySystem/Scaleform/IFlashUI.h>

class IUIPage;

// Menu pages
class CPageAuthorization;
class CPageInGame;
class CPageLoading;
class CPageLoadout;
class CPageMain;
class CPageProfile;
class CPageServerSearch;
class CPageSettings;
class CPageShop;
class CPageError;

// HUD
class CPageHUD;

class CUIManager
{
public:
	CUIManager();
	~CUIManager();
private:
	bool Init();
public:
	void LoadPage(const char* name);
	void UnloadPage(const char* name);
	void ShowPage(const char* name);
	void HidePage(const char* name);
	void ReloadPage(const char* name);

	void HideAll();
	void UnloadAll();

	int GetPagesCount();
	IUIPage* GetPage(const char* name);
	IUIElement* GetUIElement(const char* name);
public:
	CPageAuthorization* pPageAuthorization;
	CPageInGame* pPageInGame;
	CPageLoading* pPageLoading;
	CPageLoadout* pPageLoadout;
	CPageMain* pPageMain;
	CPageProfile* pPageProfile;
	CPageServerSearch* pPageServerSearch;
	CPageSettings* pPageSettings;
	CPageShop* pPageShop;
	CPageHUD* pPageHUD;
	CPageError* pPageError;
private:
	std::vector<IUIPage*> m_Pages;

	bool bIsInit;
};