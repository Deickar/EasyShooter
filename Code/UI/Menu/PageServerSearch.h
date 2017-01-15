#pragma once

#include "UI/IUIPage.h"

class CPageServerSearchEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageServerSearch : public IUIPage
{
public:
	CPageServerSearch(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageServerSearch();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	//
private:
	CPageServerSearchEventListener m_EventListener;
};