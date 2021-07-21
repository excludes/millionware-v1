#pragma once

#include "../../source engine/sdk.hpp"

namespace aimbot
{
	extern int aimbot_target;
	std::pair<int, bool> get_active_weapon_type( );

	int find_target( const vec2_t& recoil );
	int find_hitbox( player_t* player );

	void run( c_usercmd* cmd );
}