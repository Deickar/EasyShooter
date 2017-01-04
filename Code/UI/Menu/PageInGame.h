#pragma once

#include "UI/IUIPage.h"

class CPageInGameEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageInGame : public IUIPage
{
public:
	CPageInGame(const char* name) : IUIPage(name) 
	{ 
		Init(); 
	};
	~CPageInGame();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	//
private:
	IUIElement* pElement;
	CPageInGameEventListener m_EventListener;
};