#pragma once

#include "../../source engine/classes/studio.hpp"

struct model_t;
class iv_model_info_client
{
public:
	studio_hdr_t* get_studio_model( const model_t* mod )
	{
		using original_fn = studio_hdr_t * ( __thiscall* )( iv_model_info_client*, const model_t* );
		return ( *( original_fn** )this )[ 32 ]( this, mod );
	}
	int get_model_index( const char* name )
	{
		using original_fn = int( __thiscall* )( iv_model_info_client*, const char* );
		return ( *( original_fn** )this )[ 2 ]( this, name );
	}
};