#ifndef _PACMAN_HEX_H_
#define _PACMAN_HEX_H_

#include "base.h"

namespace pacman
{
	namespace hex
	{
		uint32_t from_char(int32_t c);
		int32_t to_char(uint32_t v);
	}
}

#endif // !_PACMAN_HEX_H_

