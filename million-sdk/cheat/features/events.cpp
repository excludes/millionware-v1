#include "events.hpp"

#include <algorithm>
#include <unordered_map>

#include "hitmarkers.hpp"
#include "skins.hpp"
#include "../../engine/utilities/config.hpp"

// static xdddd
static c_game_events events{};
void c_game_events::init( )
{
	interfaces::game_event_manager->add_listener_global( &events, false );
}

void c_game_events::revert( )
{
	interfaces::game_event_manager->remove_listener( &events );
}

// use a map -paracord
const char* hitgroup_to_str( int bruh )
{
	switch ( bruh )
	{
	case hitgroup_generic: return ( "body" ); break;
	case hitgroup_head: return ( "head" ); break;
	case hitgroup_chest: return ( "chest" ); break;
	case hitgroup_stomach: return ( "stomach" ); break;
	case hitgroup_leftarm: return ( "left arm" ); break;
	case hitgroup_rightarm: return ( "right arm" ); break;
	case hitgroup_leftleg: return ( "left leg" ); break;
	case hitgroup_rightleg: return ( "right leg" ); break;
	case hitgroup_gear: return ( "gear" ); break;
	}

	return xor ( "xd" );
}

bool is_knife_string( const char* str )
{
	return strstr( str, xor ( "knife" ) );
}

void c_game_events::fire_game_event( i_game_event* event )
{

	if ( !strcmp( event->get_name( ), xor ( "player_hurt" ) ) )
	{
		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

		int dmg_health = event->get_int( xor ( "dmg_health" ) );

		auto attacker = interfaces::entity_list->get<player_t>( interfaces::engine->get_player_for_user_id( event->get_int( xor ( "attacker" ) ) ) );
		auto target = interfaces::entity_list->get<player_t>( interfaces::engine->get_player_for_user_id( event->get_int( xor ( ( "userid" ) ) ) ) );

		if ( local && attacker && target && attacker == local && target->team( ) != local->team( ) )
		{
			if ( *config::get<bool>( crc( "esp:misc:hurtinfo" ) ) )
			{
				interfaces::hud_chat->chat_print( xor ( "[" "\x0C" "millionware" "\x08" "]" " hurt %s in the %s for %i [%i remaining]" ),
												  target->info( ).name, hitgroup_to_str( event->get_int( xor ( "hitgroup" ) ) ),
												  event->get_int( xor ( "dmg_health" ) ), event->get_int( xor ( "health" ) ) );
			}

			if ( *config::get<bool>( crc( "esp:misc:hitsound" ) ) )
			{
				hitmarkers::update( );
			}
		}

	}
	if ( !strcmp( event->get_name( ), xor ( "player_death" ) ) )
	{
		auto attacker = interfaces::entity_list->get<player_t>( interfaces::engine->get_player_for_user_id( event->get_int( xor ( "attacker" ) ) ) );
		if ( attacker && attacker->index( ) == interfaces::engine->get_local_player( ) )
		{
			if ( is_knife_string( event->get_string( "weapon" ) ) )
			{
				event->set_string( "weapon", skins::knifes::update_kill_icons( ) );
			}
		}
	}
	if ( !strcmp( event->get_name( ), xor( "round_freeze_end" ) ) ) {
		utils::engine::round_flags = 0;
	}
	if ( !strcmp( event->get_name( ), xor( "round_start" ) ) || !strcmp( event->get_name( ), xor( "client_disconnect" ) ) ) {
		utils::engine::round_flags = 1;
	}

}

// ?
int c_game_events::get_debug_id( )
{
	return 42;
}