#pragma once
class i_material;

class iv_model_render
{
public:
	void force_override_material( i_material* mat )
	{
		using original_fn = void( __thiscall* )( void*, i_material*, int, int );
		return ( *( original_fn** )this )[ 1 ]( this, mat, 0, 0 );
	}

	bool is_forced_material_override( )
	{
		using original_fn = bool( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 2 ]( this );
	}
};