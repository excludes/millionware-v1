#pragma once
#include "../../source engine/sdk.hpp"

namespace jump_stats
{
	// { {left, right}, {incremented_left, incremented_right} }
	using strafes_t = std::pair<std::pair<int, int>, std::pair<bool, bool>>;

	inline struct
	{
		int m_predicted_flags;
		int m_unpredicted_flags;

		bool m_bhopped;
		bool m_bhopping;
		bool m_jump_bugged;
		bool m_was_in_air;
		bool m_fell_too_much;
		bool m_jumped_too_high;

		int m_previous_strafes;
		int m_last_tick_on_ground;
		int m_last_tick_in_air;
		int m_consecutive_ticks_on_ground;
		int m_consecutive_ticks_in_air;

		float m_last_strafe_increment;

		strafes_t m_successful_strafes;
		strafes_t m_attempted_strafes;

		int m_total_successful_strafes;
		int m_total_attempted_strafes;

		int m_take_off_velocity;
		int m_highest_velocity;

		int m_strafe_sync;

		vec3 m_take_off_pos;
		vec3 m_landed_pos;

		float m_long_jump;
	} stat_info;

	void update_unpredicted_info( int flags );
	void update_predicted_info( int flags );

	void update_info( c_usercmd* cmd );

	const char* get_color_by_distance( float lj );

	void announce( float lj, bool jb = false );
}