#pragma once

class i_net_mesage
{
public:
	int get_type( )
	{
		using original_fn = int( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 7 ]( this );
	}
};