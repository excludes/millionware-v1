#pragma once

#include "../../source engine/structs/weaponinfo.hpp"

class i_weapon_system
{
public:
	weapon_info_t* get_weapon_data( int item_definition_index )
	{
		using original_fn = weapon_info_t * ( __thiscall* )( i_weapon_system*, int );
		return ( *( original_fn** )this )[ 2 ]( this, item_definition_index );
	}
};