#ifndef _PACMAN_SPRITE_LIST_H_
#define _PACMAN_SPRITE_LIST_H_

#include "base.h"
#include "console.h"
#include "sprite.h"
#include "color_list.h"

namespace pacman
{
	namespace sprite_list
	{
		enum sprite_type : int32_t
		{
			pacman_frame_00,
			pacman_frame_01,
			pacman_frame_02,
			pacman_frame_03,
			pacman_frame_04,
			ghost_blinky_frame_00,
			ghost_blinky_frame_01,
			ghost_pinky_frame_00,
			ghost_pinky_frame_01,
			ghost_inky_frame_00,
			ghost_inky_frame_01,
			ghost_clyde_frame_00,
			ghost_clyde_frame_01,
			ghost_afraid_frame_00,
			ghost_afraid_frame_01,
			ghost_afraid_frame_02,
			ghost_afraid_frame_03,
			ghost_eyes_frame_00,
			ghost_eyes_frame_01,
			ghost_eyes_frame_02,
			ghost_eyes_frame_03
		};

		void draw(console_t* console, int32_t index, const point_t& point, int32_t flags = sprite::draw_flags::none);
	}
}

#endif // !_PACMAN_SPRITE_LIST_H_

