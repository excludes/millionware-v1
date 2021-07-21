#pragma once
#include "../../source engine/classes/prediction.hpp"
#include "../../engine/interfaces/interfaces.hpp"

namespace engine_prediction
{
	extern float prev_curtime;
	extern float prev_frametime;

	void start( c_entity* local, c_user_cmd* cmd );
	void finish( c_entity* local );
};