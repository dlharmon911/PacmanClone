#ifndef _PACMAN_CLONE_H_
#define _PACMNA_CLONE_H_

#include <cstdarg>
#include <string>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

//#define INCLUDE_JSON_FONT_FUNCTIONS
#ifdef INCLUDE_JSON_FONT_FUNCTIONS
#include <allegro5/allegro_image.h>
#include <nlohmann/json.hpp>
#endif // INCLUDE_JSON_FONT_FUNCTIONS

namespace pacman
{
	using bitmap_t = ALLEGRO_BITMAP;
	using bitmap_locked_region_t = ALLEGRO_LOCKED_REGION;
	using condition_t = ALLEGRO_COND;
	using config_t = ALLEGRO_CONFIG;
	using display_t = ALLEGRO_DISPLAY;
	using event_queue_t = ALLEGRO_EVENT_QUEUE;
	using file_t = ALLEGRO_FILE;
	//using font_t = ALLEGRO_FONT;
	using file_system_entry_t = ALLEGRO_FS_ENTRY;
	using mouse_cursor_t = ALLEGRO_MOUSE_CURSOR;
	using mutex_t = ALLEGRO_MUTEX;
	using path_t = ALLEGRO_PATH;
	using thread_t = ALLEGRO_THREAD;
	using timer_t = ALLEGRO_TIMER;
	using user_event_source_t = ALLEGRO_EVENT_SOURCE;
	//using menu_t = ALLEGRO_MENU;
	using ustring_t = ALLEGRO_USTR;

	using color_t = ALLEGRO_COLOR;
	using display_mode_t = ALLEGRO_DISPLAY_MODE;
	using event_t = ALLEGRO_EVENT;
	using file_interface_t = ALLEGRO_FILE_INTERFACE;
	using file_system_interface_t = ALLEGRO_FS_INTERFACE;
	using joystick_t = ALLEGRO_JOYSTICK;
	using joystick_state_t = ALLEGRO_JOYSTICK_STATE;
	using keyboard_state_t = ALLEGRO_KEYBOARD_STATE;
	using locked_region_t = ALLEGRO_LOCKED_REGION;
	using memory_interface_t = ALLEGRO_MEMORY_INTERFACE;
	using mouse_state_t = ALLEGRO_MOUSE_STATE;
	using state_t = ALLEGRO_STATE;
	using timeout_t = ALLEGRO_TIMEOUT;
	using transform_t = ALLEGRO_TRANSFORM;
	using userEvent_t = ALLEGRO_USER_EVENT;
	using ustring_info_t = ALLEGRO_USTR_INFO;

	template <typename T>
	struct vec2_t
	{
		T x;
		T y;
		constexpr vec2_t() : x(0.0f), y(0.0f) { }
		constexpr vec2_t(T _x, T _y) : x(_x), y(_y) { }
		constexpr vec2_t(const vec2_t& v) : x(v.x), y(v.y) { }

		template <typename Q>
		constexpr vec2_t(Q _x, Q _y) : x((T)_x), y((T)_y) { }
	};

	using point_t = vec2_t<float>;
	using dim_t = vec2_t<float>;

	namespace hex
	{
		uint32_t from_char(int32_t c);
		int32_t to_char(uint32_t v);
	}

	namespace color
	{
		color_t map_rgba(uint32_t color);
		color_t map_rgb(uint32_t color);
		uint32_t unmap_rgb(color_t color);
		uint32_t unmap_rgba(color_t color);
		bool are_equal(const color_t& a, const color_t& b);
	}

	typedef struct font_t font_t;
	namespace font
	{

		font_t* create_default();
		font_t* create_from_data_array(const uint8_t* data, int32_t count, int32_t start = 0x20);
		bool save_to_file(font_t* font, const std::string& filename);
		void destroy(font_t* font);

#ifdef INCLUDE_JSON_FONT_FUNCTIONS
		font_t* load_from_json_file(const std::string& filename);
		font_t* load_from_bitmap_file(const std::string& filename, int32_t start);
		bool save_to_json_file(font_t* font, const std::string& filename);
#endif // INCLUDE_JSON_FONT_FUNCTIONS

		typedef struct glyph_t glyph_t;
		namespace glyph
		{
			static constexpr int32_t size = 8;

			glyph_t* get(font_t* font, int32_t index);
			bool set(glyph_t* glyph, const uint8_t* data);
			bool set(glyph_t* glyph, const std::string& string_16);
			void set(font_t* font, int32_t index, const std::string& string_16);
		}

