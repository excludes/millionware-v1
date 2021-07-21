#include "engine.hpp"
#include <windows.h>
#include <cstdio>

#include "xorstring.hpp"

namespace utils::engine
{
	void* create_interface( const char* module_name, const char* iface_name )
	{
		using create_interface_fn = void* ( * )( const char*, void* );
		auto fn_addr = ( create_interface_fn )GetProcAddress( GetModuleHandleA( module_name ), xor ( "CreateInterface" ) );

		auto iface_addr = fn_addr( iface_name, nullptr );
		printf( xor ( "[+] found %s at 0x%p\n" ), iface_name, iface_addr );

		return iface_addr;
	}
}