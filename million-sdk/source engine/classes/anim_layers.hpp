#pragma once

class c_animation_layer
{
	char pad_0000[ 20 ] = {};
public:
	unsigned int order{};
	unsigned int sequence{};
	float prev_cycle{};
	float weight{};
	float weight_delta_rate{};
	float playback_rate{};
	float cycle{};
	void* owner{};
private:
	char pad_0038[ 4 ] = {};
};