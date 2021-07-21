#pragma once

class i_localize
{
public:
	wchar_t* find( const char* name )
	{
		using original_fn = wchar_t* ( __thiscall* )( i_localize*, const char* );
		return ( *( original_fn** )this )[ 11 ]( this, name );
	}
};