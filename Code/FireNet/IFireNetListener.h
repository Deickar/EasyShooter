// FireNET Source File
// Copyright (C), BeatGames, 2014-2017

#pragma once

// FireNet events
enum EFireNetEvents
{
	//! Event when start connection to FireNet
	FIRENET_EVENT_MASTER_SERVER_START_CONNECTION,
    //! Event when FireNet success connected
	FIRENET_EVENT_MASTER_SERVER_CONNECTED,
	//! Event when connection to FireNet failed
	FIRENET_EVENT_MASTER_SERVER_CONNECTION_ERROR,
	//! Event when connection with FireNet lost
	FIRENET_EVENT_MASTER_SERVER_DISCONNECTED,

	// Special events

	//! Event when authorization complete
	FIRENET_EVENT_AUTHORIZATION_COMPLETE,
	//! Event when authorization failed
	FIRENET_EVENT_AUTHORIZATION_FAILED,
	//! Event when registration complete
	FIRENET_EVENT_REGISTRATION_COMPLETE,
	//! Event when registration failed
	FIRENET_EVENT_REGISTRATION_FAILED,
	//! Event when create profile complete
	FIRENET_EVENT_CREATE_PROFILE_COMPLETE,
	//! Event when create profile failed
	FIRENET_EVENT_CREATE_PROFILE_FAILED,
	//! Event when get profile complete
	FIRENET_EVENT_GET_PROFILE_COMPLETE,
	//! Event when get profile failed
	FIRENET_EVENT_GET_PROFILE_FAILED,
	//! Event when get shop complete
	FIRENET_EVENT_GET_SHOP_COMPLETE,
	//! Event when get shop failed
	FIRENET_EVENT_GET_SHOP_FAILED,
	//! Event when buy item complete
	FIRENET_EVENT_BUY_ITEM_COMPLETE,
	//! Event when buy item failed
	FIRENET_EVENT_BUY_ITEM_FAILED,
	//! Event when remove item complete
	FIRENET_EVENT_REMOVE_ITEM_COMPLETE,
	//! Event when remove item failed
	FIRENET_EVENT_REMOVE_ITEM_FAILED,
	//! Event when send invite complete
	FIRENET_EVENT_SEND_INVITE_COMPLETE,
	//! Event when send invite failed
	FIRENET_EVENT_SEND_INVITE_FAILED,
	//! Event when add friend complete
	FIRENET_EVENT_ADD_FRIEND_COMPLETE,
	//! Event when add friend failed
	FIRENET_EVENT_ADD_FRIEND_FAILED,
	//! Event when remove friend complete
	FIRENET_EVENT_REMOVE_FRIEND_COMPLETE,
	//! Event when remove friend failed
	FIRENET_EVENT_REMOVE_FRIEND_FAILED,	

	// ~Special events

	//! Event when client recived console command
	FIRENET_EVENT_CONSOLE_COMMAND_RECIVED,
	//! Event when client recived server message
	FIRENET_EVENT_SERVER_MESSAGE_RECIVED,
	//! Event when client recived game server information
	FIRENET_EVENT_GAME_SERVER_INFO_RECIVED,

	//! Event when start connection to game server
	FIRENET_EVENT_GAME_SERVER_START_CONNECTION,
	//! Event when success connected to game server
	FIRENET_EVENT_GAME_SERVER_CONNECTED,
	//! Event when connection to game server failed
	FIRENET_EVENT_GAME_SERVER_CONNECTION_ERROR,
	//! Event when connection with game server lost
	FIRENET_EVENT_GAME_SERVER_DISCONNECTED,
};

struct SFireNetEventArgs
{
	std::vector<int> mInt;
	std::vector<const char*> mString;
	std::vector<float> mFloat;

	inline void AddInt(int i)
	{
		mInt.insert(mInt.begin(), i);
	}

	inline void AddString(const char* string)
	{
		mString.insert(mString.begin(), string);
	}

	inline void AddFloat(float f)
	{
		mFloat.insert(mFloat.begin(), f);
	}

	int GetInt()
	{
		auto it = mInt.begin();

		if (it != mInt.end())
		{
			int result = (*it);
			mInt.erase(it);

			return result;
		}

		return 0;
	}

	const char* GetString()
	{
		auto it = mString.begin();

		if (it != mString.end())
		{
			const char* result = (*it);
			mString.erase(it);

			return result;
		}

		return nullptr;
	}

	float GetFloat()
	{
		auto it = mFloat.begin();

		if (it != mFloat.end())
		{
			float result = (*it);
			mFloat.erase(it);

			return result;
		}

		return 0;
	}
};

struct IFireNetListener
{
	virtual void OnFireNetEvent(EFireNetEvents event, SFireNetEventArgs& args) = 0;
};