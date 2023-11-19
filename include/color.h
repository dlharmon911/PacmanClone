#ifndef _PACMAN_COLOR_H_
#define _PACMAN_COLOR_H_

#include "base.h"

namespace pacman
{
	namespace color
	{
		color_t map_rgba(uint32_t color);
		color_t map_rgb(uint32_t color);
		uint32_t unmap_rgb(color_t color);
		uint32_t unmap_rgba(color_t color);
		bool are_equal(const color_t& a, const color_t& b);
	}
}

#endif // !_PACMAN_COLOR_H_
