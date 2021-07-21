#pragma once
#include "xorstring.hpp"
#include "memory.hpp"

namespace utils::engine
{
	void* create_interface( const char* module_name, const char* iface_name );

	template<typename t>
	t* create_interface( const char* module_name, const char* iface_name )
	{
		return reinterpret_cast< t* >( create_interface( module_name, iface_name ) );
	}

	template<class T>
	__forceinline T* find_hud_element( const char* name )
	{
		static auto fn = *reinterpret_cast< uintptr_t** > ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08" ) ) + 1 );

		static auto find_hud_element = reinterpret_cast< uintptr_t( __thiscall* )( void*, const char* ) >(
			utils::memory::pattern_scan( ( "client.dll" ), ( "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39" ) ) );
		return ( T* )find_hud_element( fn, name );
	}

	inline int round_flags;
}