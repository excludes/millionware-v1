#include "jump_stats.hpp"

#include "pred.hpp"
#include "../input/input.hpp"

#include "../renderer/renderer.hpp"
#include "../../source engine/math/point.hpp"

#include "../../engine/utilities/config.hpp"

#include "movement.hpp"

void jump_stats::update_unpredicted_info( int flags )
{
	stat_info.m_unpredicted_flags = flags;
}

void jump_stats::update_predicted_info( int flags )
{
	stat_info.m_predicted_flags = flags;
}

void jump_stats::update_info( c_usercmd* cmd )
{
	if ( !*config::get<bool>( crc( "misc:jumpstats" ) ) )
	{
		return;
	}

	player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local || !cmd )
	{
		return;
	}

	// unpredicted player's flags are 1 tick behind
	stat_info.m_bhopped = ( stat_info.m_unpredicted_flags & fl_onground ) && !( stat_info.m_predicted_flags & fl_onground );
	stat_info.m_bhopping = stat_info.m_consecutive_ticks_in_air > 0;

	if ( stat_info.m_predicted_flags & fl_onground )
	{
		stat_info.m_last_tick_on_ground = interfaces::globals->tick_count;
	}
	else
	{
		stat_info.m_last_tick_in_air = interfaces::globals->tick_count;
	}

	if ( stat_info.m_predicted_flags & fl_onground )
	{
		stat_info.m_consecutive_ticks_on_ground++;
		if ( stat_info.m_consecutive_ticks_on_ground > 1 )
		{
			stat_info.m_consecutive_ticks_in_air = 0;
		}
	}
	else
	{
		stat_info.m_consecutive_ticks_in_air++;
		stat_info.m_consecutive_ticks_on_ground = 0;
	}

	stat_info.m_was_in_air = stat_info.m_consecutive_ticks_on_ground > 1 && ( ( stat_info.m_last_tick_on_ground > stat_info.m_last_tick_in_air + 1 ) && ( stat_info.m_last_tick_on_ground - stat_info.m_last_tick_in_air ) < 25 )
		&& stat_info.m_last_tick_in_air > 0;

	if ( stat_info.m_bhopping )
	{
		stat_info.m_highest_velocity = max( local->velocity( ).length_2d( ), stat_info.m_highest_velocity );
	}

	if ( stat_info.m_was_in_air )
	{
		if ( ( stat_info.m_predicted_flags & fl_onground ) && stat_info.m_consecutive_ticks_on_ground < 3 )
		{
			stat_info.m_landed_pos = local->abs_origin( );
			stat_info.m_long_jump = fabs( ( stat_info.m_landed_pos - stat_info.m_take_off_pos ).length_2d( ) );
			announce( stat_info.m_long_jump );
		}
	}
	else if ( !stat_info.m_was_in_air && ( stat_info.m_predicted_flags & fl_onground ) && stat_info.m_consecutive_ticks_on_ground > 1 || stat_info.m_jump_bugged )
	{
		stat_info.m_take_off_velocity = local->velocity( ).length_2d( );
		stat_info.m_take_off_pos = local->abs_origin( );
		stat_info.m_landed_pos = vec3( 0, 0, 0 );
		stat_info.m_long_jump = 0.f;
		stat_info.m_highest_velocity = 0;
	}

	stat_info.m_fell_too_much = ( stat_info.m_take_off_pos.z - stat_info.m_landed_pos.z ) > 18.01f && !( stat_info.m_predicted_flags & fl_ducking ) && !( stat_info.m_unpredicted_flags & fl_ducking );
	/*stat_info.m_jump_bugged = movement::jumpbugged && stat_info.m_consecutive_ticks_in_air != 0;

	if ( stat_info.m_jump_bugged ) {
		announce( 0.f, true );
	}*/

	if ( stat_info.m_bhopping && stat_info.m_bhopped || stat_info.m_jump_bugged )
	{
		stat_info.m_take_off_velocity = local->velocity( ).length_2d( );
		stat_info.m_take_off_pos = local->abs_origin( );
		stat_info.m_landed_pos = vec3( 0, 0, 0 );
		stat_info.m_long_jump = 0.f;
		stat_info.m_highest_velocity = 0;
	}

	if ( stat_info.m_consecutive_ticks_on_ground > 1 )
	{
		stat_info.m_take_off_pos = local->abs_origin( );
		stat_info.m_landed_pos = vec3( 0, 0, 0 );
		stat_info.m_long_jump = 0.f;
		stat_info.m_highest_velocity = 0;
	}

	if ( ( stat_info.m_predicted_flags & fl_onground ) )
	{

		// successful
		stat_info.m_successful_strafes.first.first = 0; // left strafes
		stat_info.m_successful_strafes.second.first = false;

		stat_info.m_successful_strafes.first.second = 0;// right strafes
		stat_info.m_successful_strafes.second.second = false;

		// total
		stat_info.m_attempted_strafes.first.first = 0; // left strafes
		stat_info.m_attempted_strafes.second.first = false;

		stat_info.m_attempted_strafes.first.second = 0;// right strafes
		stat_info.m_attempted_strafes.second.second = false;
		return;
	}

	// can't strafe cos you're holding down both A and D
	if ( !( ( cmd->buttons & in_moveleft ) && ( cmd->buttons & in_moveright ) ) )
	{
		// tried to strafe
		if ( ( cmd->buttons & in_moveleft ) && !stat_info.m_attempted_strafes.second.first )
		{
			stat_info.m_attempted_strafes.first.first += 1;
		}

		if ( ( cmd->buttons & in_moveright ) && !stat_info.m_attempted_strafes.second.second )
		{
			stat_info.m_attempted_strafes.first.second += 1;
		}
	}

	// managed to sync the left strafe
	if ( cmd->mouse_dx < 0 )
	{
		if ( ( cmd->buttons & in_moveleft ) && !stat_info.m_successful_strafes.second.first )
		{
			stat_info.m_successful_strafes.first.first += 1;
		}
	}
	// managed to sync the right strafe
	else if ( cmd->mouse_dx > 0 )
	{
		if ( ( cmd->buttons & in_moveright ) && !stat_info.m_successful_strafes.second.second )
		{
			stat_info.m_successful_strafes.first.second += 1;
		}
	}

	static int old_successful_left_strafes = stat_info.m_successful_strafes.first.first;
	static int old_successful_right_strafes = stat_info.m_successful_strafes.first.second;

	if ( old_successful_left_strafes != stat_info.m_successful_strafes.first.first )
	{
		// already incremented left strafes, don't do it again!
		stat_info.m_successful_strafes.second.first = true;
		stat_info.m_successful_strafes.second.second = false;

		stat_info.m_last_strafe_increment = interfaces::globals->cur_time;

		old_successful_left_strafes = stat_info.m_successful_strafes.first.first;
	}

	if ( old_successful_right_strafes != stat_info.m_successful_strafes.first.second )
	{
		// already incremented right strafes, don't do it again!
		stat_info.m_successful_strafes.second.second = true;
		stat_info.m_successful_strafes.second.first = false;

		stat_info.m_last_strafe_increment = interfaces::globals->cur_time;

		old_successful_right_strafes = stat_info.m_successful_strafes.first.second;
	}

	static int old_failed_left_strafes = stat_info.m_attempted_strafes.first.first;
	static int old_failed_right_strafes = stat_info.m_attempted_strafes.first.second;

	if ( old_failed_left_strafes != stat_info.m_attempted_strafes.first.first )
	{
		// already incremented left strafes, don't do it again!
		stat_info.m_attempted_strafes.second.first = true;
		stat_info.m_attempted_strafes.second.second = false;

		stat_info.m_last_strafe_increment = interfaces::globals->cur_time;

		old_failed_left_strafes = stat_info.m_attempted_strafes.first.first;
	}

	if ( old_failed_right_strafes != stat_info.m_attempted_strafes.first.second )
	{
		// already incremented right strafes, don't do it again!
		stat_info.m_attempted_strafes.second.second = true;
		stat_info.m_attempted_strafes.second.first = false;

		stat_info.m_last_strafe_increment = interfaces::globals->cur_time;

		old_failed_right_strafes = stat_info.m_attempted_strafes.first.second;
	}

	if ( fabs( interfaces::globals->cur_time - stat_info.m_last_strafe_increment ) > 0.4f )
	{
		// successful
		stat_info.m_successful_strafes.first.first = 0; // left strafes
		stat_info.m_successful_strafes.second.first = false;

		stat_info.m_successful_strafes.first.second = 0;// right strafes
		stat_info.m_successful_strafes.second.second = false;

		// total
		stat_info.m_attempted_strafes.first.first = 0; // left strafes
		stat_info.m_attempted_strafes.second.first = false;

		stat_info.m_attempted_strafes.first.second = 0;// right strafes
		stat_info.m_attempted_strafes.second.second = false;
	}

	stat_info.m_total_successful_strafes = stat_info.m_successful_strafes.first.first + stat_info.m_successful_strafes.first.second;
	stat_info.m_total_attempted_strafes = stat_info.m_attempted_strafes.first.first + stat_info.m_attempted_strafes.first.second;
}

