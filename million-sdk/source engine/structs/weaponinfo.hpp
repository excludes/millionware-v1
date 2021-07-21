#pragma once

class c_strike_weapon_definition
{
public:
	char pad_0x0000[ 0x8 ]; //0x0000
	int id; //0x0008
};

class weapon_info_t
{
public:
	int item_definition_index( ) const
	{
		if ( !def )
			return -1;

		return def->id;
	}

	virtual ~weapon_info_t( ) = default;

	char* console_name;				// 0x0004
	char		pad_0008[ 8 ];				// 0x0008
	c_strike_weapon_definition* def;  //0x0010
	int			max_clip;					// 0x0014
	int			max_clip2;					// 0x0018
	int			default_clip;				// 0x001C
	int			default_clip2;				// 0x0020
	char		pad_0024[ 8 ];				// 0x0024
	char* world_model;				// 0x002C
	char* view_model;				// 0x0030
	char* dropped_model;				// 0x0034
	char		pad_0038[ 4 ];				// 0x0038
	char* bruh;					// 0x003C
	char		pad_0040[ 56 ];				// 0x0040
	char* empty_sound;				// 0x0078
	char		pad_007C[ 4 ];				// 0x007C
	char* bullet_type;				// 0x0080
	char		pad_0084[ 4 ];				// 0x0084
	char* hud_name;					// 0x0088
	char* weapon_name;				// 0x008C
	char		pad_0090[ 60 ];				// 0x0090
	int 		type;					// 0x00C8
	int			price;				// 0x00CC
	int			kill_award;					// 0x00D0
	char* anim_prefix;			// 0x00D4
	float		cycle_time;				// 0x00D8
	float		cycle_time_alt;				// 0x00DC
	float		time_to_idle;				// 0x00E0
	float		idle_interval;				// 0x00E4
	bool		full_auto;					// 0x00E8
	char		pad_0x00E5[ 3 ];			// 0x00E9
	int			damage;					// 0x00EC
	float		armor_ratio;				// 0x00F0
	int			bullets;					// 0x00F4
	float		penetration;				// 0x00F8
	float		vel_modifier_large;	// 0x00FC
	float		vel_modifier_small;	// 0x0100
	float		range;					// 0x0104
	float		range_modifier;			// 0x0108
	float		throw_vel;			// 0x010C
	char		pad_0x010C[ 16 ];			// 0x0110
	bool		has_silencer;				// 0x011C
	char		pad_0x0119[ 3 ];			// 0x011D
	char* silencer_model;				// 0x0120
	int			crosshair_min_dist;		// 0x0124
	float		max_speed;	        // 0x0128
	float		max_speed_alt;		// 0x012C
	char		pad_0x0130[ 4 ];		    // 0x0130
	float		spread;					// 0x0134
	float		spread_alt;				// 0x0138
	float		inaccuracy_crouch;			// 0x013C
	float		inaccuracy_crouch_alt;		// 0x0140
	float		inaccuracy_stand;			// 0x0144
	float		inaccuracy_stand_alt;		// 0x0148
	float		inaccuracy_jump_initial;	// 0x014C
	float		inaccuracy_jump;			// 0x0150
	float		inaccuracy_jump_alt;		// 0x0154
	float		inaccuracy_land;			// 0x0158
	float		dsffdgngfds;		// 0x015C
	float		dsfdsf;			// 0x0160
	float		dsfgdsdfds;		// 0x0164
	float		fdsfs;			// 0x0168
	float		dsfdsgfgfds;		// 0x016C
	float		fsddsf;			// 0x0170
	float		sfdsf;		// 0x0174
	float		fsdf;			// 0x0178
	int			seed;				// 0x017C
	float		sdfds;				// 0x0180
	float		nom;			// 0x0184
	float		sfds;		// 0x0188
	float		dsfdsfherreh;	// 0x018C
	float		sfsdf;			// 0x0190
	float		sfsdfdfgdg;		// 0x0194
	float		sdfsdf;	// 0x0198
	float		sdfdsf;	// 0x019C
	float		amnagm;		// 0x01A0
	float		dfsdf;		// 0x01A4
	float		sdfsdfdfgfdg;	// 0x01A8
	float		FS;	// 0x01AC
	int			nbdab;	// 0x01B0 
	int			gfg;	// 0x01B4
	bool		nfgsnfsnfgnsfdsf;			// 0x01B8
	bool		adfhadgnsdfds;		// 0x01B9
	char		pad_0x01B5[ 2 ];			// 0x01BA
	char		gfd[ 3 ];			// 0x01BC
	int			barfgbg[ 2 ];				// 0x01C0
	float		fsdfdsf[ 3 ];				// 0x01C4
	char* weapon_class;				// 0x01D4
	float		addon_Scale;				// 0x01D8
	char		pad_0x01DC[ 4 ];			// 0x01DC
	char* useless;			// 0x01E0
	char* what_the_fuck;				// 0x01E4
	int			sfdsfds;			// 0x01E8
	int			iTracefsdfsfsdffrFrequencyAlt;		// 0x01EC
	char* sdfsdfdsfdsf;	// 0x01F0
	char		pad_0x01F4[ 4 ];				// 0x01F4
	char* afdsfds;	// 0x01F8
	char		pad_0x01FC[ 4 ];			// 0x01FC
	char* sfnsfgmfsmdsf;		// 0x0200
	float		flHeatPerNigger;				// 0x0204
	char* nigger;				// 0x0208
	char* bro;				// 0x020C
	float		wtf;		// 0x0210
	float		half;	// 0x0214
	float		of;			// 0x0218
	char		these[ 8 ];			// 0x0220
	char* are;				// 0x0224
	bool		fucking;				// 0x0228
	char		XDXDuseless[ 3 ];			// 0x0229
	bool		pandora;				// 0x022C
	bool		best;		// 0x0230
};