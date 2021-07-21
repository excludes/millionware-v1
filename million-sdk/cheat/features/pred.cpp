#include "pred.hpp"

#include "../../source engine/sdk.hpp"

float engine_prediction::prev_curtime;
float engine_prediction::prev_frametime;

int tick_base;
c_user_cmd* last_cmd;

void engine_prediction::start( c_entity* local, c_user_cmd* cmd )
{
	// fix tickbase if game didnt render previous tick
	if ( last_cmd )
	{
		if ( last_cmd->has_been_predicted )
		{
			tick_base = local->tick_base( );
		}
		else
		{
			++tick_base;
		}
	}

	last_cmd = cmd;
	prev_curtime = interfaces::globals->cur_time;
	prev_frametime = interfaces::globals->frame_time;

	interfaces::globals->cur_time = ( tick_base * interfaces::globals->interval_per_tick );
	interfaces::globals->frame_time = interfaces::globals->interval_per_tick;

	interfaces::movement->StartTrackPredictionErrors( local );

	CMoveData data;
	memset( &data, 0, sizeof( CMoveData ) );

	interfaces::move_helper->SetHost( local );
	interfaces::prediction->SetupMove( local, cmd, interfaces::move_helper, &data );
	interfaces::movement->ProcessMovement( local, &data );
	interfaces::prediction->FinishMove( local, cmd, &data );
}

void engine_prediction::finish( c_entity* local )
{
	interfaces::movement->FinishTrackPredictionErrors( local );
	interfaces::move_helper->SetHost( nullptr );

	interfaces::globals->cur_time = prev_curtime;
	interfaces::globals->frame_time = prev_frametime;
}