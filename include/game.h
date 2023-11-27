#ifndef _PACMAN_GAME_H_
#define _PACMAN_GAME_H_

#include "base.h"
#include "font.h"
#include "console.h"
#include "game_color_list.h"
#include "game_sprite_list.h"
#include "game_player.h"
#include "game_grid.h"

namespace pacman
{
	typedef struct game_t game_t;
	namespace game
	{
		game_t* create();
		void destroy(game_t* game);
		void reset(game_t* game);
		void update(game_t* game);

		namespace input
		{
			void keypressed(game_t* game, int32_t direction);
		}

		namespace font
		{
			font_t* create();
		}

		namespace palette
		{
			void set(console_t* console);
		}

		namespace gfx
		{
			void draw(console_t* console, const game_t* game);
		}
	}
}

#endif // !_PACMAN_GAME_H_

