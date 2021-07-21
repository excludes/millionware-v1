#include "vector3d.hpp"
#include <cmath>

vec3_t::vec3_t( void )
{
	x = y = z = 0.f;
}

vec3_t::vec3_t( float fx, float fy, float fz )
{
	x = fx;
	y = fy;
	z = fz;
}

vec3_t::~vec3_t( void )
{

};

void vec3_t::init( )
{
	x = y = z = 0.f;
}

void vec3_t::clamp( void )
{
	// horrible idea if the angle is enormous
	// it doesnt happen if your code is not shit (this post was sponsored by duxe and alpha corp)
	while ( this->z < -89.f )
		this->z += 89.f;

	if ( this->z > 89.f )
		this->z = 89.f;

	while ( this->y < -180.f )
		this->y += 360.f;

	while ( this->y > 180.f )
		this->y -= 360.f;

	this->z = 0.f;
}

void vec3_t::normalize( void )
{
	auto x_rev = this->x / 360.f;
	if ( this->x > 180.f || this->x < -180.f )
	{
		x_rev = abs( x_rev );
		x_rev = round( x_rev );

		if ( this->x < 0.f )
			this->x = ( this->x + 360.f * x_rev );

		else
			this->x = ( this->x - 360.f * x_rev );
	}

	auto y_rev = this->y / 360.f;
	if ( this->y > 180.f || this->y < -180.f )
	{
		y_rev = abs( y_rev );
		y_rev = round( y_rev );

		if ( this->y < 0.f )
			this->y = ( this->y + 360.f * y_rev );

		else
			this->y = ( this->y - 360.f * y_rev );
	}

	auto z_rev = this->z / 360.f;
	if ( this->z > 180.f || this->z < -180.f )
	{
		z_rev = abs( z_rev );
		z_rev = round( z_rev );

		if ( this->z < 0.f )
			this->z = ( this->z + 360.f * z_rev );

		else
			this->z = ( this->z - 360.f * z_rev );
	}
}

vec3_t vec3_t::normalized( void )
{
	vec3_t vec( *this );
	vec.normalize( );

	return vec;
}

float vec3_t::length( void )
{
	return sqrt( x * x + y * y + z * z );
}

float vec3_t::length_2d( void )
{
	return sqrt( x * x + y * y );
}

float vec3_t::length_sqr( void )
{
	return ( x * x + y * y + z * z );
}

float vec3_t::dot( const vec3_t other )
{
	return ( x * other.x + y * other.y + z * other.z );
}

float vec3_t::dist_to( const vec3_t vec )
{
	return ( *this - vec ).length( );
}