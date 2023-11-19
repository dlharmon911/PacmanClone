#include "game_player.h"

namespace pacman
{
	namespace game
	{
		typedef struct player_t
		{
			point_t m_position{ 108.0f, 208.0f };
			int32_t m_status{ 0 };
			int32_t m_frame{ 1 };
			int32_t m_score{ 0 };
			int32_t m_lives{ 3 };
			int32_t m_direction{ game::direction::left };
			int32_t m_last_direction_request{ -1 };
		} player_t;

		namespace player
		{
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
				player->m_position = { 108.0f, 208.0f };
				player->m_status = 0;
				player->m_frame = 1;
				player->m_score = 0;
				player->m_lives = 3;
				player->m_direction = game::direction::left;
				player->m_last_direction_request = -1;
			}

			void update(player_t* player, grid_t* grid)
			{
				if (player->m_frame == 3)
				{
					static constexpr int32_t delta_x[4] = { 0, 0, -1, 1 };
					static constexpr int32_t delta_y[4] = { -1, 1, 0, 0 };

					const int32_t x = ((int32_t)player->m_position.x) >> 3;
					const int32_t y = ((int32_t)player->m_position.y) >> 3;

					uint8_t cell = grid::cell::get(grid, x, y);
					int32_t type = grid::cell::type::get(cell);

					switch (type)
					{
					case grid::cell::type::empty:		break;
					case grid::cell::type::text:		break;
					case grid::cell::type::wall:		break;
					case grid::cell::type::door:		break;
					case grid::cell::type::dot:			
					{
						player->m_score -= 90;
						grid::cell::set(grid, x, y, 0x20);
					} break;
					case grid::cell::type::big_dot:
					{
						player->m_score += 100;
						grid::cell::set(grid, x, y, 0x20);
					} break;
					}

					// check can keep going in same direction
					cell = grid::cell::get(grid, x + delta_x[player->m_direction], y + delta_y[player->m_direction]);
					type = grid::cell::type::get(cell);

					if (type == grid::cell::type::door ||
						type == grid::cell::type::wall)
					{
						player->m_status = -1;
					}

					// was there a direction change request
					if (player->m_last_direction_request >= 0)
					{
						cell = grid::cell::get(grid, x + delta_x[player->m_last_direction_request], y + delta_y[player->m_last_direction_request]);
						type = grid::cell::type::get(cell);

						if (!(type == grid::cell::type::door ||
							type == grid::cell::type::wall))
						{
							player->m_direction = player->m_last_direction_request;
							player->m_status = 0;
							player->m_last_direction_request = -1;
						}
					}
				}

				if (player->m_status >= 0)
				{
					if (player->m_direction >= 0)
					{
						++player->m_frame;
						if (player->m_frame == 4)
						{
							player->m_frame = 0;
						}
					}

					switch (player->m_direction)
					{
					case game::direction::left:
					{
						player->m_position.x -= 2;
					} break;
					case game::direction::right:
					{
						player->m_position.x += 2;
					} break;
					case game::direction::up:
					{
						player->m_position.y -= 2;
					} break;
					case game::direction::down:
					{
						player->m_position.y += 2;
					} break;
					}
				}
			}

			namespace direction
			{
				void request_change(player_t* player, int32_t new_direction)
				{
					if (new_direction >= 0 && new_direction < game::direction::count)
					{
						player->m_last_direction_request = new_direction;
					}
				}
			}

			namespace gfx
			{
				void draw(console_t* console, player_t* player)
				{
					static constexpr int32_t vertical_frames[4] =
					{
						game::sprite_list::pacman_frame_03,
						game::sprite_list::pacman_frame_00,
						game::sprite_list::pacman_frame_03,
						game::sprite_list::pacman_frame_04
					};
					static constexpr int32_t horizontal_frames[4] =
					{
						game::sprite_list::pacman_frame_01,
						game::sprite_list::pacman_frame_00,
						game::sprite_list::pacman_frame_01,
						game::sprite_list::pacman_frame_02
					};
					static const int32_t* frames = horizontal_frames;
					static constexpr point_t position_lives = { 16.0f, 272.0f };

					if (player->m_direction == game::direction::up ||
						player->m_direction == game::direction::down)
					{
						frames = vertical_frames;
					}
					else
					{
						frames = horizontal_frames;
					}

					int32_t flags = 0;
					if (player->m_direction == game::direction::up)
					{
						flags = sprite::draw_flags::flip_vertical;
					}
					if (player->m_direction == game::direction::left)
					{
						flags = sprite::draw_flags::flip_horizontal;
					}

					game::sprite_list::draw(console, frames[player->m_frame], { player->m_position.x - 4.0f, player->m_position.y - 4.0f}, flags);

					for (int32_t i = 1; i < player->m_lives; ++i)
					{
						game::sprite_list::draw(console, game::sprite_list::pacman_frame_01, { position_lives.x + (float)(i<<4), position_lives.y}, sprite::draw_flags::flip_horizontal);
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
