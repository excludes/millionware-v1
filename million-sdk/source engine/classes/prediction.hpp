#pragma once
#include "../math/vector3d.hpp"
class player_t;
class c_usercmd;

using c_entity = player_t;
using c_user_cmd = c_usercmd;

class CMoveHelper
{
public:
	void SetHost( c_entity* host )
	{
		using original_fn = void( __thiscall* )( void*, c_entity* );
		return ( *( original_fn** )this )[ 1 ]( this, host );
	}
};

struct CMoveData
{
	char data[ 184 ];
};

class CGameMovement
{
public:
	virtual			~CGameMovement( void )
	{}

	virtual void	ProcessMovement( c_entity* pPlayer, CMoveData* pMove ) = 0;
	virtual void	Reset( void ) = 0;
	virtual void	StartTrackPredictionErrors( c_entity* pPlayer ) = 0;
	virtual void	FinishTrackPredictionErrors( c_entity* pPlayer ) = 0;
	virtual void	DiffPrint( char const* fmt, ... ) = 0;

	virtual vec3 const& GetPlayerMins( bool ducked ) const = 0;
	virtual vec3 const& GetPlayerMaxs( bool ducked ) const = 0;
	virtual vec3 const& GetPlayerViewOffset( bool ducked ) const = 0;

	virtual bool			IsMovingPlayerStuck( void ) const = 0;
	virtual c_entity* GetMovingPlayer( void ) const = 0;
	virtual void			UnblockPusher( c_entity* pPlayer, c_entity* pPusher ) = 0;

	virtual void    SetupMovementBounds( CMoveData* pMove ) = 0;
};

class CPrediction
{
	// Construction
public:

	virtual ~CPrediction( void ) = 0;//

	virtual void Init( void ) = 0;//
	virtual void Shutdown( void ) = 0;//

									// Implement IPrediction
public:

	virtual void Update
	(
		int startframe, // World update ( un-modded ) most recently received
		bool validframe, // Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command // Last command (most recent) sent to server (un-modded)
	);//

	virtual void PreEntityPacketReceived( int commands_acknowledged, int current_world_update_packet );//
	virtual void PostEntityPacketReceived( void );//5
	virtual void PostNetworkDataReceived( int commands_acknowledged );//

	virtual void OnReceivedUncompressedPacket( void );//

													// The engine needs to be able to access a few predicted values
	virtual void GetViewOrigin( vec3& org );//
	virtual void SetViewOrigin( vec3& org );//
	virtual void GetViewAngles( vec3& ang );//10
	virtual void SetViewAngles( vec3& ang );//

	virtual void GetLocalViewAngles( vec3& ang );//
	virtual void SetLocalViewAngles( vec3& ang );//

	virtual bool InPrediction( void ) const;//14
	virtual bool IsFirstTimePredicted( void ) const;//

	virtual int GetLastAcknowledgedCommandNumber( void ) const;//

#if !defined( NO_ENTITY_PREDICTION )
	virtual int GetIncomingPacketNumber( void ) const;//
#endif

	virtual void CheckMovingGround( c_entity* player, double frametime );//
	virtual void RunCommand( c_entity* player, c_user_cmd* cmd, CMoveHelper* moveHelper );//

	virtual void SetupMove( c_entity* player, c_user_cmd* cmd, CMoveHelper* pHelper, CMoveData* move );//20
	virtual void FinishMove( c_entity* player, c_user_cmd* cmd, CMoveData* move );//
	virtual void SetIdealPitch( int nSlot, c_entity* player, const vec3& origin, const vec3& angles, const vec3& viewheight );//

	virtual void CheckError( int nSlot, c_entity* player, int commands_acknowledged );//

public:
	virtual void _Update
	(
		int nSlot,
		bool received_new_world_update,
		bool validframe,            // Is frame data valid
		int incoming_acknowledged,  // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command        // Last command (most recent) sent to server (un-modded)
	);

	// Actually does the prediction work, returns false if an error occurred
	bool PerformPrediction( int nSlot, c_entity* localPlayer, bool received_new_world_update, int incoming_acknowledged, int outgoing_command );

	void ShiftIntermediateDataForward( int nSlot, int slots_to_remove, int previous_last_slot );

	void RestoreEntityToPredictedFrame( int nSlot, int predicted_frame );

	int ComputeFirstCommandToExecute( int nSlot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command );

	void DumpEntity( c_entity* ent, int commands_acknowledged );

	void ShutdownPredictables( void );

	void ReinitPredictables( void );

	void RemoveStalePredictedEntities( int nSlot, int last_command_packet );

	void RestoreOriginalEntityState( int nSlot );

	void RunSimulation( int current_command, float curtime, c_user_cmd* cmd, c_entity* localPlayer );

	void Untouch( int nSlot );

	void StorePredictionResults( int nSlot, int predicted_frame );

	bool ShouldDumpEntity( c_entity* ent );

	void SmoothViewOnMovingPlatform( c_entity* pPlayer, vec3& offset );

	void ResetSimulationTick( );

	void ShowPredictionListEntry( int listRow, int showlist, c_entity* ent, int& totalsize, int& totalsize_intermediate );

	void FinishPredictionList( int listRow, int showlist, int totalsize, int totalsize_intermediate );

	void CheckPredictConvar( );

#if !defined( NO_ENTITY_PREDICTION )

#endif
};