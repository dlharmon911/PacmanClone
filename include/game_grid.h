#ifndef _PACMAN_GAME_GRID_H_
#define _PACMAN_GAME_GRID_H_

#include "base.h"
#include "console.h"

namespace pacman
{
	namespace game
	{
		typedef struct grid_t grid_t;
		namespace grid
		{
			static constexpr int32_t width = 28;
			static constexpr int32_t height = 36;

			grid_t* create();
			void destroy(grid_t* grid);
			void reset(grid_t* grid);

			namespace cell
			{
				namespace type
				{
					enum
					{
						empty,
						text,
						wall,
						door,
						dot,
						big_dot,
						count
					};
					int32_t get(uint8_t value);
				}
				void set(grid_t* grid, int32_t x, int32_t y, uint8_t value);
				uint8_t get(const grid_t* grid, int32_t x, int32_t y);
			}

			namespace gfx
			{
				void draw(console_t* console, const grid_t* grid);
			}
		}
	}
}

#endif // !_PACMAN_GAME_GRID_H_

