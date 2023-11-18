#include "pacman.h"

namespace pacman
{
	namespace console
	{
		namespace cell
		{
			static constexpr float width = 8.0f;
			static constexpr float height = 8.0f;
		}

		typedef struct cell_t
		{
			int8_t m_background;
			int8_t m_foreground;
			uint8_t m_data;
		} cell_t;
	}

	typedef struct console_t
	{
		console::cursor_t m_cursor;
		int8_t m_background;
		int8_t m_foreground;
		console::cell_t* m_data;
		int8_t m_width;
		int8_t m_height;
		console::palette_t m_palette;
	} console_t;

	namespace console
	{
		console_t* create(int8_t width, int8_t height)
		{
			console_t* console = new console_t;
			if (console)
			{
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

				for (int32_t i = 0; i < palette::size; ++i)
				{
					console->m_palette[i] = default_palette[i];
				}

				console->m_data = new cell_t[width * height];
				if (console->m_data)
				{
					console->m_width = width;
					console->m_height = height;
					clear(console);
				}
				else
				{
					delete console;
					console = nullptr;
				}
			}
			return console;
		}

		void destroy(console_t* console)
		{
			if (console)
			{
				delete console;
			}
		}

		void clear(console_t* console)
		{
			console->m_cursor = { 0.0f, 0.0f };
			console->m_foreground = 15;
			console->m_background = 1;
			for (int8_t j = 0; j < console->m_height; ++j)
			{
				for (int8_t i = 0; i < console->m_width; ++i)
				{
					console->m_data[i + j * console->m_width].m_data = 0;
				}
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

		namespace palette
		{
			void set(console_t* console, int8_t index, uint32_t rgba)
			{
				if (index >= 0 && index < palette::size)
				{
					console->m_palette[index] = rgba;
				}
			}
			
			void set(console_t* console, const palette_t& palette)
			{
				for (int32_t index = 0; index < palette::size; ++index)
				{
					console->m_palette[index] = palette[index];
				}
			}
			
			uint32_t get(const console_t* console, int8_t index)
			{
				if (index >= 0 && index < palette::size)
				{
					return console->m_palette[index];
				}
				return -1;
			}

			void get(const console_t* console, palette_t& palette)
			{
				for (int32_t index = 0; index < palette::size; ++index)
				{
					palette[index] = console->m_palette[index];
				}
			}

			namespace background
			{
				void set(console_t* console, int8_t index)
				{
					if (index >= 0 && index < palette::size)
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
					if (index >= 0 && index < palette::size)
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
			void out(console_t* console, uint8_t c)
			{
				cell_t* cell = console->m_data + (console->m_cursor.x + console->m_cursor.y * console->m_width);

				cell->m_background = console->m_background;
				cell->m_foreground = console->m_foreground;
				cell->m_data = c;

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

			//void out(console_t* console, const std::string& string)
			//{
			//	for (auto i : string)
			//	{
			//		text::out(console, i);
			//	}
			//}
		}

		void draw(const console_t* console, const font_t* font, const point_t& point)
		{
			point_t cursor = point;

			for (int8_t j = 0; j < console->m_height; ++j)
			{
				for (int8_t i = 0; i < console->m_width; ++i)
				{
					cursor.x = point.x + cell::width * (float)i;
					cursor.y = point.y + cell::height * (float)j;
					const console::cell_t& cell = console->m_data[i + j * console->m_width];
					font::draw(font, pacman::color::map_rgba(console->m_palette[cell.m_background]), cursor, 219);
					if (cell.m_data != ' ')
					{
						font::draw(font, pacman::color::map_rgba(console->m_palette[cell.m_foreground]), cursor, cell.m_data);
					}
				}
			}
		}
	}
}