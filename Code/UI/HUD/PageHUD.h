#pragma once

#include "UI/IUIPage.h"

class CPageHUDEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageHUD : public IUIPage
{
public:
	CPageHUD(const char* name) : IUIPage(name)
	{
		Init();
	};
	~CPageHUD();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	// ~IUIPage
private:
	IUIElement* pElement;
	CPageHUDEventListener m_EventListener;
};