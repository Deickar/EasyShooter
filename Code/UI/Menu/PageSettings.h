#pragma once

#include "UI/IUIPage.h"

class CPageSettingsEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageSettings : public IUIPage
{
public:
	CPageSettings(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageSettings();
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
	CPageSettingsEventListener m_EventListener;
};