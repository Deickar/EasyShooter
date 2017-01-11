// FireNET Source File
// Copyright (C), BeatGames, 2014-2017

#pragma once

#include "IFireNetBase.h"
#include "IFireNetListener.h"

class CTcpPacket;
class CUdpPacket;

// Base interface for using in game plugin
struct IFireNetCore
{
	// Register FireNet listener for work with UI or somethings else
	virtual void RegisterFireNetListener(IFireNetListener *listener) = 0;

	// Register entity in FireNet system for synchronization entity state in game world
	virtual void RegisterFireNetEntity(IFireNetEntity *entity) = 0;

	/**************************************************************************************/
	/*************************** Master server functionality ******************************/
	/**************************************************************************************/

	// Connect to master server
	virtual void ConnectToMasterServer() = 0;

	// Send authorization request to master server
	virtual void Authorization(const string &login, const string &password) = 0;

	// Send register request to master server
	virtual void Registration(const string &login, const string &password) = 0;

	// Send create profile request to master server
	virtual void CreateProfile(const string &nickname, const string &character) = 0;

	// Send get profile request to master server
	virtual void GetProfile(int uid = 0) = 0;

	// Send get shop request to master server
	virtual void GetShop() = 0;

	// Send buy item request to master server
	virtual void BuyItem(const string &item) = 0;

	// Send remove item request to master server
	virtual void RemoveItem(const string &item) = 0;

	// Send invite to other player
	virtual void SendInvite(EFireNetInviteType type, int uid) = 0;

	// Decline invite from other player
	virtual void DeclineInvite() = 0;

	// Accept invite from other player
	virtual void AcceptInvite() = 0;

	// Send remove friend request to master server
	virtual void RemoveFriend(int uid) = 0;

	// Send chat message
	virtual void SendChatMessage(EFireNetChatMsgType type, int uid = 0) = 0;

	// Send get game server request to master server
	virtual void GetGameServer(const string &map, const string &gamerules) = 0;

	// Send some raw request to master server. For e.g. this may be login or register request
	// You need add to you project TcpPacket.h for using this function
	virtual void SendRawRequestToMasterServer(CTcpPacket &packet) = 0;


	/**************************************************************************************/
	/************************* Dedicated server functionality *****************************/
	/**************************************************************************************/

	// Connect to dedicated game server
	virtual void ConnectToGameServer() = 0;

	// Send raw request to dedicated server (Move, action, script, etc...)
	// You need add to you project UdpPacket.h for using this function
	virtual void SendRawRequestToGameServer(CUdpPacket &packet) = 0;
};