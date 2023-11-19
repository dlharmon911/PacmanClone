#ifndef _PACMAN_CONSOLE_H_
#define _PACMAN_CONSOLE_H_

#include "base.h"
#include "color.h"
#include "font.h"

namespace pacman
{
	typedef struct console_t console_t;
	namespace console
	{
		console_t* create(int8_t width = 40, int8_t height = 25);
		void destroy(console_t* console);
		void clear(console_t* console);
		void draw(const console_t* console, const point_t& point);
		int8_t width(const console_t* console);
		int8_t height(const console_t* console);

		using cursor_t = vec2_t<int>;
		namespace cursor
		{
			const console::cursor_t& get(const console_t* console);
			void set(console_t* console, const console::cursor_t& cursor);
		}

		namespace font
		{
			void set(console_t* console, font_t* font);
			const font_t* get(const console_t* console);
		}

		namespace palette
		{
			static constexpr int32_t size = 16;
		}
		using rgba_t = uint32_t;
		using palette_t = rgba_t[palette::size];
		namespace palette
		{
			void set(console_t* console, int8_t index, uint32_t rgba);
			void set(console_t* console, const palette_t& palette);
			uint32_t get(const console_t* console, int8_t index);
			void get(const console_t* console, palette_t& palette);

			namespace background
			{
				void set(console_t* console, int8_t index);
				int8_t get(const console_t* console);
			}
			namespace foreground
			{
				void set(console_t* console, int8_t index);
				int8_t get(const console_t* console);
			}
		}

		namespace text
		{
			void out(console_t* console, uint8_t c);
			//void out(console_t* console, const std::string& string);
		}
	}
}

#endif // !_PACMAN_CONSOLE_H_

