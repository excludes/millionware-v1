#pragma once

#include "../../source engine/sdk.hpp"

class c_game_events : public i_game_event_listener
{
public:
	// static xdddd
	static void init( );
	static void revert( );

	void fire_game_event( i_game_event* event ) override;
	int get_debug_id( ) override;
};