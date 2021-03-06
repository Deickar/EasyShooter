// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#include "StdAfx.h"
#include "UIManager.h"

// UI pages
#include "Menu/PageAuthorization.h"
#include "Menu/PageInGame.h"
#include "Menu/PageLoading.h"
#include "Menu/PageLoadout.h"
#include "Menu/PageMain.h"
#include "Menu/PageProfile.h"
#include "Menu/PageServerSearch.h"
#include "Menu/PageSettings.h"
#include "Menu/PageShop.h"
#include "Menu/PageError.h"

#include "HUD/PageHUD.h"

CUIManager::CUIManager()
	: bIsInit(false)
{
	CryLogAlways(TITLE "Start initialization UI manager...");

	if (gEnv->pFlashUI)
	{
		pPageAuthorization = new CPageAuthorization("AuthorizationPage");
		pPageInGame = new CPageInGame("InGamePage");
		pPageLoading = new CPageLoading("LoadingPage");
		pPageLoadout = new CPageLoadout("LoadoutPage");
		pPageMain = new CPageMain("MainPage");
		pPageProfile = new CPageProfile("ProfilePage");
		pPageServerSearch = new CPageServerSearch("ServeSearchPage");
		pPageSettings = new CPageSettings("SettingsPage");
		pPageShop = new CPageShop("ShopPage");
		pPageHUD = new CPageHUD("HUDPage");
		pPageError = new CPageError("ErrorPage");

		Init();
	}
	else 
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, TITLE "Failed init UI manager. Flash not loaded");
	}
}

CUIManager::~CUIManager()
{
	UnloadAll();

	SAFE_DELETE(pPageAuthorization);
	SAFE_DELETE(pPageInGame);
	SAFE_DELETE(pPageLoading);
	SAFE_DELETE(pPageLoadout);
	SAFE_DELETE(pPageMain);
	SAFE_DELETE(pPageProfile);
	SAFE_DELETE(pPageServerSearch);
	SAFE_DELETE(pPageSettings);
	SAFE_DELETE(pPageShop);
	SAFE_DELETE(pPageError);
}

bool CUIManager::Init()
{
	if (!bIsInit)
	{
		m_Pages.push_back((IUIPage*)pPageAuthorization);
		m_Pages.push_back((IUIPage*)pPageInGame);
		m_Pages.push_back((IUIPage*)pPageLoading);
		m_Pages.push_back((IUIPage*)pPageLoadout);
		m_Pages.push_back((IUIPage*)pPageMain);
		m_Pages.push_back((IUIPage*)pPageProfile);
		m_Pages.push_back((IUIPage*)pPageServerSearch);
		m_Pages.push_back((IUIPage*)pPageSettings);
		m_Pages.push_back((IUIPage*)pPageShop);
		m_Pages.push_back((IUIPage*)pPageHUD);
		m_Pages.push_back((IUIPage*)pPageError);

		CryLogAlways(TITLE "Success init UI manager. Loaded %d pages", m_Pages.size());

		bIsInit = true;
		return bIsInit;
	}

	CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, TITLE "Failed init UI manager. Manager already initialized");
	return false;
}

void CUIManager::LoadPage(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			(*it)->LoadPage();
		}
	}
}

void CUIManager::UnloadPage(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			(*it)->UnloadPage();
		}
	}
}

void CUIManager::ShowPage(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			(*it)->ShowPage();
		}
	}
}

void CUIManager::HidePage(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			(*it)->HidePage();
		}
	}
}

void CUIManager::ReloadPage(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			(*it)->ReloadPage();
		}
	}
}

void CUIManager::HideAll()
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		(*it)->HidePage();
	}
}

void CUIManager::UnloadAll()
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		(*it)->UnloadPage();
	}
}

int CUIManager::GetPagesCount()
{
	return m_Pages.size();
}

IUIPage * CUIManager::GetPage(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			return (*it);
		}
	}

	return nullptr;
}

IUIElement * CUIManager::GetUIElement(const char * name)
{
	for (auto it = m_Pages.begin(); it != m_Pages.end(); ++it)
	{
		if (strcmp((*it)->GetName(), name) == 0)
		{
			return (*it)->GetUIElement();
		}
	}

	return nullptr;
}
