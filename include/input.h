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
			static constexpr int32_t BUTTON_COUNT = 8;

			extern point_t m_pos;
			extern point_t m_wheel;
			extern button_t m_button[BUTTON_COUNT];
		}
		namespace keyboard
		{
			static constexpr int32_t BUTTON_COUNT = ALLEGRO_KEY_MAX;
			extern button_t m_button[BUTTON_COUNT];
		}
		void acknowledge_button_presses();
	}
}

#endif // !_PACMAN_INPUT_H_

