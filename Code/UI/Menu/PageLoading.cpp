#include "StdAfx.h"
#include "PageLoading.h"

CPageLoading::~CPageLoading()
{
	UnloadPage();

	SAFE_DELETE(pElement);
}

void CPageLoading::Init()
{
	CryLog("[%s] Init()", GetName());

	if (gEnv->pFlashUI)
	{
		pElement = gEnv->pFlashUI->GetUIElement(GetName());

		if (pElement)
		{
			CryLog("[%s] Success init page", GetName());

			// Set default values
			m_Background = "backgrounds/loading.png";
			m_LoadingText = "@ui_level_loading";
		}
		else
		{
			CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed init. UIElement not found", GetName());
		}
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed init. Flash not loaded", GetName());
	}
}

void CPageLoading::LoadPage()
{
	CryLog("[%s] LoadPage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(true);

		// Call set loading text
		SUIArguments load_args;
		load_args.AddArgument(m_LoadingText);
		pElement->CallFunction("SetLoadingStatus", load_args);

		// Call load background function
		SUIArguments bg_args;
		bg_args.AddArgument(m_Background);
		pElement->CallFunction("LoadBackground", bg_args);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed load page. UIElement not found", GetName());
	}
}

void CPageLoading::UnloadPage()
{
	CryLog("[%s] UnloadPage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(false);
		pElement->Unload();
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed unload page. UIElement not found", GetName());
	}
}

void CPageLoading::ShowPage()
{
	CryLog("[%s] ShowPage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(true);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed show page. UIElement not found", GetName());
	}
}

void CPageLoading::HidePage()
{
	CryLog("[%s] HidePage()", GetName());

	if (pElement)
	{
		pElement->SetVisible(false);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed hide page. UIElement not found", GetName());
	}
}

void CPageLoading::ReloadPage()
{
	CryLog("[%s] ReloadPage()", GetName());

	if (pElement)
	{
		pElement->Reload(true);
	}
	else
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "[%s] Failed reload page. UIElement not found", GetName());
	}
}