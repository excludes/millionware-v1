#pragma once

#include "../../source engine/classes/entities.hpp"

// forward declarations or define point here?
#include "../../source engine/math/point.hpp"

#include <unordered_map>

namespace visuals
{
	struct box_t
	{
		point_t pos;
		point_t size;
	};

	// general context to avoid calling get_box
	// and shit multiple times on players, if we
	// don't like this or have a better way of
	// going around this then change it and lmk ~alpha
	inline struct context_t
	{
		box_t bbox;

		player_t* player;
		player_t* local;

		std::vector< std::pair< int, float > > players;

		int offset;
		float alpha[ 64 ];
	} ctx;

	inline std::unordered_map<int, std::wstring> weapon_chars =
	{
		{ weapon_deagle, L"F" }, { weapon_elite, L"S" }, { weapon_revolver, L"" }, { weapon_taser, L"" }, { weapon_fiveseven, L"U" },
		{ weapon_awp, L"R" }, { weapon_famas, L"T" }, { weapon_g3sg1, L"I" }, { weapon_galilar, L"V" }, { weapon_m249, L"Z" }, { weapon_aug, L"E" },
		{ weapon_m4a1, L"W" }, { weapon_mac10, L"L" }, { weapon_p90, L"M" }, { weapon_ump45, L"Q" }, { weapon_xm1014, L"]" },
		{ weapon_bizon, L"D" }, { weapon_mag7, L"K" }, { weapon_negev, L"Z" }, { weapon_sawedoff, L"K" }, { weapon_tec9, L"C" },
		{ weapon_hkp2000, L"Y" }, { weapon_mp7, L"X" }, { weapon_mp9, L"D" }, { weapon_nova, L"K" }, { weapon_ak47, L"B" },
		{ weapon_p250, L"Y" }, { weapon_scar20, L"I" }, { weapon_sg556, L"[" }, { weapon_scout, L"N" }, { weapon_knife, L"J" },
		{ weapon_flashbang, L"G" }, { weapon_hegrenade, L"H" }, { weapon_smokegrenade, L"P" }, { weapon_molotov, L"P" }, { weapon_decoy, L"G" },
		{ weapon_incgrenade, L"P" }, { weapon_c4, L"\\" }, { weapon_knife_t, L"J" }, { weapon_m4a1_silencer, L"W" }, { weapon_usp_silencer, L"Y" },
		{ weapon_bayonet, L"J" }, { weapon_knife_flip, L"J" }, { weapon_knife_gut, L"J" }, { weapon_knife_karambit, L"J" }, { weapon_glock, L"C" },
		{ weapon_knife_m9_bayonet, L"J" }, { weapon_knife_tactical, L"J" }, { weapon_knife_falchion, L"J" }, { weapon_knife_survival_bowie, L"J" },
		{ weapon_knife_butterfly, L"J" }, { weapon_knife_push, L"J" }, { weapon_knife_gypsy_jackknife, L"J" }, { weapon_knife_stiletto, L"J" },
		{ weapon_knife_ursus, L"J" }, { weapon_knife_widowmaker, L"J" }, { weapon_mp5sd, L"X" }
	};

	void box( );
	void name( );
	void flashkill( );
	void weapon( );
	void health( );
	void flags( );
	void glow( );
	void skeleton( );

	void bomb( player_t* ent );
	void dropped( player_t* ent );

	void sort_players( );
	bool get_box( player_t* ent, box_t& bbox );

	bool begin( );

	void draw( );
}