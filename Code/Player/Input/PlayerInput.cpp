#include "StdAfx.h"
#include "PlayerInput.h"
#include "Player/Player.h"
#include "Entities/Gameplay/Weapons/ISimpleWeapon.h"
#include "Player/Movement/PlayerMovement.h"
#include "UI/UIManager.h"

#include <CryAnimation/ICryAnimation.h>

void CPlayerInput::PostInit(IGameObject *pGameObject)
{
	m_pPlayer = static_cast<CPlayer *>(pGameObject->QueryExtension("Player"));
	m_moveSpeed = m_pPlayer->GetCVars().m_moveSpeed;

	// NOTE: Since CRYENGINE 5.3, the game is responsible to initialize the action maps
	IActionMapManager *pActionMapManager = gEnv->pGameFramework->GetIActionMapManager();
	pActionMapManager->InitActionMaps("Libs/config/defaultprofile.xml");
	pActionMapManager->Enable(true);
	pActionMapManager->EnableActionMap("player", true);

	if (IActionMap *pActionMap = pActionMapManager->GetActionMap("player"))
	{
		pActionMap->SetActionListener(GetEntityId());
	}

	GetGameObject()->CaptureActions(this);

	// Make sure that this extension is updated regularly via the Update function below
	GetGameObject()->EnableUpdateSlot(this, 0);

	// Populate the action handler callbacks so that we get action map events
	InitializeActionHandler();
}

void CPlayerInput::Update(SEntityUpdateContext &ctx, int updateSlot)
{
	// Start by updating look dir
	Ang3 ypr = CCamera::CreateAnglesYPR(Matrix33(m_lookOrientation));
	
	ypr.x += m_mouseDeltaRotation.x * m_pPlayer->GetCVars().m_rotationSpeedYaw * ctx.fFrameTime;

	// TODO: Perform soft clamp here instead of hard wall, should reduce rot speed in this direction when close to limit.
	ypr.y = CLAMP(ypr.y + m_mouseDeltaRotation.y * m_pPlayer->GetCVars().m_rotationSpeedPitch * ctx.fFrameTime, m_pPlayer->GetCVars().m_rotationLimitsMinPitch, m_pPlayer->GetCVars().m_rotationLimitsMaxPitch);

	ypr.z = 0;

	m_lookOrientation = Quat(CCamera::CreateOrientationYPR(ypr));

	// Reset every frame
	m_mouseDeltaRotation = ZERO;
}

void CPlayerInput::OnPlayerRespawn()
{
	m_inputFlags = 0;
	m_mouseDeltaRotation = ZERO;
	m_lookOrientation = IDENTITY;
}

void CPlayerInput::HandleInputFlagChange(EInputFlags flags, int activationMode, EInputFlagType type)
{
	switch (type)
	{
		case eInputFlagType_Hold:
		{
			if (activationMode == eIS_Released)
			{
				m_inputFlags &= ~flags;
			}
			else
			{
				m_inputFlags |= flags;
			}
		}
		break;
		case eInputFlagType_Toggle:
		{
			if (activationMode == eIS_Released)
			{
				// Toggle the bit(s)
				m_inputFlags ^= flags;
			}
		}
		break;
	}
}

void CPlayerInput::InitializeActionHandler()
{
	m_actionHandler.AddHandler(ActionId("moveleft"), &CPlayerInput::OnActionMoveLeft);
	m_actionHandler.AddHandler(ActionId("moveright"), &CPlayerInput::OnActionMoveRight);
	m_actionHandler.AddHandler(ActionId("moveforward"), &CPlayerInput::OnActionMoveForward);
	m_actionHandler.AddHandler(ActionId("moveback"), &CPlayerInput::OnActionMoveBack);

	// --------------
	m_actionHandler.AddHandler(ActionId("jump"), &CPlayerInput::OnActionJump);
	m_actionHandler.AddHandler(ActionId("sprint"), &CPlayerInput::OnActionSprint);
	m_actionHandler.AddHandler(ActionId("toggleTP"), &CPlayerInput::OnToggleThirdPersonMode);
	m_actionHandler.AddHandler(ActionId("gamePause"), &CPlayerInput::OnActionGamePaused);

	// Debug actions
	m_actionHandler.AddHandler(ActionId("phys_debug"), &CPlayerInput::OnPhysicDebug);
	// --------------

	m_actionHandler.AddHandler(ActionId("mouse_rotateyaw"), &CPlayerInput::OnActionMouseRotateYaw);
	m_actionHandler.AddHandler(ActionId("mouse_rotatepitch"), &CPlayerInput::OnActionMouseRotatePitch);

	m_actionHandler.AddHandler(ActionId("shoot"), &CPlayerInput::OnActionShoot);
}

void CPlayerInput::OnAction(const ActionId &action, int activationMode, float value)
{
	// This function is called when inputs trigger action map events
	// The handler below maps the event (see 'action') to a callback, further below in this file.
	m_actionHandler.Dispatch(this, GetEntityId(), action, activationMode, value);
}

bool CPlayerInput::OnActionMoveLeft(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	HandleInputFlagChange(eInputFlag_MoveLeft, activationMode);
	return true;
}

