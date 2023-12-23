#include "game_player.h"

namespace pacman
{
	namespace game
	{
		namespace defaults
		{
			static constexpr point_t POSITION{ 108.0f, 208.0f };
			static constexpr int32_t STATUS{ 0 };
			static constexpr int32_t FRAME{ 1 };
			static constexpr int32_t LIVES{ 3 };
			static constexpr int32_t DIRECTION{ game::direction::LEFT };
		}

		typedef struct player_t
		{
			point_t m_position{ defaults::POSITION };
			int32_t m_status{ defaults::STATUS };
			int32_t m_frame{ defaults::FRAME };
			int32_t m_score{ 0 };
			int32_t m_lives{ defaults::LIVES };
			int32_t m_direction{ defaults::DIRECTION };
			int32_t m_last_direction_request{ game::direction::UNDEFINED };
		} player_t;

		namespace player
		{

			namespace score
			{
				static constexpr int32_t DOT = 10;
				static constexpr int32_t POWERUP = 100;
			}

			namespace celltype
			{
				static constexpr int32_t WALL = 0x80;
				static constexpr int32_t EMPTY = 0x20;
			}

			namespace frame
			{
				static constexpr int32_t COUNT = 4;
			}
	
			player_t* create()
			{
				player_t* player = new player_t;
				if (player)
				{
					reset(player);
				}
				return player;
			}

			void destroy(player_t* player)
			{
				if (player)
				{
					delete player;
				}
			}

			void reset(player_t* player)
			{
				player->m_position = { defaults::POSITION };
				player->m_status = defaults::STATUS;
				player->m_frame = defaults::FRAME;
				player->m_score = 0;
				player->m_lives = defaults::LIVES;
				player->m_direction = defaults::DIRECTION;
				player->m_last_direction_request = game::direction::UNDEFINED;
			}

			void update(player_t* player, grid_t* grid)
			{
				static constexpr float MOVEMENT = (float)(font::glyph::SIZE / frame::COUNT);

				if (player->m_frame == 3)
				{
					static constexpr int32_t DELTA_X[game::direction::COUNT] = { 0, 0, -1, 1 };
					static constexpr int32_t DELTA_Y[game::direction::COUNT] = { -1, 1, 0, 0 };
					static uint8_t cells[game::direction::COUNT] = { 0, 0, 0, 0 };
					static int32_t x = 0;
					static int32_t y = 0;

					for (int32_t i = 0; i < game::direction::COUNT; ++i)
					{
						cells[i] = 0;

					}
					x = ((int32_t)player->m_position.x) >> pacman::font::glyph::SHIFT;
					y = ((int32_t)player->m_position.y) >> pacman::font::glyph::SHIFT;

					if (player->m_status >= 0)
					{
						if (player->m_direction == game::direction::LEFT && x == -1)
						{
							player->m_position.x = (float)(grid::WIDTH * font::glyph::SIZE);
						}
						if (player->m_direction == game::direction::RIGHT && x == grid::WIDTH)
						{
							player->m_position.x = -(float)(font::glyph::SIZE);
						}
					}

					uint8_t cell = grid::cell::get(grid, x, y);
					int32_t type = grid::cell::type::get(cell);

					switch (type)
					{
					case grid::cell::type::EMPTY:		break;
					case grid::cell::type::TEXT:		break;
					case grid::cell::type::WALL:		break;
					case grid::cell::type::DOOR:		break;
					case grid::cell::type::DOT:			
					{
						player->m_score += score::DOT;
						grid::cell::set(grid, x, y, celltype::EMPTY);
					} break;
					case grid::cell::type::POWERUP:
					{
						player->m_score += score::POWERUP;
						grid::cell::set(grid, x, y, celltype::EMPTY);
					} break;
					}

					// check can keep going in same direction			

					for (int32_t i = 0; i < game::direction::COUNT; ++i)
					{
						cells[i] = grid::cell::get(grid, x + DELTA_X[i], y + DELTA_Y[i]);
					}

					if (x <= 0 || x >= (grid::WIDTH - 1))
					{
						cells[game::direction::UP] = 
						cells[game::direction::DOWN] = celltype::WALL;
						cells[game::direction::LEFT] = 
						cells[game::direction::RIGHT] = celltype::EMPTY;
					}

					cell = cells[player->m_direction];
					type = grid::cell::type::get(cell);

					if (type == grid::cell::type::DOOR ||
						type == grid::cell::type::WALL)
					{
						player->m_status = -1;
					}

					// was there a direction change request
					if (player->m_last_direction_request >= 0)
					{
						cell = grid::cell::get(grid, x + DELTA_X[player->m_last_direction_request], y + DELTA_Y[player->m_last_direction_request]);
						type = grid::cell::type::get(cell);

						if (!(type == grid::cell::type::DOOR ||
							type == grid::cell::type::WALL))
						{
							player->m_direction = player->m_last_direction_request;
							player->m_status = 0;
							player->m_last_direction_request = game::direction::UNDEFINED;
						}
					}
				}

				if (player->m_status >= 0)
				{
					if (player->m_direction >= 0)
					{
						++player->m_frame;
						if (player->m_frame == frame::COUNT)
						{
							player->m_frame = 0;
						}
					}

					switch (player->m_direction)
					{
					case game::direction::LEFT:
					{
						player->m_position.x -= MOVEMENT;
					} break;
					case game::direction::RIGHT:
					{
						player->m_position.x += MOVEMENT;
					} break;
					case game::direction::UP:
					{
						player->m_position.y -= MOVEMENT;
					} break;
					case game::direction::DOWN:
					{
						player->m_position.y += MOVEMENT;
					} break;
					}
				}
			}

