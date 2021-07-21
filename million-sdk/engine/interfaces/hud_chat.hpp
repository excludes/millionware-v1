#pragma once
#include <iostream>
#include <stdarg.h>

class c_hud_chat
{
public:
	void chat_print( const char* format, ... )
	{
		if ( !this ) return;

		static char buf[ 1024 ] = "";

		va_list va;
		va_start( va, format );
		vsnprintf_s( buf, 1024, format, va );
		va_end( va );

		using original_fn = void( __cdecl* )( void*, int, int, const char*, ... );
		return ( *( original_fn** )this )[ 27 ]( this, 0, 0, buf );
	}

	void chat_print_w( const wchar_t* format )
	{
		if ( !this ) return;

		using original_fn = void( __thiscall* )( void*, int, int, const wchar_t* );
		return ( *( original_fn** )this )[ 28 ]( this, 0, 0, format );
	}
};