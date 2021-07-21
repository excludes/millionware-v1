#pragma once
#include "../../source engine/math/vector3d.hpp"

class c_glow_manager
{
public:
	class c_glow_object
	{
	public:
		void set( float r, float g, float b, float a )
		{
			m_colour = vec3_t( r, g, b );
			m_alpha = a;
			m_render_when_occluded = true;
			m_render_when_unoccluded = false;
			m_bloom_amount = 1.0f;
		}

		void* entity( )
		{
			return m_entity;
		}

		bool unused( ) const
		{
			return m_next_slot != c_glow_object::ENTRY_IN_USE;
		}

	public:
		void* m_entity;
		vec3_t           m_colour;
		float            m_alpha;

		char             pad04[ 4 ]; //pad
		float            pad08; //confirmed to be treated as a float while reversing glow functions
		float            m_bloom_amount;
		float            m_local_zero;


		bool             m_render_when_occluded;
		bool             m_render_when_unoccluded;
		bool             m_full_bloom;
		char             m_pad09[ 1 ]; //pad


		int              m_bloom_stencil; // 0x28
		int              m_pad013; //appears like it needs to be zero  
		int              m_screen_slot; //Should be -1

										// Linked list of free slots
		int              m_next_slot;

		// Special values for GlowObjectDefinition_t::m_nNextFreeSlot
		static const int END_OF_FREE_LIST = -1;
		static const int ENTRY_IN_USE = -2;
	};

	c_glow_object* m_definitions;
	int            m_max_size;
	int            pad04;
	int            m_size;
	c_glow_object* m_definitions_other;
	int            m_current_objects;
	int            m_free_slot;
};
