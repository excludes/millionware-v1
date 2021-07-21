#pragma once
#include "../../engine/interfaces/interfaces.hpp"
#include <cstdint>

#include "../../source engine/classes/c_usercmd.hpp"#
#include "../../source engine/structs/models.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "holy_hook.hpp"

namespace hooks
{
	class c_hook
	{
	private:
		uint8_t m_original_bytes[ 5 ];
		uint32_t m_original_address;
		uint32_t m_hook_address;
		bool m_is_rwx = false;
	public:
		void hook_function( uint32_t _original_address, uint32_t _hook_address );

		void unhook( );

		void rehook( );
		uint32_t get_ofunc( );
	};

	inline c_holy_hook pt_holy_hook;
	inline c_holy_hook fsn_holy_hook;
	inline c_holy_hook cm_holy_hook;
	inline c_holy_hook lc_holy_hook;
	inline c_holy_hook dme_holy_hook;
	inline c_holy_hook dpu_holy_hook;
	inline c_holy_hook gcm_holy_hook;
	inline c_holy_hook iuspdm_holy_hook;

	inline c_hook pt_hook;
	inline c_hook fsn_hook;
	inline c_hook cm_hook;
	inline c_hook lc_hook;
	inline c_hook es_hook;
	inline c_hook snm_hook;
	inline c_hook dme_hook;
	inline c_hook dpu_hook;
	inline c_hook cc_hook;
	inline c_hook ossc_hook;

	inline bool b_predicting;

	void __fastcall paint_traverse( void* ecx, void* edx, unsigned int panel, bool force, bool allow_force );
	void __fastcall frame_stage_notify( void* ecx, void* edx, int stage );
	bool __fastcall create_move( void* ecx, void* edx, float frame_time, c_usercmd* cmd );
	void __fastcall lock_cursor( void* ecx, void* edx );
	void __fastcall emit_sound( void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const vec3* pOrigin, const vec3* pDirection, vec3* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, void* fwer );
	bool __fastcall send_net_msg( void* channel, uint32_t, void* msg, bool reliable, bool voice );
	void __fastcall draw_model_execute( void* ecx, void* edx, void* ctx, void* state, model_render_info_t* info, matrix_t* matrix );
	bool __fastcall dispatch_user_message( void*, void*, int type, uint32_t a3, uint32_t len, void* msg_data );
	void __fastcall client_cmd( void* ecx, void* edx, const char* cmd );
	void __fastcall on_screen_size_change( void* ecx, void* edx, int old_w, int old_h );
	void __fastcall get_color_modulation(void* ecx, void* edx, float* r, float* g, float* b);
	bool __stdcall  is_using_static_prop_debug_modes();
	
	void init( );

	void revert( );
}