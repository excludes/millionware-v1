#include "bt.hpp"
#include "../../engine/utilities/math.hpp"
#include "../../engine/utilities/config.hpp"

namespace backtrack
{
	std::vector<c_record> records[ 65 ];

	int max_backtrack_amount( )
	{
		static int max_record_size{};

		switch ( *config::get<int>( crc( "ass::backtrack::intensity" ) ) )
		{
		case 0: max_record_size = 4; break;
		case 1: max_record_size = 8; break;
		case 2: max_record_size = 12; break;
		}

		return max_record_size;
	}

	std::optional<c_record> find_last_record( int idx )
	{
		if ( records[ idx ].empty( ) )
		{
			return std::nullopt;
		}

		return std::make_optional( records[ idx ].back( ) );
	}

	void create_move( c_user_cmd* cmd, c_entity* local )
	{
		int closest = -1;
		float delta = FLT_MAX;

		auto view = cmd->view_angles;

		for ( int i = 1; i <= 64; i++ )
		{
			auto ent = ( interfaces::entity_list->get<player_t>( i ) );

			if ( !ent )
			{
				if ( !records[ i ].empty( ) )
				{
					records[ i ].clear( );
				}

				continue;
			}

			if ( !ent->health( ) )
			{
				if ( !records[ i ].empty( ) )
				{
					records[ i ].clear( );
				}

				continue;
			}

			if ( !*config::get<bool>( crc( "ass:backtrack" ) ) )
			{
				if ( !records[ i ].empty( ) )
				{
					records[ i ].clear( );
				}

				return;
			}

			records[ i ].insert( records[ i ].begin( ), c_record( cmd->tick_count, ent->bone_pos( 8 ), ent->abs_origin( ) ) );

			if ( records[ i ].size( ) > max_backtrack_amount( ) )
			{
				records[ i ].pop_back( );
			}

			if ( !ent->setup_bones( records[ i ].front( ).m_matrix, 128, bone_used_by_anything, 0.f ) )
			{
				continue;
			}

			auto fov = utils::math::get_fov( local->eye_pos( ), ent->eye_pos( ), view );
			if ( fov < delta )
			{
				closest = i;
				delta = fov;
			}
		}

		int index = 0;

		if ( closest != -1 )
		{
			for ( uint32_t i = 0; i < records[ closest ].size( ); i++ )
			{
				float fov = utils::math::get_fov( local->eye_pos( ), records[ closest ][ i ].m_headpos, view );

				if ( fov < delta )
				{
					index = i;
					delta = fov;
				}
			}

			if ( index && cmd->buttons & in_attack )
			{
				cmd->tick_count = records[ closest ].at( index ).m_tickcount;
			}
		}
	}
}