			namespace direction
			{
				void request_change(player_t* player, int32_t new_direction)
				{
					if (new_direction >= 0 && new_direction < game::direction::COUNT)
					{
						player->m_last_direction_request = new_direction;
					}
				}
			}

			namespace gfx
			{
				void draw(console_t* console, player_t* player)
				{
					static constexpr int32_t VERTICAL_FRAMES[frame::COUNT] =
					{
						game::sprite_list::PACMAN_FRAME_03,
						game::sprite_list::PACMAN_FRAME_00,
						game::sprite_list::PACMAN_FRAME_03,
						game::sprite_list::PACMAN_FRAME_04
					};
					static constexpr int32_t HORIZONTAL_FRAMES[frame::COUNT] =
					{
						game::sprite_list::PACMAN_FRAME_01,
						game::sprite_list::PACMAN_FRAME_00,
						game::sprite_list::PACMAN_FRAME_01,
						game::sprite_list::PACMAN_FRAME_02
					};
					static const int32_t* frames = nullptr;
					static constexpr point_t EXTRA_LIVES_POSITION = 
					{
						(float)font::glyph::SIZE * 2.0f, 
						(float)font::glyph::SIZE* ((float)grid::HEIGHT - 2.0f)
					};

					if (player->m_direction == game::direction::UP ||
						player->m_direction == game::direction::DOWN)
					{
						frames = VERTICAL_FRAMES;
					}
					else
					{
						frames = HORIZONTAL_FRAMES;
					}

					int32_t flags = 0;
					if (player->m_direction == game::direction::UP)
					{
						flags = pacman::console::sprite::draw_flags::FLIP_VERTICAL;
					}
					if (player->m_direction == game::direction::LEFT)
					{
						flags = pacman::console::sprite::draw_flags::FLIP_HORIZONTAL;
					}

					game::sprite_list::gfx::draw(console, frames[player->m_frame], { player->m_position.x - (float)(font::glyph::SIZE >> 1), player->m_position.y - (float)(font::glyph::SIZE >> 1) }, flags);

					for (int32_t i = 1; i < player->m_lives; ++i)
					{
						game::sprite_list::gfx::draw(console, game::sprite_list::PACMAN_FRAME_01, { EXTRA_LIVES_POSITION.x + (float)(i << (font::glyph::SHIFT + 1)), EXTRA_LIVES_POSITION.y}, console::sprite::draw_flags::FLIP_HORIZONTAL);
					}
				}
			}

			namespace position
			{
				point_t get(const player_t* player)
				{
					return player->m_position;
				}

				void set(player_t* player, const point_t& position)
				{
					player->m_position = position;
				}
			}

			namespace score
			{
				void set(player_t* player, int32_t score)
				{
					player->m_score = score;
				}

				void add(player_t* player, int32_t delta)
				{
					player->m_score += delta;
				}

				int32_t get(const player_t* player)
				{
					return player->m_score;
				}
			}

			namespace lives
			{
				void set(player_t* player, int32_t lives)
				{
					player->m_lives = lives;
				}

				int32_t get(const player_t* player)
				{
					return player->m_lives;
				}
			}
		}
	}
}
