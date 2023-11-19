#ifndef _PACMAN_INPUT_H_
#define _PACMAN_INPUT_H_

#include "base.h"

namespace pacman
{
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
}

#endif // !_PACMAN_INPUT_H_

