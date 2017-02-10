// Copyright (C) 2014-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/FireNET/blob/master/LICENSE

#pragma once

#include "IFireNetClientBase.h"

struct IFireNetClientCore
{
	virtual void SendMovementRequest(EFireNetClientActions action, float value = 0.f) = 0;
};