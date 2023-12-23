#include "input.h"

namespace pacman
{
	namespace input
	{
		namespace mouse
		{
			point_t m_pos;
			point_t m_wheel;
			button_t m_button[BUTTON_COUNT];
		}
		namespace keyboard
		{
			button_t m_button[BUTTON_COUNT];
		}
		void acknowledge_button_presses()
		{
			for (int32_t i = 0; i < mouse::BUTTON_COUNT; ++i)
			{
				mouse::m_button[i].m_was_pressed = false;
			}
			for (int32_t i = 0; i < keyboard::BUTTON_COUNT; ++i)
			{
				keyboard::m_button[i].m_was_pressed = false;
			}
		}
	}
}