bool CPlayerInput::OnActionMoveRight(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	HandleInputFlagChange(eInputFlag_MoveRight, activationMode);
	return true;
}

bool CPlayerInput::OnActionMoveForward(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	HandleInputFlagChange(eInputFlag_MoveForward, activationMode);
	return true;
}

bool CPlayerInput::OnActionMoveBack(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	HandleInputFlagChange(eInputFlag_MoveBack, activationMode);
	return true;
}

bool CPlayerInput::OnActionJump(EntityId entityId, const ActionId & actionId, int activationMode, float value)
{
	if (activationMode == eIS_Pressed)
	{
		auto *pMovement = m_pPlayer->GetMovement();
		auto *pEntity = m_pPlayer->GetEntity();
		auto *pPhysics = GetEntity()->GetPhysics();

		if (pPhysics && pEntity &&  pMovement->IsOnGround())
		{
			// This bad way! We need use animations for this action
			pe_action_impulse impulseAction;

			//impulseAction.impulse = pEntity->GetWorldRotation().GetColumn2() * 500.f * m_pPlayer->GetCVars().m_jumpHeightMultiplier;

			Vec3 impulsePos = pEntity->GetWorldPos();
			impulsePos.x = 0;
			impulsePos.y = 0;

			impulseAction.impulse = impulsePos * 15.f * m_pPlayer->GetCVars().m_jumpHeightMultiplier;
			pPhysics->Action(&impulseAction);
		}
	}
	return true;
}

bool CPlayerInput::OnActionSprint(EntityId entityId, const ActionId & actionId, int activationMode, float value)
{	
	ICVar* speed = gEnv->pConsole->GetCVar("pl_moveSpeed");

	if (activationMode == eIS_Down)
	{
		if (speed)
			speed->Set(m_moveSpeed + 30.0f);
	}
	else if (activationMode == eIS_Released)
	{
		if (speed)
			speed->Set(m_moveSpeed);
	}

	return true;
}

bool CPlayerInput::OnToggleThirdPersonMode(EntityId entityId, const ActionId & actionId, int activationMode, float value)
{
	if (activationMode == eIS_Released)
	{
		if (m_pPlayer->IsThirdPerson())
			m_pPlayer->SetThirdPerson(false);
		else
			m_pPlayer->SetThirdPerson(true);
	}

	return true;
}

bool CPlayerInput::OnActionGamePaused(EntityId entityId, const ActionId & actionId, int activationMode, float value)
{
	// Load InGame page if game paused and unload it when game resumed
	if (!gEnv->IsEditor() && pEnv->bInGame && activationMode == eIS_Released && !bGamePaused)
	{
		bGamePaused = true;

		// Block input
		IActionMapManager* pAMM = gEnv->pGameFramework->GetIActionMapManager();
		if (pAMM)
		{
			pAMM->EnableFilter("no_move", true);	
		}

		pEnv->pUIManager->LoadPage("InGamePage");
		gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_GAME_PAUSED, 0, 0);
	}
	else if (!gEnv->IsEditor() && pEnv->bInGame && activationMode == eIS_Released && bGamePaused)
	{
		bGamePaused = false;

		// Unblock input
		IActionMapManager* pAMM = gEnv->pGameFramework->GetIActionMapManager();
		if (pAMM)
		{
			pAMM->EnableFilter("no_move", false);
		}

		pEnv->pUIManager->UnloadPage("InGamePage");
		gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_GAME_RESUMED, 0, 0);
	}

	return false;
}

// Debug functions
bool CPlayerInput::OnPhysicDebug(EntityId entityId, const ActionId & actionId, int activationMode, float value)
{
	if (activationMode == eIS_Released && !bPhysDebug)
	{
		CryLog("Physic debugging enabled");

		gEnv->pConsole->ExecuteString("p_draw_helpers 1");	
		bPhysDebug = true;
	}
	else if (activationMode == eIS_Released && bPhysDebug)
	{
		CryLog("Physic debugging disabled");

		gEnv->pConsole->ExecuteString("p_draw_helpers 0");
		bPhysDebug = false;
	}

	return false;
}
//

bool CPlayerInput::OnActionMouseRotateYaw(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	m_mouseDeltaRotation.x -= value;
	return true;
}

bool CPlayerInput::OnActionMouseRotatePitch(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	m_mouseDeltaRotation.y -= value;
	return true;
}

bool CPlayerInput::OnActionShoot(EntityId entityId, const ActionId& actionId, int activationMode, float value)
{
	// Only fire on press, not release
	if (activationMode == /*eIS_Pressed*/ eIS_Down)
	{
		auto *pWeapon = m_pPlayer->GetCurrentWeapon();
		auto *pCharacter = GetEntity()->GetCharacter(CPlayer::eGeometry_FirstPerson);

		if (pWeapon != nullptr && pCharacter != nullptr)
		{
			auto *pBarrelOutAttachment = pCharacter->GetIAttachmentManager()->GetInterfaceByName("barrel_out");

			if (pBarrelOutAttachment != nullptr)
			{
				QuatTS bulletOrigin = pBarrelOutAttachment->GetAttWorldAbsolute();

				pWeapon->RequestFire(bulletOrigin.t, bulletOrigin.q);
			}
		}
	}

	return true;
}