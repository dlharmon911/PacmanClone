#include "input.h"

namespace pacman
{
	namespace input
	{
		namespace mouse
		{
			point_t m_pos;
			point_t m_wheel;
			button_t m_button[button_count];
		}
		namespace keyboard
		{
			button_t m_button[button_count];
		}
		void acknowledge_button_presses()
		{
			for (int32_t i = 0; i < mouse::button_count; ++i)
			{
				mouse::m_button[i].m_was_pressed = false;
			}
			for (int32_t i = 0; i < keyboard::button_count; ++i)
			{
				keyboard::m_button[i].m_was_pressed = false;
			}
		}
	}
}
