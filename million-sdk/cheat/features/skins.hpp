#pragma once

class weapon_t;
class attributable_item_t;

namespace skins
{
	namespace general
	{
		void full_update( );
	}

	namespace knifes
	{
		void update_knife( weapon_t* weapon );
		const char* update_kill_icons( );
	}

	namespace gloves
	{
		void set_glove_model( );
		void set_glove_attributes( attributable_item_t* item );
	}
}