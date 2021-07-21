#pragma once
#include <cstdint>
#include <string.h>
#include <array>

namespace utils::crypto
{
	constexpr __declspec( noinline ) auto gen_crc32_table( )
	{
		constexpr auto num_bytes = 256;
		constexpr auto num_iterations = 8;
		constexpr auto polynomial = 0xEDB88320;

		auto crc32_table = std::array<int32_t, num_bytes>{};

		for ( auto byte = 0; byte < num_bytes; ++byte )
		{
			auto crc = byte;

			for ( auto i = 0; i < num_iterations; ++i )
			{
				auto mask = -( crc & 1 );
				crc = ( crc >> 1 ) ^ ( polynomial & mask );
			}

			crc32_table[ byte ] = crc;
		}

		return crc32_table;
	}
	static constexpr auto crc32_table = gen_crc32_table( );
	constexpr __declspec( noinline ) auto crc32( const char* in )
	{
		auto crc = 0xFFFFFFFFu;

		for ( auto i = 0u; auto c = in[ i ]; ++i )
		{
			crc = crc32_table[ ( crc ^ c ) & 0xFF ] ^ ( crc >> 8 );
		}

		return ~crc;
	}

	__forceinline uint64_t hash( const wchar_t* p )
	{
		size_t s = wcslen( p );
		size_t result = 0;
		const size_t prime = 31;
		for ( size_t i = 0; i < s; ++i )
		{
			result = p[ i ] + ( result * prime );
		}
		return result;
	}

	__forceinline uint64_t hash( const char* p )
	{
		size_t s = strlen( p );
		size_t result = 0;
		const size_t prime = 31;
		for ( size_t i = 0; i < s; ++i )
		{
			result = p[ i ] + ( result * prime );
		}
		return result;
	}
}

#define crc(s) ::utils::crypto::crc32(s)