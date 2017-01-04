#include "StdAfx.h"
#include "SpawnPoint.h"
#include "GamePlugin.h"
#include "Player/Player.h"

#include <CryEntitySystem/IEntitySystem.h>

class CSpawnPointRegistrator : public IEntityRegistrator
{
	virtual void Register() override
	{
		//CGamePlugin::RegisterEntityWithDefaultComponent<CSpawnPoint>("SpawnPoint");
		RegisterEntityWithDefaultComponent<CSpawnPoint>("SpawnPoint", "Default", "SpawnPoint.bmp");
	}

	virtual void Unregister() override {}
};

CSpawnPointRegistrator g_spawnerRegistrator;

void CSpawnPoint::SpawnEntity(IEntity &otherEntity)
{
	otherEntity.SetWorldTM(GetEntity()->GetWorldTM());
}