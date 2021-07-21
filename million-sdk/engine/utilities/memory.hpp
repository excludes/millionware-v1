#pragma once
#include <cstdint>
#include <string_view>

namespace utils::memory
{
	uint8_t* pattern_scan( const char* module_name, const std::string_view signature );
}