#include "console.h"

namespace pacman
{
	namespace console
	{
		namespace cell
		{
			static constexpr float width = 8.0f;
			static constexpr float height = 8.0f;
		}
	}

	typedef struct console_t
	{
		console::cursor_t m_cursor = { 0.0f, 0.0f };
		int8_t m_background{ 0 };
		int8_t m_foreground{ 15 };
		int8_t m_width{ 0 };
		int8_t m_height{ 0 };
		bitmap_t* m_bitmap{ nullptr };
		uint8_t* m_data{ nullptr };
		console::palette_t m_palette{};
		font_t* m_font{ nullptr };
	} console_t;

	namespace console
	{
		console_t* create(font_t* font, int32_t width, int32_t height)
		{
			console_t* console = new console_t;

			palette_t default_palette =
			{
				0x000000ff,
				0x0000aaff,
				0x00aa00ff,
				0x00aaaaff,
				0xaa0000ff,
				0xaa00aaff,
				0xaa5500ff,
				0xaaaaaaff,
				0x555555ff,
				0x5555ffff,
				0x55ff55ff,
				0x55ffffff,
				0xff5555ff,
				0xff55ffff,
				0xffff55ff,
				0xffffffff
			};

			if (console)
			{
				console->m_cursor = { 0.0f, 0.0f };
				console->m_background = 0;
				console->m_foreground = 15;
				console->m_width = 0;
				console->m_height = 0;
				console->m_bitmap = nullptr;
				console->m_data = nullptr;
				console->m_font = font;

				if (!(console->m_bitmap = al_create_bitmap(width << 3, height << 3)) ||
					!(console->m_data = new uint8_t[width * height]) ||
					!(console->m_font))
				{
					console::destroy(console);
					return nullptr;
				}

				console->m_width = width;
				console->m_height = height;

				for (int8_t j = 0; j < console->m_height; ++j)
				{
					for (int8_t i = 0; i < console->m_width; ++i)
					{
						console->m_data[i + j * console->m_width] = 0;
					}
				}

				for (int32_t i = 0; i < console::palette::size; ++i)
				{
					console->m_palette[i] = default_palette[i];
				}

				console::clear(console);
			}

			return console;
		}

		void destroy(console_t* console)
		{
			if (console)
			{
				if (console->m_data)
				{
					delete[] console->m_data;
				}

				if (console->m_bitmap)
				{
					al_destroy_bitmap(console->m_bitmap);
				}

				delete console;
			}
		}

		int8_t width(const console_t* console)
		{
			return console->m_width;
		}

		int8_t height(const console_t* console)
		{
			return console->m_height;
		}

		void clear(console_t* console)
		{
			static bitmap_t* target = nullptr;

			target = al_get_target_bitmap();
			al_set_target_bitmap(console->m_bitmap);

			al_clear_to_color(color::map_rgb(console->m_palette[console->m_background]));

			al_set_target_bitmap(target);

			console->m_cursor = { 0.0f, 0.0f };

			for (int8_t j = 0; j < console->m_height; ++j)
			{
				for (int8_t i = 0; i < console->m_width; ++i)
				{
					console->m_data[i + j * console->m_width] = 0;
				}
			}
		}

		namespace gfx
		{
			void draw(const console_t* console, const point_t& point)
			{
				al_draw_bitmap(console->m_bitmap, point.x, point.y, 0);
			}
		}

		namespace cursor
		{
			const console::cursor_t& get(const console_t* console)
			{
				return console->m_cursor;
			}

			void set(console_t* console, const console::cursor_t& cursor)
			{
				console->m_cursor = cursor;
			}
		}

		namespace bitmap
		{
			bitmap_t* get(console_t* console)
			{
				return console->m_bitmap;
			}
		}

		namespace font
		{
			void set(console_t* console, font_t* font)
			{
				console->m_font = font;
			}

			const font_t* get(const console_t* console)
			{
				return console->m_font;
			}

			font_t* get(console_t* console)
			{
				return console->m_font;
			}
		}

		namespace palette
		{
			void set(console_t* console, int8_t index, uint32_t rgba)
			{
				if (index >= 0 && index < console::palette::size)
				{
					console->m_palette[index] = rgba;
				}
			}

