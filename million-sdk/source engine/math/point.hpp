#pragma once
struct point_t
{
	int x, y;

	//point_t( ) : x( 0 ), y( 0 ) { };
	//point_t( int _x, int _y ) : x( _x ), y( _y ) { };

	point_t( )
	{}

	point_t( int _x, int _y )
	{
		x = _x;
		y = _y;
	}

	point_t operator+( const point_t& p2 )
	{
		return point_t( this->x + p2.x, this->y + p2.y );
	}

	point_t operator-( const point_t& p2 )
	{
		return point_t( this->x - p2.x, this->y - p2.y );
	}

	point_t operator+( int a )
	{
		return point_t( this->x + a, this->y + a );
	}

	point_t operator-( int a )
	{
		return point_t( this->x - a, this->y - a );
	}

	point_t operator/( int a )
	{
		return point_t( this->x / a, this->y / a );
	}
};

struct color_t
{
	int r, g, b, a;
	color_t( int _r, int _g, int _b, int _a = 255 ) : r( _r ), g( _g ), b( _b ), a( _a )
	{};

	color_t alpha( int _a, bool adaptive = true )
	{
		return color_t( r, g, b, adaptive ? a * ( _a / 255.f ) : _a );
	}

	bool operator!=( color_t& other )
	{
		return other.r != r || other.g != g || other.b != b || other.a != a;
	}

	static color_t blend( color_t first, color_t second, float t )
	{
		return color_t(
			first.r + static_cast< int >( t * ( second.r - first.r ) ),
			first.g + static_cast< int >( t * ( second.g - first.g ) ),
			first.b + static_cast< int >( t * ( second.b - first.b ) ),
			first.a + static_cast< int >( t * ( second.a - first.a ) )
		);
	}
};

using color = color_t;
using point = point_t;