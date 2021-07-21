#pragma once
#include <cstdint>

#include "../../source engine/structs/materials.hpp"

class i_material_system
{
public:
	i_material* find_material( char const* material_name, const char* group_name = nullptr, bool complain = true, const char* complain_prefix = 0 )
	{
		using original_fn = i_material * ( __thiscall* )( void*, char const*, const char*, bool, const char* );
		return ( *( original_fn** )this )[ 84 ]( this, material_name, group_name, complain, complain_prefix );
	}

	material_handle_t first_material( )
	{
		using original_fn = material_handle_t( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 86 ]( this );
	}

	material_handle_t next_material( material_handle_t handle )
	{
		using original_fn = material_handle_t( __thiscall* )( void*, material_handle_t );
		return ( *( original_fn** )this )[ 87 ]( this, handle );
	}

	material_handle_t invalid_material_handle( )
	{
		using original_fn = material_handle_t( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 88 ]( this );
	}

	i_material* get_material( material_handle_t handle )
	{
		using original_fn = i_material * ( __thiscall* )( void*, material_handle_t );
		return ( *( original_fn** )this )[ 89 ]( this, handle );
	}

	int	get_materials_count( )
	{
		using original_fn = int( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 90 ]( this );
	}
};