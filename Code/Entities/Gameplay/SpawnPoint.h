#pragma once

#include "Entities/Helpers/ISimpleExtension.h"

class CSpawnPoint : public ISimpleExtension
{
public:
	virtual ~CSpawnPoint() {}

	void SpawnEntity(IEntity &otherEntity);
};