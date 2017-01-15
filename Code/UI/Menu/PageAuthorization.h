#pragma once

#include "UI/IUIPage.h"

class CPageAuthorizationEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageAuthorization : public IUIPage
{
public:
	CPageAuthorization(const char* name) : IUIPage(name)
	{
		Init(); 
	};
	~CPageAuthorization();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	// ~IUIPage
private:
	CPageAuthorizationEventListener m_EventListener;
};