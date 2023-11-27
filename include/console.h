#ifndef _PACMAN_CONSOLE_H_
#define _PACMAN_CONSOLE_H_

#include "base.h"
#include "font.h"

namespace pacman
{
	typedef struct console_t console_t;
	namespace console
	{
		console_t* create(font_t* font, int32_t width = 40, int32_t height = 25);
		void destroy(console_t* console);
		int8_t width(const console_t* console);
		int8_t height(const console_t* console);
		void clear(console_t* console);

		namespace gfx
		{
			void draw(const console_t* console, const point_t& point);
		}

		using cursor_t = vec2_t<int>;
		namespace cursor
		{
			const console::cursor_t& get(const console_t* console);
			void set(console_t* console, const console::cursor_t& cursor);
		}

		namespace bitmap
		{
			bitmap_t* get(console_t* console);
		}

		namespace font
		{
			void set(console_t* console, font_t* font);
			const font_t* get(const console_t* console);
			font_t* get(console_t* console);
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
			const palette_t& get(const console_t* console);
			palette_t& get(console_t* console);

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
			namespace gfx
			{
				void draw(console_t* console, uint8_t c);
			}
		}

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
			sprite::layer_t* m_layers{ nullptr };
			int32_t m_begin{ 0 };
			int32_t m_end{ 0 };
		} sprite_t;

		namespace sprite
		{
			namespace draw_flags
			{
				static constexpr int32_t none = 0;
				static constexpr int32_t flip_horizontal = 1;
				static constexpr int32_t flip_vertical = 2;
			};

			namespace gfx
			{
				void draw(console_t* console, const sprite_t* sprite, const point_t& point, int32_t flags = draw_flags::none);
				void draw(console_t* console, const layer_t* layers, int32_t begin, int32_t end, const point_t& point, int32_t flags = draw_flags::none);
			}
		}
	}
}

#endif // !_PACMAN_CONSOLE_H_

