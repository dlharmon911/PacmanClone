#ifndef _PACMAN_GAME_PLAYER_H_
#define _PACMAN_GAME_PLAYER_H_

#include "base.h"
#include "console.h"
#include "sprite.h"
#include "game_defines.h"
#include "game_sprite_list.h"
#include "game_grid.h"

namespace pacman
{
	namespace game
	{
		typedef struct player_t player_t;
		namespace player
		{
			player_t* create();
			void destroy(player_t* player);
			void reset(player_t* player);
			void update(player_t* player, grid_t* grid);

			namespace gfx
			{
				void draw(console_t* console, player_t* player);
			}

			namespace position
			{
				point_t get(const player_t* player);
				void set(player_t* player, const point_t& position);
			}

			namespace direction
			{
				void request_change(player_t* player, int32_t new_direction);
			}
			
			namespace score
			{
				void add(player_t* player, int32_t delta);
				void set(player_t* player, int32_t score);
				int32_t get(const player_t* player);
			}

			namespace lives
			{
				void set(player_t* player, int32_t lives);
				int32_t get(const player_t* player);
			}
		}
	}
}

#endif // !_PACMAN_GAME_PLAYER_H_
