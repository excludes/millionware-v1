#pragma once

class i_game_event
{
public:
	const char* get_name( )
	{
		using original_fn = const char* ( __thiscall* )( i_game_event* );
		return ( *( original_fn** )this )[ 1 ]( this );
	}
	int get_int( const char* name )
	{
		using original_fn = int( __thiscall* )( i_game_event*, const char*, int );
		return ( *( original_fn** )this )[ 6 ]( this, name, 0 );
	}
	const char* get_string( const char* keyname = nullptr )
	{
		using original_fn = const char* ( __thiscall* )( i_game_event*, const char*, const char* );
		return ( *( original_fn** )this )[ 9 ]( this, keyname, "" );
	}
	void set_string( const char* keyname, const char* value )
	{
		using original_fn = void( __thiscall* )( i_game_event*, const char*, const char* );
		return ( *( original_fn** )this )[ 16 ]( this, keyname, value );
	}
};

class i_game_event_listener
{
public:
	virtual ~i_game_event_listener( )
	{}

	virtual void fire_game_event( i_game_event* event ) = 0;
	virtual int get_debug_id( ) = 0;

public:
	int debug_id;
};

class i_game_event_manager
{
public:
	bool add_listener( i_game_event_listener* listener, const char* name, bool serverside )
	{
		using original_fn = bool( __thiscall* )( i_game_event_manager*, i_game_event_listener*, const char*, bool );
		return ( *( original_fn** )this )[ 3 ]( this, listener, name, serverside );
	}

	void remove_listener( i_game_event_listener* listener )
	{
		using original_fn = void( __thiscall* )( i_game_event_manager*, i_game_event_listener* );
		return ( *( original_fn** )this )[ 5 ]( this, listener );
	}

	void add_listener_global( i_game_event_listener* listener, bool serverside )
	{
		using original_fn = void( __thiscall* )( i_game_event_manager*, i_game_event_listener*, bool );
		return ( *( original_fn** )this )[ 6 ]( this, listener, serverside );
	}
};