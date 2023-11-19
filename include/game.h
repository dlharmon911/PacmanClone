#ifndef _PACMAN_GAME_H_
#define _PACMAN_GAME_H_

#include "base.h"
#include "font.h"
#include "console.h"
#include "sprite.h"
#include "sprite_list.h"
#include "color_list.h"

namespace pacman
{
	typedef struct game_t game_t;
	namespace game
	{
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

		namespace palette
		{
			void set(console_t* console);
		}

		namespace console
		{
			void draw_grid(console_t* console, const game_t* game);
			void draw_sprites(console_t* console, const game_t* game);
		}
	}
}

#endif // !_PACMAN_GAME_H_

