#include "movement.hpp"
#include "../../engine/utilities/config.hpp"
#include "../input/input.hpp"
#include "../hooks/hooks.hpp"
#include "../renderer/renderer.hpp"

#include "../../engine/utilities/xorstring.hpp"

namespace movement
{
	bool jumpbugged;

	void pre_prediction( c_usercmd* cmd, player_t* local, int pre_flags )
	{
		if ( *config::get<bool>( crc( "misc:infinite_duck" ) ) )
		{
			cmd->buttons |= in_bullrush;
		}

		if ( *config::get<bool>( crc( "misc:bhop" ) ) )
			if ( !input::hold( *config::get<int>( crc( "misc:jb:key" ) ) ) && local->move_type( ) != 9 )
				if ( !( pre_flags & ( fl_onground ) ) && cmd->buttons & ( in_jump ) )
				{
					cmd->buttons &= ~( in_jump );
				}
	}

	void post_prediction( c_usercmd* cmd, player_t* local, int pre_flags, int post_flags )
	{
		if ( *config::get<bool>( crc( "misc:jb" ) ) )
		{
			if ( input::hold( *config::get<int>( crc( "misc:jb:key" ) ) ) )
			{
				hooks::b_predicting = true;
				if ( !( pre_flags & ( 1 << 0 ) ) && post_flags & ( 1 << 0 ) )
				{
					cmd->buttons |= in_duck;
				}

				if ( post_flags & fl_onground )
				{
					cmd->buttons &= ~in_jump;
					jumpbugged = true;
				}
			}
		}

		if ( *config::get<bool>( crc( "misc:ej" ) ) )
		{
			if ( input::hold( *config::get<int>( crc( "misc:ej:key" ) ) ) )
			{
				if ( pre_flags & ( 1 << 0 ) && !( post_flags & 1 << 0 ) )
				{
					cmd->buttons |= in_jump;
				}
			}
			if ( *config::get<bool>( crc( "misc:lj" ) ) )
			{
				// kinda weird, dont know why we need a seperate check. Prob because of tickrate. anyways you could remove this check and make a lj on every jump feature :sunglasses:
				if ( input::hold( *config::get<int>( crc( "misc:ej:key" ) ) ) )
				{
					if ( !( post_flags & 1 << 0 ) )
					{
						cmd->buttons |= in_duck;
					}
				}
			}
		}

		if ( *config::get<bool>( crc( "misc:eb" ) ) )
		{
			if ( !( pre_flags & ( 1 << 0 ) ) && post_flags & ( 1 << 0 ) && input::hold( *config::get<int>( crc( "misc:eb:key" ) ) ) )
			{
				cmd->buttons |= ( in_duck );
			}
		}
		//this is basically just the exact same as eb assist but you dont hold the key lOl
		if (*config::get<bool>(crc("misc:stathelper")))
		{
			if (!(pre_flags & (1 << 0)) && post_flags & (1 << 0))
			{
				cmd->buttons |= (in_duck);
				cmd->buttons |= (in_duck);
			}
		}
	}

	void draw( )
	{
		static float last_vel = 0.f;
		static int tick_prev = 0;

		static float take_off = 0.f;
		static float take_off_time = 0.f;

		static bool last_on_ground = false;

		point screen_size; interfaces::engine->get_screen_size( screen_size.x, screen_size.y );
		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

		if ( local )
		{
			float vel = floorf( min( 10000, local->velocity( ).length_2d( ) + 0.5 ) );
			bool on_ground = ( local->flags( ) & fl_onground );
			if ( last_on_ground && !on_ground )
			{
				take_off = vel;
				take_off_time = interfaces::globals->cur_time + 2.f;
			}

			if ( *config::get<bool>( crc( "misc:vel" ) ) )
			{
				color c = vel == last_vel ? color( 255, 199, 89 ) : vel < last_vel ? color( 255, 119, 119 ) : color( 30, 255, 109 );

				bool should_draw_takeoff = ( !on_ground || ( take_off_time > interfaces::globals->cur_time ) ) && *config::get<bool>( crc( "misc:vel:takeoff" ) );

				render::text( point( screen_size.x / 2, screen_size.y - 100 ), fonts::velocity_indicator, font_centered_x | font_dropshadow, c, should_draw_takeoff ? L"%.0f (%.0f)\n" : L"%.0f", vel, take_off );
			}

			if ( *config::get<bool>( crc( "misc:jb:indicator" ) ) && *config::get<bool>( crc( "misc:jb" ) ) && input::hold( *config::get<int>( crc( "misc:jb:key" ) ) ) )
			{
				render::text( point( screen_size.x / 2, screen_size.y - 150 ), fonts::other_indicators, font_centered_x | font_dropshadow, jumpbugged ? color( 30, 255, 109 ) : color( 255, 255, 255 ), xor ( L"jb\n" ) );
			}
			else
			{
				jumpbugged = false;
			}

			if ( *config::get<bool>( crc( "misc:eb:indicator" ) ) && *config::get<bool>( crc( "misc:eb" ) ) && input::hold( *config::get<int>( crc( "misc:eb:key" ) ) ) )
			{
				render::text( point( screen_size.x / 2, screen_size.y - 170 ), fonts::other_indicators, font_centered_x | font_dropshadow, color( 255, 255, 255 ), xor ( L"eb\n" ) );
			}

			if ( *config::get<bool>( crc( "misc:ej:indicator" ) ) && *config::get<bool>( crc( "misc:ej" ) ) && input::hold( *config::get<int>( crc( "misc:ej:key" ) ) ) )
			{
				render::text( point( screen_size.x / 2, screen_size.y - 190 ), fonts::other_indicators, font_centered_x | font_dropshadow, color( 255, 255, 255 ), xor ( L"ej\n" ) );
			}

			if ( tick_prev + 5 < interfaces::globals->tick_count )
			{
				last_vel = vel;
				tick_prev = interfaces::globals->tick_count;
			}

			last_on_ground = on_ground;

			if ( jumpbugged && ( !on_ground || ( take_off_time > interfaces::globals->cur_time ) ) )
			{
				jumpbugged = false;
			}
		}
		else
		{
			last_vel = 0.f;
			tick_prev = 0;
			take_off = 0.f;
			take_off_time = 0.f;
		}
	}
}