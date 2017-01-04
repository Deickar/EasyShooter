#pragma once

#include "UI/IUIPage.h"

class CPageShopEventListener : public IUIElementEventListener
{
public:
	// IUIElementEventListener
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	// ~IUIElementEventListener
};

class CPageShop : public IUIPage
{
public:
	CPageShop(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageShop();
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
	CPageShopEventListener m_EventListener;
};