		enum class alignment_t
		{
			left,
			right,
			centre
		};

		void draw(const font_t* font, color_t color, const point_t& point, uint8_t c);
		void draw(const font_t* font, color_t color, const point_t& point, alignment_t alignment, const std::string& text);
		void draw(const font_t* font, color_t color, const point_t& point, alignment_t alignment, const char* format, ...);
	}

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

		void draw(console_t* console, const sprite_t* sprite, const point_t& point, int32_t flags = draw_flags::none);
		void draw(console_t* console, const layer_t* layers, int32_t begin, int32_t end, const point_t& point, int32_t flags = draw_flags::none);
	}









	namespace input
	{
		typedef struct button_t
		{
			bool m_is_pressed;
			bool m_was_pressed;
		} button_t;

		namespace mouse
		{
			extern point_t m_pos;
			extern point_t m_wheel;
			static constexpr int32_t button_count = 8;
			extern button_t m_button[button_count];
		}
		namespace keyboard
		{
			static constexpr int32_t button_count = ALLEGRO_KEY_MAX;
			extern button_t m_button[button_count];
		}
		void acknowledge_button_presses();
	}

	typedef struct game_t game_t;
	namespace game
	{
		namespace sprite
		{
			static constexpr uint8_t pacman_frame_00 = 0x00;
			static constexpr uint8_t pacman_frame_01 = 0x01;
			static constexpr uint8_t pacman_frame_02 = 0x02;
			static constexpr uint8_t pacman_frame_03 = 0x03;
			static constexpr uint8_t pacman_frame_04 = 0x04;
			
			static constexpr uint8_t ghost_blinky_frame_00 = 0x05;
			static constexpr uint8_t ghost_blinky_frame_01 = 0x06;

			static constexpr uint8_t ghost_pinky_frame_00 = 0x07;
			static constexpr uint8_t ghost_pinky_frame_01 = 0x08;

			static constexpr uint8_t ghost_inky_frame_00 = 0x09;
			static constexpr uint8_t ghost_inky_frame_01 = 0x0a;
			
			static constexpr uint8_t ghost_clyde_frame_00 = 0x0b;
			static constexpr uint8_t ghost_clyde_frame_01 = 0x0c;

			static constexpr uint8_t ghost_afraid_frame_00 = 0x0d;
			static constexpr uint8_t ghost_afraid_frame_01 = 0x0e;
			static constexpr uint8_t ghost_afraid_frame_02 = 0x0f;
			static constexpr uint8_t ghost_afraid_frame_03 = 0x10;

			static constexpr uint8_t ghost_eyes_frame_00 = 0x11;
			static constexpr uint8_t ghost_eyes_frame_01 = 0x12;
			static constexpr uint8_t ghost_eyes_frame_02 = 0x13;
			static constexpr uint8_t ghost_eyes_frame_03 = 0x14;

		};

		namespace color
		{
			static constexpr int8_t black = 0;
			static constexpr int8_t wall = 1;			// (blue)			0x2121de
			static constexpr int8_t pacman = 2;			// (yellow)		0xffff00
			static constexpr int8_t blinky = 3;			// (red)		0xff0000
			static constexpr int8_t pinky = 4;			// (pink)		0xffb8de
			static constexpr int8_t inky = 5;			// (cyan)		0x00ffde
			static constexpr int8_t clyde = 6;			// (orange)		0xffbb47
			static constexpr int8_t dot = 7;			//				0xffbb97
			static constexpr int8_t cherry_stem = 8;	//			0xde9747
			static constexpr int8_t text = 9;			// (white)		0xdedede
			static constexpr int8_t eyes = 10;
			static constexpr int8_t undef_11 = 11;
			static constexpr int8_t undef_12 = 12;
			static constexpr int8_t undef_13 = 13;
			static constexpr int8_t undef_14 = 14;
			static constexpr int8_t undef_15 = 15;
		}

		namespace grid
		{
			static constexpr int32_t width = 28;
			static constexpr int32_t height = 36;
		}

		namespace font
		{
			font_t* create();
		}

		game_t* create();
		void destroy(game_t* game);
		void reset(game_t* game);
		void set_palette(console_t* console);

		namespace console
		{
			void draw_grid(console_t* console, const game_t* game);
			void draw_sprites(console_t* console, const game_t* game);
		}
	}

	namespace application
	{
		int32_t run(const std::vector<std::string>& argList);
	}
}

#endif // !_PACMAN_CLONE_H_
