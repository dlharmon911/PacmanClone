#include "sprite.h"

namespace pacman
{
	namespace sprite
	{
		void draw(console_t* console, const sprite_t* sprite, const point_t& point, int32_t flags)
		{
			draw(console, sprite->m_layers, sprite->m_begin, sprite->m_end, point, flags);
		}

		void draw(console_t* console, const layer_t* layers, int32_t begin, int32_t end, const point_t& point, int32_t flags)
		{
			const font_t* font = console::font::get(console);
			ALLEGRO_TRANSFORM backup;
			ALLEGRO_TRANSFORM t;

			al_copy_transform(&backup, al_get_current_transform());
			al_identity_transform(&t);
			al_translate_transform(&t, -point.x, -point.y);

			if (flags & draw_flags::flip_horizontal)
			{
				al_scale_transform(&t, -1.0f, 1.0f);
				al_translate_transform(&t, 16.0f, 0.0f);
			}

			if (flags & draw_flags::flip_vertical)
			{
				al_scale_transform(&t, 1.0f, -1.0f);
				al_translate_transform(&t, 0.0f, 16.0f);
			}

			al_translate_transform(&t, point.x, point.y);
			al_use_transform(&t);
			for (int32_t layer = 0; layer < (1 + (end - begin)); ++layer)
			{
				int index = 0;
				for (int32_t j = 0; j < 2; ++j)
				{
					for (int32_t i = 0; i < 2; ++i)
					{
						point_t p = point;
						p.x += i * 8.0f;
						p.y += j * 8.0f;

						color_t color = color::map_rgba(console::palette::get(console, layers[layer + begin].color_index));
						uint8_t c = layers[layer + begin].character[index];
						pacman::font::draw(font, color, p, layers[layer + begin].character[index]);
						++index;
					}
				}
			}
			al_use_transform(&backup);
		}
	}
}