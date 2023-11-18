#include <limits>
#include <cmath>
#include "pacman.h"

namespace pacman
{
	namespace color
	{
		union _color
		{
			uint32_t i;
			struct
			{
				uint8_t a;
				uint8_t b;
				uint8_t g;
				uint8_t r;
			};
		};

		color_t map_rgba(uint32_t color)
		{
			_color c = { 0 };
			c.i = color;
			return al_map_rgba(c.r, c.g, c.b, c.a);
		}

		color_t map_rgb(uint32_t color)
		{
			return color::map_rgba(0xff | (color << 8));
		}

		uint32_t unmap_rgb(color_t color)
		{
			_color c = { 0 };

			al_unmap_rgba(color, &c.r, &c.g, &c.b, &c.a);

			return (c.i >> 8);
		}

		uint32_t unmap_rgba(color_t color)
		{
			_color c = { 0 };

			al_unmap_rgba(color, &c.r, &c.g, &c.b, &c.a);

			return c.i;
		}

		bool are_equal(const color_t& a, const color_t& b)
		{
			return (unmap_rgba(a) == unmap_rgba(b));
		}
	}
}