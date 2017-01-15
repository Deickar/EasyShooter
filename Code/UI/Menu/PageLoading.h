#pragma once

#include "UI/IUIPage.h"

class CPageLoading : public IUIPage
{
public:
	CPageLoading(const char* name) : IUIPage(name) 
	{
		Init();
	};
	~CPageLoading();
	// IUIPage
	virtual void Init() override;
	virtual void LoadPage() override;
	virtual void UnloadPage() override;
	virtual void ShowPage() override;
	virtual void HidePage() override;
	virtual void ReloadPage() override;
	//
	void SetBackground(const char* name) { m_Background = name; };
	void SetLoadingText(const char* text) { m_LoadingText = text; };
private:
	const char* m_Background;
	const char* m_LoadingText;
};