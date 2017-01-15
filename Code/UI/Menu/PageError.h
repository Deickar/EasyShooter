#pragma once

#include "UI/IUIPage.h"

class CPageErrorEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageError : public IUIPage
{
public:
	CPageError(const char* name) : IUIPage(name)
	{
		Init();
	};
	~CPageError();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	//
private:
	CPageErrorEventListener m_EventListener;
};