const char* jump_stats::get_color_by_distance( float lj )
{
	if ( lj <= 210.f )
	{
		return ( "\x08" );
	}
	else if ( lj > 210.f && lj <= 230.f )
	{
		return ( "\x04" );
	}
	else if ( lj > 230.f && lj <= 235.f )
	{
		return ( "\x0C" );
	}
	else if ( lj > 235.f && lj <= 240.f )
	{
		return ( "\x02" );
	}
	else if ( lj > 240.f && lj >= 245.0f )
	{
		return ( "\x09" );
	}
}

void jump_stats::announce( float lj, bool jb )
{
	if ( !*config::get<bool>( crc( "misc:jumpstats" ) ) )
	{
		return;
	}

	float sync = float( stat_info.m_total_attempted_strafes == 0 ? 0.f : ( ( float )stat_info.m_total_successful_strafes / ( float )stat_info.m_total_attempted_strafes ) * 100.f );

	if ( jb || lj >= 255.f )
	{
		static bool announced = false;
		static float last_announced = interfaces::globals->tick_count;

		if ( !announced )
		{
			interfaces::hud_chat->chat_print( xor ( "[" "\x0C" "millionware" "\x01" "]" "\x08" " jump failed [" "\x02" "jump bug" "\x08" "]" ) );
			last_announced = interfaces::globals->tick_count;
			announced = true;
		}

		if ( interfaces::globals->tick_count - last_announced > 5 )
		{
			announced = false;
		}
	}
	else if ( sync == 0 || stat_info.m_total_successful_strafes == 0 && lj > 100.f )
	{
		static bool announced = false;
		static float last_announced = interfaces::globals->tick_count;

		if ( !announced )
		{
			interfaces::hud_chat->chat_print( xor ( "[" "\x0C" "millionware" "\x01" "]" "\x08" " jump failed [" "\x02" "invalid" "\x08" "]" ) );
			last_announced = interfaces::globals->tick_count;
			announced = true;
		}

		if ( interfaces::globals->tick_count - last_announced > 5 )
		{
			announced = false;
		}
	}
	else
	{
		// gay
		char percent[ 5 ];
		strcpy( percent, "%%" );

		if ( lj >= 180.f )
		{
			interfaces::hud_chat->chat_print( xor ( "[" "\x0C" "millionware" "\x01" "]" "%s" " LJ: %.2f units " "\x08" "[" "\x06" "%i " "\x08" "strafes | " "\x06" "%i " "\x08" "pre | " "\x06" "%i " "\x08" "max | " "\x06" "%.f%s " "\x08" "sync]" ),
											  get_color_by_distance( lj ), lj, stat_info.m_total_successful_strafes, stat_info.m_take_off_velocity, stat_info.m_highest_velocity, sync, percent );
		}
	}
}