			void set(console_t* console, const palette_t& palette)
			{
				for (int32_t index = 0; index < console::palette::size; ++index)
				{
					console->m_palette[index] = palette[index];
				}
			}

			uint32_t get(const console_t* console, int8_t index)
			{
				if (index >= 0 && index < console::palette::size)
				{
					return console->m_palette[index];
				}
				return -1;
			}

			const palette_t& get(const console_t* console)
			{
				return console->m_palette;
			}

			palette_t& get(console_t* console)
			{
				return console->m_palette;
			}

			namespace background
			{
				void set(console_t* console, int8_t index)
				{
					if (index >= 0 && index < console::palette::size)
					{
						console->m_background = index;
					}
				}

				int8_t get(const console_t* console)
				{
					return console->m_background;
				}
			}

			namespace foreground
			{
				void set(console_t* console, int8_t index)
				{
					if (index >= 0 && index < console::palette::size)
					{
						console->m_foreground = index;
					}
				}

				int8_t get(const console_t* console)
				{
					return console->m_foreground;
				}
			}
		}

		namespace text
		{
			namespace gfx
			{
				void draw(console_t* console, uint8_t c)
				{
					static ALLEGRO_BITMAP* target{ nullptr };
					static point_t point{ 0.0f, 0.0f };
					static color_t background = { 0.0f, 0.0f, 0.0f, 0.0f };
					static color_t foreground = { 0.0f, 0.0f, 0.0f, 0.0f };

					point = { float(console->m_cursor.x * pacman::font::glyph::size), float(console->m_cursor.y * pacman::font::glyph::size) };
					background = pacman::color::map_rgba(console->m_palette[console->m_background]);
					foreground = pacman::color::map_rgba(console->m_palette[console->m_foreground]);

					target = al_get_target_bitmap();
					al_set_target_bitmap(console::bitmap::get(console));
					pacman::font::draw(console->m_font, background, point, 255);
					pacman::font::draw(console->m_font, foreground, point, c);
					al_set_target_bitmap(target);

					console->m_data[console->m_cursor.x + console->m_cursor.y * console->m_width] = c;

					++console->m_cursor.x;
					if (console->m_cursor.x == console->m_width)
					{
						console->m_cursor.x = 0;
						++console->m_cursor.y;
						if (console->m_cursor.y == console->m_height)
						{
							console->m_cursor.y = 0;
						}
					}
				}
			}
		}

		namespace sprite
		{
			namespace gfx
			{
				void draw(console_t* console, const sprite_t* sprite, const point_t& point, int32_t flags)
				{
					draw(console, sprite->m_layers, sprite->m_begin, sprite->m_end, point, flags);
				}

				void draw(console_t* console, const layer_t* layers, int32_t begin, int32_t end, const point_t& point, int32_t flags)
				{
					static ALLEGRO_BITMAP* target = nullptr;
					static ALLEGRO_TRANSFORM backup;
					static ALLEGRO_TRANSFORM t;
					static font_t* font = nullptr;
					static palette_t& palette = console::palette::get(console);

					font = console::font::get(console);

					target = al_get_target_bitmap();
					al_set_target_bitmap(console::bitmap::get(console));

					al_copy_transform(&backup, al_get_current_transform());
					al_identity_transform(&t);
					al_translate_transform(&t, -point.x, -point.y);

					if (flags & draw_flags::flip_horizontal)
					{
						al_scale_transform(&t, -1.0f, 1.0f);
						al_translate_transform(&t, (float)pacman::font::glyph::size * 2.0f, 0.0f);
					}

					if (flags & draw_flags::flip_vertical)
					{
						al_scale_transform(&t, 1.0f, -1.0f);
						al_translate_transform(&t, 0.0f, (float)pacman::font::glyph::size * 2.0f);
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
								p.x += i * (float)pacman::font::glyph::size;
								p.y += j * (float)pacman::font::glyph::size;

								color_t color = color::map_rgba(palette[layers[layer + begin].color_index]);
								uint8_t c = layers[layer + begin].character[index];
								pacman::font::draw(font, color, p, layers[layer + begin].character[index]);
								++index;
							}
						}
					}
					al_use_transform(&backup);
					al_set_target_bitmap(target);
				}
			}
		}
	}
}