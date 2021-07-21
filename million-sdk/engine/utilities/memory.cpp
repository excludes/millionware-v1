#include "memory.hpp"
#include <windows.h>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <vector>

namespace utils::memory
{
#define FIND_NT_HEADER(x) reinterpret_cast<PIMAGE_NT_HEADERS>( uint32_t(x) + reinterpret_cast<PIMAGE_DOS_HEADER>(x)->e_lfanew )

	uint8_t* pattern_scan( const char* module_name, const std::string_view signature )
	{
		std::vector<uint8_t> signature_bytes{ };

		{
			signature_bytes.resize( signature.size( ) );

			std::vector<std::string> signature_chunks{ };
			std::string current_chunk{ };

			std::istringstream string_stream{ signature.data( ) };

			while ( std::getline( string_stream, current_chunk, ' ' ) )
				signature_chunks.push_back( current_chunk );

			std::transform( signature_chunks.cbegin( ), signature_chunks.cend( ), signature_bytes.begin( ), [ ]( const std::string& val ) -> uint8_t
							{
								return val.find( '?' ) != std::string::npos ? 0ui8 : static_cast< uint8_t >( std::stoi( val, nullptr, 16 ) );
							} );
		}

		uint8_t* found_bytes = nullptr;	{
			const auto image_start = reinterpret_cast< uint8_t* >( GetModuleHandleA( module_name ) );
			const auto image_end = image_start + FIND_NT_HEADER( image_start )->OptionalHeader.SizeOfImage;

			const auto result = std::search( image_start, image_end, signature_bytes.cbegin( ), signature_bytes.cend( ), [ ]( uint8_t left, uint8_t right ) -> bool
			 {
				 return right == 0ui8 || left == right;
			 } );

			found_bytes = ( result != image_end ) ? result : nullptr;
		}

		return found_bytes;
	}
}