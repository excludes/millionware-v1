#pragma once
#include "../utilities/engine.hpp"
#include "client.hpp"
#include "panel.hpp"
#include "surface.hpp"
#include "entity_list.hpp"
#include "../../source engine/classes/prediction.hpp"
#include "globals.hpp"
#include "../utilities/memory.hpp"
#include "../utilities/xorstring.hpp"
#include "engine.hpp"
#include "debug_overlay.hpp"
#include "weapon_system.hpp"
#include "i_localize.hpp"
#include "model_info_client.hpp"
#include "client_state.hpp"
#include "model_render.hpp"
#include "material_system.hpp"
#include "hud_chat.hpp"
#include "../../source engine/classes/gameevent.hpp"
#include "glow_object_manager.hpp"
#include "i_console.hpp"
#include "engine_trace.hpp"

namespace interfaces
{
	inline i_base_client_dll* client;
	inline i_panel* panel;
	inline i_surface* surface;
	inline i_client_entity_list* entity_list;
	inline void* client_mode;
	inline CPrediction* prediction;
	inline CGameMovement* movement;
	inline CMoveHelper* move_helper;
	inline c_global_vars_base* globals;
	inline iv_engine_client* engine;
	inline iv_debug_overlay* debug_overlay;
	inline i_weapon_system* weapon_system;
	inline i_localize* localize;
	inline iv_model_info_client* model_info;
	inline iv_model_render* model_render;
	inline void* engine_sound;
	inline i_client_state* client_state;
	inline i_material_system* material_system;
	inline c_hud_chat* hud_chat;
	inline i_game_event_manager* game_event_manager;
	inline c_glow_manager* glow_object;
	inline i_console* console;
	inline i_trace* trace;

	__forceinline void init( )
	{
		client = utils::engine::create_interface<i_base_client_dll>( xor ( "client.dll" ), xor ( "VClient018" ) );
		panel = utils::engine::create_interface<i_panel>( xor ( "vgui2.dll" ), xor ( "VGUI_Panel009" ) );
		surface = utils::engine::create_interface<i_surface>( xor ( "vguimatsurface.dll" ), xor ( "VGUI_Surface031" ) );
		entity_list = utils::engine::create_interface<i_client_entity_list>( xor ( "client.dll" ), xor ( "VClientEntityList003" ) );
		engine = utils::engine::create_interface<iv_engine_client>( xor ( "engine.dll" ), xor ( "VEngineClient014" ) );
		prediction = utils::engine::create_interface<CPrediction>( xor ( "client.dll" ), xor ( "VClientPrediction001" ) );
		movement = utils::engine::create_interface<CGameMovement>( xor ( "client.dll" ), xor ( "GameMovement001" ) );
		engine_sound = utils::engine::create_interface<void>( xor ( "engine.dll" ), xor ( "IEngineSoundClient003" ) );
		debug_overlay = utils::engine::create_interface<iv_debug_overlay>( xor ( "engine.dll" ), xor ( "VDebugOverlay004" ) );
		localize = utils::engine::create_interface<i_localize>( xor ( "localize.dll" ), xor ( "Localize_001" ) );
		model_info = utils::engine::create_interface<iv_model_info_client>( xor ( "engine.dll" ), xor ( "VModelInfoClient004" ) );
		model_render = utils::engine::create_interface<iv_model_render>( xor ( "engine.dll" ), xor ( "VEngineModel016" ) );
		material_system = utils::engine::create_interface<i_material_system>( xor ( "materialsystem.dll" ), xor ( "VMaterialSystem080" ) );
		game_event_manager = utils::engine::create_interface<i_game_event_manager>( xor ( "engine.dll" ), xor ( "GAMEEVENTSMANAGER002" ) );
		console = utils::engine::create_interface<i_console>( xor ( "vstdlib.dll" ), xor ( "VEngineCvar007" ) );
		trace = utils::engine::create_interface<i_trace>( xor ( "engine.dll" ), xor ( "EngineTraceClient004" ) );

		client_state = **( i_client_state*** )( utils::memory::pattern_scan( xor ( "engine.dll" ), xor ( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) ) + 1 );
		move_helper = **reinterpret_cast< CMoveHelper*** >( ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "8B 0D ? ? ? ? 8B 46 08 68" ) ) + 2 ) );
		weapon_system = *reinterpret_cast< i_weapon_system** >( ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "8B 35 ? ? ? ? FF 10 0F B7 C0" ) ) + ( 69 - 67 ) ) );
		glow_object = *reinterpret_cast< c_glow_manager** >( ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "0F 11 05 ? ? ? ? 83 C8 01" ) ) + 3 ) );

		client_mode = **reinterpret_cast< uintptr_t*** >( ( *reinterpret_cast< uintptr_t** >( client ) )[ 10 ] + 5 );
		globals = **reinterpret_cast<c_global_vars_base***>((utils::memory::pattern_scan(xor ("client.dll"), xor ("A1 ? ? ? ? 5E 8B 40 10")) + 1)); //A1 ? ? ? ? 5E 8B 40 10

		hud_chat = utils::engine::find_hud_element<c_hud_chat>( xor ( "CHudChat" ) );
	}
}