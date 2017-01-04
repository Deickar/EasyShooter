// FireNET Source File
// Copyright (C), BeatGames, 2014-2017

#pragma once

#include "IFireNetBase.h"
#include "IFireNetListener.h"

class CTcpPaket;

// Base interface for using in game plugin
struct IFireNetCore
{
	// Register FireNet listener for work with UI or somethings else
	virtual void RegisterFireNetListener(IFireNetListener* listener) = 0;

	// Register entity in FireNet system for synchronization entity state in game world
	virtual void RegisterFireNetEntity(IFireNetEntity *entity) = 0;

	// Connect to master server
	virtual void ConnectToMasterServer(const char* ip, int port) = 0;

	// Send some request to master server. For e.g. this may be login or register request
	virtual void SendRequestToMasterServer(CTcpPaket &packet) = 0;

	// Connect to dedicated game server
	virtual void ConnectToGameServer(const char* ip, int port) = 0;

	// Send move request to dedicated server
	virtual void SendRequestToGameServer(/*TODO*/) = 0;
};