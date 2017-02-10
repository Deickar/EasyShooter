// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "Entities/Helpers/ISimpleExtension.h"
#include <CryEntitySystem/IEntityComponent.h>
#include <CrySerialization/Decorators/Resources.h>

class CLiftEntity
	: public ISimpleExtension
	, public IEntityPropertyGroup
{
public:
	virtual ~CLiftEntity() {}

	// Entity properties
	virtual IEntityPropertyGroup* GetPropertyGroup() { return this; }
	virtual const char* GetLabel() const override { return "Lift"; }
	virtual void SerializeProperties(Serialization::IArchive& archive) override
	{
		archive(m_geometry, "Geometry", "Geometry");
		archive(m_floorsCount, "FloorsCount", "FloorsCount");
		archive(m_floorHeight, "FloorHeight", "FloorHeight");
		archive(m_speed, "Speed", "Speed");
		archive(m_pause, "PauseTime", "PauseTime");
		archive(bIsLooped, "Looped", "Looped");

		if (!archive.isInput())
		{
			Reset();
		}
	};

	// ISimpleExtension	
	virtual void PostInit(IGameObject *pGameObject) override;
	virtual void HandleEvent(const SGameObjectEvent &event) override;
	virtual void Update(SEntityUpdateContext& ctx, int updateSlot) override;
	virtual void ProcessEvent(SEntityEvent& event) override;
	// ~ISimpleExtension
protected:
	void Reset();
	void Physicalize();

	void StartLift();
	void PauseLift();
	void StopLift();
protected:	
	string m_geometry = "Objects/default/primitive_box.cgf";
	float  m_mass = 10;

	float  m_speed = 0.01f;
	int    m_floorsCount = 1;
	float  m_floorHeight = 3.0f;
	float  m_pause = 3.f;
private:
	float  m_StartHeigth = 0.f;
	float  m_EndHeigth = 0.f;

	float  m_PauseCounter = 0.f;
	int    m_FloorCounter = 1;
	int    m_FloorRevertCounter = 1;

	bool   bIsStarted = false;
	bool   bIsEnd = false;
	bool   bIsPaused = true;
	bool   bIsLooped = false;
};