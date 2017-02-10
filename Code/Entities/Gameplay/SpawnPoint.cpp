// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#include "StdAfx.h"
#include "SpawnPoint.h"
#include "GamePlugin.h"
#include "Player/Player.h"

#include <CryEntitySystem/IEntitySystem.h>

class CSpawnPointRegistrator : public IEntityRegistrator
{
	virtual void Register() override
	{
		CGamePlugin::RegisterEntityWithDefaultComponent<CSpawnPoint>("SpawnPoint", "Gameplay", "SpawnPoint.bmp", true);
	}

	virtual void Unregister() override {}
};

CSpawnPointRegistrator g_spawnerRegistrator;

void CSpawnPoint::PostInit(IGameObject * pGameObject)
{
	LoadMesh(0, "Editor/Objects/spawnpointhelper.cgf");
}

void CSpawnPoint::ProcessEvent(SEntityEvent & event)
{
	switch (event.event)
	{
	case ENTITY_EVENT_RESET:
	{
		switch (event.nParam[0])
		{
		case 0: // Game ends
			GetEntity()->Hide(false);
			break;
		case 1: // Game starts
			GetEntity()->Hide(true);
			break;
		default:
			break;
		}
	}
	}
}

void CSpawnPoint::SpawnEntity(IEntity &otherEntity)
{
	if (bEnabled)
		otherEntity.SetWorldTM(GetEntity()->GetWorldTM());
}