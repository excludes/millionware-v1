#pragma once
#include "../../source engine/math/point.hpp"
#include <Windows.h>
#include <algorithm>
#include <array>

namespace input
{
	extern point cursor_pos;
	extern point cursor_delta;

	extern point mouse_move; // for wndproc

	inline std::array<bool, 256> key_state{};
	inline std::array<bool, 256> prev_state{};

	inline std::array<bool, 256> key_down{};

	__forceinline bool hover( point pos, point size )
	{
		return ( cursor_pos.x > pos.x&& cursor_pos.y > pos.y&& cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y );
	}

	__forceinline bool click( int k )
	{
		return key_state.at( k ) && !prev_state.at( k );
	}

	__forceinline bool hold( int k )
	{
		return key_state.at( k );
	}

	__forceinline bool release( int k )
	{
		return !key_state.at( k ) && prev_state.at( k );
	}

	void update( );
}