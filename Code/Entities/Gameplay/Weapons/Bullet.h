// Copyright (C) 2016-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/EasyShooter/blob/master/LICENCE.md

#pragma once

#include "Entities/Helpers/ISimpleExtension.h"

class CBullet 
	: public ISimpleExtension
{
public:
	virtual ~CBullet() {}

	// ISimpleExtension	
	virtual void PostInit(IGameObject *pGameObject) override;
	virtual void HandleEvent(const SGameObjectEvent &event) override;
	// ~ISimpleExtension

protected:
	void Physicalize();
};