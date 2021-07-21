#pragma once

#include "../../source engine/classes/entities.hpp"
#include "../../source engine/math/point.hpp"
#include "../../source engine/classes/c_usercmd.hpp"

namespace fake_backwards
{
	struct angle_data_t
	{
		vec3_t m_old_viewangle;
		float m_old_sidemove;
		float m_old_forwardmove;

		bool m_should_turn;
		bool m_in_recovery;
		bool m_can_recover;
		bool m_has_recovered;

		float m_current_turn;

		float m_last_activity;
	};

	inline angle_data_t angle_data;

	void pre_move_fix( c_usercmd* cmd );
	void post_move_fix( c_usercmd* cmd );

	float handle_turn( player_t* local );
	void run( c_usercmd* cmd );
	void visualise( );
}