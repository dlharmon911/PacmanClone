#ifndef _PACMAN_GAME_SPRITE_LIST_H_
#define _PACMAN_GAME_SPRITE_LIST_H_

#include "base.h"
#include "font.h"
#include "console.h"
#include "game_color_list.h"

namespace pacman
{
	namespace game
	{
		namespace sprite_list
		{
			enum
			{
				PACMAN_FRAME_00,
				PACMAN_FRAME_01,
				PACMAN_FRAME_02,
				PACMAN_FRAME_03,
				PACMAN_FRAME_04,
				GHOST_BLINKY_FRAME_00,
				GHOST_BLINKY_FRAME_01,
				GHOST_PINKY_FRAME_00,
				GHOST_PINKY_FRAME_01,
				GHOST_INKY_FRAME_00,
				GHOST_INKY_FRAME_01,
				GHOST_CLYDE_FRAME_00,
				GHOST_CLYDE_FRAME_01,
				GHOST_AFRAID_FRAME_00,
				GHOST_AFRAID_FRAME_01,
				GHOST_AFRAID_FRAME_02,
				GHOST_AFRAID_FRAME_03,
				GHOST_EYES_FRAME_00,
				GHOST_EYES_FRAME_01,
				GHOST_EYES_FRAME_02,
				GHOST_EYES_FRAME_03,
				COUNT
			};

			namespace gfx
			{
				void draw(console_t* console, int32_t index, const point_t& point, int32_t flags = pacman::console::sprite::draw_flags::NONE);
			}
		}
	}
}

#endif // !_PACMAN_GAME_SPRITE_LIST_H_

