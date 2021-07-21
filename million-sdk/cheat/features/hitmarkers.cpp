#include "hitmarkers.hpp"

#include "../renderer/renderer.hpp"
#include "../../engine/utilities/config.hpp"

void hitmarkers::update( )
{
	hit_info.m_alpha = 1.0f;
	hit_info.m_hurt_time = interfaces::globals->cur_time;

	int bruh = *config::get<int>( crc( "esp:misc:hitsound_type" ) );
	std::string str;
	if ( bruh == 0 )
	{
		str = ( xor ( "playvol survival/money_collect_05.wav " ) );
	}
	// xd
	else if ( bruh == 1 )
	{
		str = ( xor ( "playvol buttons/arena_switch_press_02.wav " ) );
	}
	else if (bruh == 2)
	{
		str = (xor ("playvol custom.wav "));
	}

	str += std::to_string( *config::get<float>( crc( "esp:misc:hitsound_volume" ) ) / 100.f );
	interfaces::engine->execute_cmd( str.c_str( ) );
}

void hitmarkers::draw( )
{
	if ( interfaces::globals->cur_time - hit_info.m_hurt_time >= 0.5f )
	{
		hit_info.m_alpha -= ( ( 1.0 / 0.5f ) * interfaces::globals->frame_time );
	}

	if ( hit_info.m_alpha <= 0.f )
	{
		hit_info.m_alpha = 0.f;
		return;
	}

	// draw hitmarker shibble here!!
}