#pragma once
#include <iostream> 
#include <algorithm>
#include "../../source engine/math/vector3d.hpp"

namespace utils::math
{
	// pi constants.
	constexpr float pi{ 3.14159265359f };
	constexpr float rad_per_deg{ 0.01745329251f };
	constexpr float deg_per_rad{ 57.2957795131f };

	__forceinline float rad_to_deg( float x )
	{
		return x * deg_per_rad;
	}

	__forceinline float deg_to_rad( float x )
	{
		return x * rad_per_deg;
	}

	__forceinline void sin_cos( float a, float* s, float* c )
	{
		*s = sin( a );
		*c = cos( a );
	}

	__forceinline void vector_angles( vec3& forward, vec3& angles )
	{
		if ( forward.x == 0.f && forward.y == 0.f )
		{
			angles.x = ( forward.z > 0.f ) ? 270.f : 90.f;
			angles.y = 0.f;
		}
		else
		{
			angles.x = -rad_to_deg( atan2( -forward.z, forward.length_2d( ) ) );
			angles.y = rad_to_deg( atan2( forward.y, forward.x ) );

			if ( angles.y > 90.f ) angles.y -= 180.f;
			else if ( angles.y < 90.f ) angles.y += 180.f;
			else if ( angles.y == 90.f ) angles.y = 0.f;
		}

		angles.z = 0.f;
	}

	__forceinline vec3 calc_angle( const vec3& src, const vec3& dst )
	{
		vec3 angles;
		vec3 delta = src - dst;

		vector_angles( delta, angles );

		angles.normalize( );

		return angles;
	}

	__forceinline float get_fov( vec3 local, vec3 point, vec3 view )
	{
		vec3 angle = calc_angle( local, point );
		auto dif = view - angle;
		auto norm = dif;
		norm.clamp( );
		auto len = norm.length_sqr( );

		//printf("%f, %f, %f %f\n", angle.y, dif.y, norm.y, len);

		return len;
	}

	// to however the fuck made this: you don't need to normalize angles returned from stl math functions since they have a fixed period -paracord
	__forceinline void normalize_angles( vec3& angles )
	{
		for ( auto i = 0; i < 3; i++ )
		{
			while ( angles[ i ] < -180.f ) angles[ i ] += 360.f;
			while ( angles[ i ] > 180.f ) angles[ i ] -= 360.f;
		}
	}

	__forceinline void angle_vectors( const vec3& angles, vec3_t* forward )
	{
		float sp, sy, cp, cy;

		sin_cos( deg_to_rad( angles.x ), &sy, &cy );
		sin_cos( deg_to_rad( angles.y ), &sp, &cp );

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	__forceinline float get_fov( const vec3& view_angle, const vec3& aim_angle )
	{
		vec3_t ang, aim;

		angle_vectors( view_angle, &aim );
		angle_vectors( aim_angle, &ang );

		return rad_to_deg( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
	}

	__forceinline void vector_transform( vec3_t& in1, const matrix_t& in2, vec3_t& out )
	{
		out[ 0 ] = in1.dot( in2[ 0 ] ) + in2[ 0 ][ 3 ];
		out[ 1 ] = in1.dot( in2[ 1 ] ) + in2[ 1 ][ 3 ];
		out[ 2 ] = in1.dot( in2[ 2 ] ) + in2[ 2 ][ 3 ];
	}

	__forceinline void smooth_angle( vec3_t& angle, float ptr, const vec3_t& viewangles )
	{
		vec3_t delta = angle - viewangles;
		delta.clamp( );

		float smooth = powf( ptr / 50.f, 0.4f );

		smooth = ( ( 0.99f ) < ( smooth ) ? ( 0.99f ) : ( smooth ) );
		vec3_t to_change;

		// slow end
		// to_change = delta - delta * smooth;
		float coeff = ( 1.0f - smooth ) / delta.length( ) * 4.f;

		// fast end
		// coeff = powf( coeff, 2.f ) * 10.f;
		coeff = ( ( 1.f ) < ( coeff ) ? ( 1.f ) : ( coeff ) );

		to_change = delta * coeff;

		angle = viewangles + to_change;
	}
}