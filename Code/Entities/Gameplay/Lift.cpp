// Copyright (C) 2017 BeatGames. All rights reserved. Contacts: <chernecoff@gmail.com>

#include "StdAfx.h"
#include "Lift.h"
#include "GamePlugin.h"

class CLiftRegistrator : public IEntityRegistrator
{
	virtual void Register() override
	{
		CGamePlugin::RegisterEntityWithDefaultComponent<CLiftEntity>("Lift", "Gameplay", "smartobject.bmp", true);
	}

	virtual void Unregister() override {}
};

static CLiftRegistrator g_testRegistrator;

void CLiftEntity::Reset()
{
	LoadMesh(0, m_geometry);
	Physicalize();
}

void CLiftEntity::Physicalize()
{
	SEntityPhysicalizeParams params;
	params.type = PE_STATIC;
	params.mass = m_mass;

	GetEntity()->Physicalize(params);
}

void CLiftEntity::StartLift()
{
	bIsEnd = false;
	bIsStarted = true;

	m_StartHeigth = GetEntity()->GetPos().z;

	int m_X = m_floorsCount > 1 ? m_floorsCount - 1 : m_floorsCount;
	m_EndHeigth = m_StartHeigth + (m_X * m_floorHeight);

	PauseLift();
}

void CLiftEntity::PauseLift()
{
	bIsPaused = true;
	m_PauseCounter = 0.f;
}

void CLiftEntity::StopLift()
{
	bIsEnd = true;
	bIsStarted = false;
	bIsPaused = false;

	m_PauseCounter = 0.f;
	m_FloorCounter = 1;
	m_FloorRevertCounter = 1;
}

void CLiftEntity::PostInit(IGameObject * pGameObject)
{
	pGameObject->EnableUpdateSlot(this, 0);
	Reset();
}

void CLiftEntity::HandleEvent(const SGameObjectEvent & event)
{
}

void CLiftEntity::Update(SEntityUpdateContext & ctx, int updateSlot)
{
	if (gEnv->pSystem->IsQuitting())
		return;

	if (!bIsEnd && bIsStarted && !bIsPaused)
	{
		Vec3 m_currentPos = GetEntity()->GetPos();
		Vec3 m_newPos;
		m_newPos.x = m_currentPos.x;
		m_newPos.y = m_currentPos.y;
		m_newPos.z = m_currentPos.z + m_speed;

		GetEntity()->SetPos(m_newPos);

		if (m_currentPos.z >= m_StartHeigth + (m_FloorCounter * m_floorHeight))
		{
			m_FloorCounter++;	
			PauseLift();	
		}

		if (m_currentPos.z >= m_EndHeigth)
			bIsEnd = true;

		Physicalize();
	}

	if (bIsEnd && bIsStarted && !bIsPaused && bIsLooped)
	{
		Vec3 m_currentPos = GetEntity()->GetPos();
		Vec3 m_newPos;
		m_newPos.x = m_currentPos.x;
		m_newPos.y = m_currentPos.y;
		m_newPos.z = m_currentPos.z - m_speed;

		GetEntity()->SetPos(m_newPos);

		if (m_currentPos.z <= m_EndHeigth - (m_FloorRevertCounter * m_floorHeight))
		{
			m_FloorRevertCounter++;
			m_FloorCounter--;
			PauseLift();
		}

		if (m_currentPos.z <= m_StartHeigth)
		{
			bIsEnd = false;
			m_FloorRevertCounter = 1;
		}

		Physicalize();
	}

	if (bIsPaused && m_pause > 0.f)
	{
		m_PauseCounter += 0.015f;

		if (m_PauseCounter >= m_pause)
			bIsPaused = false;
	}
}

void CLiftEntity::ProcessEvent(SEntityEvent &event)
{
	switch (event.event)
	{
	case ENTITY_EVENT_START_GAME:
	{
		StartLift();
		break;
	}
	case ENTITY_EVENT_RESET:
	{
		StopLift();
	}
	default:
		break;
	}
}