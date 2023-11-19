#ifndef _PACMAN_BASE_H_
#define _PACMAN_BASE_H_

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
}

#endif // !_PACMAN_BASE_H_
