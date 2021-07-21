#pragma once
#include "../../source engine/sdk.hpp"

namespace movement
{
	extern bool jumpbugged;

	void pre_prediction( c_usercmd* cmd, player_t* local, int pre_flags );
	void post_prediction( c_usercmd* cmd, player_t* local, int pre_flags, int post_flags );

	void draw( );
}