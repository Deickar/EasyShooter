#pragma once

#include "UI/IUIPage.h"

class CPageProfileEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageProfile : public IUIPage
{
public:
	CPageProfile(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageProfile();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	//
private:
	CPageProfileEventListener m_EventListener;
};