#include "input.hpp"
#include "../../engine/utilities/xorstring.hpp"

namespace input
{
	point cursor_pos;
	point cursor_delta;

	point mouse_move;

	void update( )
	{
		static HWND window;
		if ( !window )
			window = FindWindowA( xor ( "Valve001" ), 0 );

		POINT mouse;
		GetCursorPos( &mouse );
		ScreenToClient( window, &mouse );

		cursor_delta.x = mouse_move.x - cursor_pos.x;
		cursor_delta.y = mouse_move.y - cursor_pos.y;

		cursor_pos.x = mouse_move.x;
		cursor_pos.y = mouse_move.y;

		std::copy( key_state.begin( ), key_state.end( ), prev_state.begin( ) );

		for ( int i = 0; i < 256; i++ )
			key_state.at( i ) = GetAsyncKeyState( i ); // key_down[ i ];
	}
}