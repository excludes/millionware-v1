#pragma once

#include "../../source engine/sdk.hpp"

namespace hitmarkers
{
	struct
	{
		float m_alpha;
		float m_hurt_time;
	} hit_info;

	void update( );
	void draw( );
}