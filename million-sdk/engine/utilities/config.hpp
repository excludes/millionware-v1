#pragma once

#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

#include "../../source engine/math/point.hpp"
#include "crypto.hpp"

namespace config
{
	struct config_node_t
	{
		char buffer[32];
	};

	inline std::unordered_map<uint64_t, config_node_t> config_map{};

	template<typename t>
	t* get(uint64_t hash)
	{
		if (config_map.find(hash) == config_map.end())
			config_map.insert({ hash, {} });

		return (t*)&config_map.at(hash);
	}

	__forceinline std::vector<char> dump()
	{
		std::vector<char> cfg_buf;
		std::for_each(config_map.begin(), config_map.end(), [&](std::pair<uint64_t, config_node_t> element)
		{
			for (int i = 0; i < 8; i++)
				cfg_buf.push_back(*(char*)((uintptr_t)&element.first + i));

			for (int i = 0; i < 32; i++)
				cfg_buf.push_back(*(char*)((uintptr_t)element.second.buffer + i));
		});

		return cfg_buf;
	}

	__forceinline void load(std::vector<char> cfg_buf)
	{
		for (int i = 0; i < cfg_buf.size(); i += 40)
		{
			auto buf = (const char*)((uintptr_t)cfg_buf.data() + i);

			const auto hash = *(uint64_t*)buf;
			buf += 8;

			*get<config_node_t>(hash) = *(config_node_t*)buf;
		}
	}

	void load_from_file(const char* file_name);
	void save_to_file(const char* file_name);
};