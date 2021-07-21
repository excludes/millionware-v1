// fuck you duxe u pasting fucking retard i want to fucking slap your fucking mother so god damn hard for not drowning you at birth you stupid dumb fucking rat bastard im going to literally shut your fucking power off and then make ur fridge run down the street

#include "triggerbot.hpp"

#include "../../engine/utilities/config.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "../input/input.hpp"

#include "aimbot.hpp"

template<class T>
T get_trigger_config( const char* bruh )
{
	auto nice = [ & ]( )-> const char* {
		switch ( aimbot::get_active_weapon_type( ).first )
		{
		case 2: return aimbot::get_active_weapon_type( ).second ? ":heavy_pistol" : ":pistol"; break;
		case 4: case 7: return ":rifle"; break;
		case 5: return ":other"; break;
		case 6: return ":sniper"; break;
		case 3: return ":smg"; break;
		}
	};

	return *config::get<T>( crc( std::string( bruh ).append( nice( ) ).data( ) ) );
}

void triggerbot::run( c_usercmd* cmd )
{
	if ( !get_trigger_config<bool>( xor ( "ass:trigger:enabled" ) ) )
	{
		return;
	}

	if ( !input::hold( get_trigger_config<int>( xor ( "ass:trigger:key:value" ) ) ) && get_trigger_config<bool>( xor ( "ass:trigger:key:enabled" ) ) )
	{
		return;
	}

	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local )
	{
		return;
	}

	if ( !local->alive( ) )
	{
		return;
	}

	auto weapon = local->active_weapon( );
	if ( !weapon )
	{
		return;
	}

	auto weapon_data = weapon->weapon_data( );
	if ( !weapon_data )
	{
		return;
	}

	static bool should_set_target_time = true;
	static float last_valid_target_time = 0.f;

	vec3_t src = local->eye_pos( );
	vec3_t ang = cmd->view_angles;
	vec3_t dst;

	utils::math::angle_vectors( ang, &ang );

	ang *= weapon_data->range;
	dst = src + ang;

	trace_t trace;
	trace_filter filter;
	filter.skip = local;

	ray_t ray;
	ray.initialize( src, dst );

	interfaces::trace->trace_ray( ray, 0x46004003, &filter, &trace );

	auto entity = reinterpret_cast< entity_t* >( trace.entity );
	if ( !entity )
	{
		return;
	}

	if ( !entity->is_player( ) )
	{
		should_set_target_time = true;
		last_valid_target_time = 0.f;
		return;
	}
	else
	{
		if ( should_set_target_time )
		{
			last_valid_target_time = interfaces::globals->cur_time;
			should_set_target_time = false;
		}
	}

	auto player = reinterpret_cast< player_t* >( entity );
	auto valid_player = [ & ]( ) {
		if ( !player )
			return false;

		if ( !player->alive( ) )
			return false;

		if ( player->dormant( ) )
			return false;

		if ( player->team( ) == local->team( ) )
			return false;

		return !( player->has_gun_game_immunity( ) );
	};

	if ( trace.hitGroup >= 0 && trace.hitGroup <= 7 )
	{
		if ( valid_player( ) )
		{
			float delta = interfaces::globals->cur_time - last_valid_target_time;
			if ( delta > get_trigger_config<float>( xor ( "ass:trigger:delay" ) ) )
			{
				cmd->buttons |= in_attack;
			}
		}
	}
}