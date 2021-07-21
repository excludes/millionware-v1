#pragma once
#include <optional>

#include "../../source engine/sdk.hpp"

#define time_to_ticks(time) static_cast<int>(0.5f + time / interfaces::globals->interval_per_tick)
#define ticks_to_time(ticks) (interfaces::globals->interval_per_tick * ticks)

namespace backtrack
{
	struct c_record
	{
		c_record( int tickcount, vec3 headpos, vec3 abs_origin ) : m_tickcount( tickcount ), m_headpos( headpos ), m_abs_origin( abs_origin )
		{}

		int m_tickcount;
		vec3 m_headpos;
		vec3 m_abs_origin;
		matrix_t m_matrix[ 128 ];
	};

	extern std::vector<c_record> records[ 65 ];

	std::optional<c_record> find_last_record( int idx );

	void create_move( c_user_cmd* cmd, c_entity* lcoal );
}