// FireNET Source File
// Copyright (C), BeatGames, 2014-2017

#pragma once

// Item types for shop/loadout items
enum EFireNetItemType
{
	EItem_None,
	EItem_Weapon,
	EItem_Booster,
	EItem_Other,
};

// Player status
enum EFireNetPlayerStatus
{
	EStatus_Online,
	EStatus_InGame,
	EStatus_InRoom,
	EStatus_AFK,
	EStatus_Offline,
};

// Item structure
struct SFireNetItem
{
	string name;
	EFireNetItemType type;
	int cost;
	int minLvlForBuy;
};

// Friend stucture
struct SFireNetFriend
{
	int uid;
	string name;
	EFireNetPlayerStatus status;
};

// Player statistic
struct SFireNetStats
{
	int kills;
	int deaths;
	double kd;
};

// Player profile
struct SFireNetProfile
{
	int uid;
	string nickname;
	string fileModel;
	int lvl;
	int xp;
	int money;
	std::vector<SFireNetItem> items;
	std::vector<SFireNetFriend> friends;
	std::vector<SFireNetStats> stats;
};

// Game server structure
struct SFireNetGameServer
{
	string name;
	const char* ip;
	int port;
	string map;
	string gamerules;
	int online;
	int maxPlayers;
};

// FireNet entity base class
class IFireNetEntity
{
public:
	IFireNetEntity() {}
	~IFireNetEntity() {}
private:
};