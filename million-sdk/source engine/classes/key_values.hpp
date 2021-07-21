#pragma once

#include "../../engine/utilities/memory.hpp"
#include "../../engine/utilities/xorstring.hpp"

class key_values
{
public:
	key_values* init( const char* name )
	{
		using ctor_t = key_values * ( __thiscall* )( void*, const char* );

		static auto ctor = reinterpret_cast< ctor_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC 51 33 C0 C7 45" ) );
		return ctor( this, name );
	};

	// xref '%s\\gameinfo.txt'
	bool load_from_buffer( const char* name, const char* buffer )
	{
		using load_t = bool( __thiscall* )( key_values*, const char*, const char*, void*, void*, void* );

		static auto load_from_buffer_fn = reinterpret_cast< load_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" ) );
		return load_from_buffer_fn( this, name, buffer, 0, 0, 0 );
	}

	key_values* find_key( const char* name, bool bCreate )
	{
		using findkey_t = key_values * ( __thiscall* )( key_values*, const char*, bool );
		static auto find_key_fn = reinterpret_cast< findkey_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC 83 EC 1C 53 8B D9 85 DB" ) );
		return find_key_fn( this, name, bCreate );
	}

	void set_int( const char* keyName, int val )
	{
		auto key_int = find_key( keyName, true );

		if ( key_int )
		{
			*reinterpret_cast< int* >( reinterpret_cast< uintptr_t >( key_int ) + 0xC ) = val;
			*reinterpret_cast< char* >( reinterpret_cast< uintptr_t >( key_int ) + 0x10 ) = 2;
		}
	}

	void set_string( const char* name, const char* a2 )
	{
		auto key = find_key( name, true );
		using setstring_t = void( __thiscall* )( void*, const char* );

		if ( key )
		{
			static auto set_string_fn = reinterpret_cast< setstring_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01" ) );
			set_string_fn( key, a2 );
		}
	}
};