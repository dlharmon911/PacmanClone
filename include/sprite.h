#ifndef _PACMAN_SPRITE_H_
#define _PACMAN_SPRITE_H_

#include "base.h"
#include "console.h"

namespace pacman
{
	namespace sprite
	{
		typedef struct layer_t
		{
			int8_t color_index;
			uint8_t character[4];
		} layer_t;
	}

	typedef struct sprite_t
	{
		sprite::layer_t* m_layers;
		int32_t m_begin;
		int32_t m_end;
	} sprite_t;

	namespace sprite
	{
		namespace draw_flags
		{
			static constexpr int32_t none = 0;
			static constexpr int32_t flip_horizontal = 1;
			static constexpr int32_t flip_vertical = 2;
		};
		\
		void draw(console_t* console, const sprite_t* sprite, const point_t& point, int32_t flags = draw_flags::none);
		void draw(console_t* console, const layer_t* layers, int32_t begin, int32_t end, const point_t& point, int32_t flags = draw_flags::none);
	}
}

#endif // !_PACMAN_SPRITE_H_

