#ifndef _PACMAN_GAME_DEFINES_H_
#define _PACMAN_GAME_DEFINES_H_

#include "base.h"

namespace pacman
{
	namespace game
	{
		namespace direction
		{
			enum
			{
				UNDEFINED = -1,
				UP,
				DOWN,
				LEFT,
				RIGHT,
				COUNT
			};
		}

	}
}

#endif // !_PACMAN_GAME_DEFINES_H_
