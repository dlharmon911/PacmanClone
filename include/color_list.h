#ifndef _PACMAN_COLOR_LIST_H_
#define _PACMAN_COLOR_LIST_H_

#include "base.h"
#include "console.h"

namespace pacman
{
	namespace color_list
	{
		enum color_type : int32_t
		{
			black,			// 0x000000
			blue,			// 0x2121de
			yellow,			// 0xffff00
			red,			// 0xff0000
			pink,			// 0xffb8de
			cyan,			// 0x00ffde
			orange,			// 0xffbb47
			dot,			// 0xffbb97
			brown,			// 0xde9747
			white,			// 0xdedede
			eyes,			// 0xe0ddff
			undef_11,
			undef_12,
			undef_13,
			undef_14,
			undef_15,
		};
	}
}

#endif // !_PACMAN_COLOR_LIST_H_

