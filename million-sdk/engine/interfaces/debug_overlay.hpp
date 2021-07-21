#pragma once
#include "../../source engine/math/point.hpp"

class vec3_t;
class iv_debug_overlay
{
public:
	bool world_to_screen( const vec3_t& in, vec3_t& out )
	{
		using original_fn = int( __thiscall* )( iv_debug_overlay*, const vec3_t&, vec3_t& );
		int return_value = ( *( original_fn** )this )[ 13 ]( this, in, out );
		return static_cast< bool >( return_value != 1 );
	}

	bool world_to_screen( const vec3_t& in, point_t& out )
	{
		vec3_t out_3d{};
		const auto ret_val = world_to_screen( in, out_3d );

		out = { ( int )out_3d.x, ( int )out_3d.y };

		return ret_val;
	}
};