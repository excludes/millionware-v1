#pragma once
#include "../math/vector3d.hpp"

struct model_t
{
	void* handle;
	char name[ 255 ];
};

struct model_render_info_t
{
	vec3_t origin;
	vec3_t angles;
	char pad[ 0x4 ];
	void* renderable;
	const model_t* model;
	const matrix_t* model_to_world;
	const matrix_t* lighting_offset;
	const vec3_t* lighting_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	unsigned short instance;
};