#pragma once

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
private:
	std::vector<IUIPage*> m_Pages;

	bool bIsInit;
};