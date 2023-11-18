#include "pacman.h"

namespace pacman
{
	typedef struct sprite_t
	{
		sprite::layer_t* layers;
		int32_t count;
	} sprite_t;

	namespace sprite
	{
		sprite_t* create(const layer_t* layers)
		{
			sprite_t* sprite = nullptr;
			int32_t count = 0;
			while (layers[count].color_index >= 0)
			{
				++count;
			}

			if (layers && count)
			{
				sprite = new sprite_t;
				if (sprite)
				{
					sprite->layers = new layer_t[count];
					if (sprite->layers)
					{
						sprite->count = count;
						for (int32_t layer = 0; layer < count; ++layer)
						{
							sprite->layers[layer].color_index = layers[layer].color_index;
							for (int32_t c = 0; c < 4; ++c)
							{
								sprite->layers[layer].character[c] = layers[layer].character[c];
							}
						}
					}
					else
					{
						delete sprite;
						sprite = nullptr;
					}
				}
			}

			return sprite;
		}

		void destroy(sprite_t* sprite)
		{
			if (sprite)
			{
				if (sprite->layers)
				{
					delete[] sprite->layers;
				}
				delete sprite;
			}
		}

		void draw(console_t* console, const font_t* font, const sprite_t* sprite, const point_t& point)
		{
			for (int32_t layer = 0; layer < sprite->count; ++layer)
			{
				int index = 0;
				for (int32_t j = 0; j < 2; ++j)
				{
					for (int32_t i = 0; i < 2; ++i)
					{
						point_t p = point;
						p.x += i * 8.0f;
						p.y += j * 8.0f;

						color_t color = color::map_rgba(console::palette::get(console, sprite->layers[layer].color_index));
						uint8_t c = sprite->layers[layer].character[index];
						pacman::font::draw(font, color, p, sprite->layers[layer].character[index]);
						++index;
					}
				}
			}
		}
	}


}
