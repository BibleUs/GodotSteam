
#ifndef GODOTSTEAM_H
#define GODOTSTEAM_H

#include <steam/steam_api.h>

#include "object.h"
#include "scene/resources/texture.h" // avatars
// #include "dictionary.h" // contains array.h as well

#include "godotsteam_leaderboard.h"


class Steam: public Object
{
public:
	enum {
		ERR_NO_CLIENT=2, ERR_NO_CONNECTION=3,
		
		AVATAR_SMALL=0, AVATAR_MEDIUM, AVATAR_LARGE
	};
	static Steam* get_singleton();
	Steam();
	~Steam();
	
	int init();
	String get_userdata_path();
	// user
	int get_steamid();
	String get_username(int steamId=0); // 0 - current user
	// stats / achievements
	void unlock_achiv(const String& aName);
	bool has_achiv(const String& aName);
	void reset_achiv(const String& aName);
	
	void set_stat_i(const String& sName, int sVal);
	int get_stat_i(const String& sName);
	void set_stat_f(const String& sName, float sVal);
	float get_stat_f(const String& sName);
	void sync_stats();
	
	void load_leaderboard(const String& lName);
	// other
	bool has_dlc(int appId);
	void load_avatar(int size=AVATAR_MEDIUM);
	
	// not for GDScript
	Image draw_avatar(int size, uint8* buffer);
	CSteamID create_steamid( uint32 steamId, int accountType=-1 );
	

protected:
	static void _bind_methods();
	static Steam* singleton;

private:
	
	STEAM_CALLBACK(Steam, _avatar_loaded, AvatarImageLoaded_t );
	// STEAM_CALLBACK(Steam, _leaderboard_loaded, LeaderboardFindResult_t );
	CCallResult<Steam, LeaderboardFindResult_t> callResultFindLeaderboard;
		void _leaderboard_loaded(LeaderboardFindResult_t *callData, bool bIOFailure);
	
	
	void run_callbacks() { SteamAPI_RunCallbacks(); }

	bool isInitSuccess;
	OBJ_TYPE(Steam, Object);
	OBJ_CATEGORY("Steam");
};
#endif


