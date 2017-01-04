#pragma once

#include "UI/IUIPage.h"

class CPageLoadoutEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageLoadout : public IUIPage
{
public:
	CPageLoadout(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageLoadout();
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
	CPageLoadoutEventListener m_EventListener;
};