#include "pacman.h"

namespace pacman
{
	namespace application
	{
		namespace padding
		{
			static constexpr float width = 4.0f;
			static constexpr float height = 4.0f;
		}

		int32_t init(const std::vector<std::string>& argList);
		void shutdown();
		int32_t loop();
		void draw();
		void logic();
		void input();

		display_t* m_display = nullptr;
		event_queue_t* m_event_queue = nullptr;
		timer_t* m_timer = nullptr;
		bitmap_t* m_buffer = nullptr;
		font_t* m_font_default = nullptr;
		font_t* m_font_game = nullptr;
		console_t* m_console = nullptr;
		game_t* m_game = nullptr;
		bool m_kill = false;
		int32_t m_counter = 0;

		static constexpr dim_t DISPLAY_SIZE = { 504.0f, 648.0f };
		static constexpr dim_t BUFFER_SIZE = { (float)(game::grid::width << 3), (float)(game::grid::height << 3) };
		static constexpr double TIMING = 60.0;
		static constexpr const char* APPNAME = "Pacman Clone";
	}


	int32_t application::run(const std::vector<std::string>& argList)
	{
		if (application::init(argList) == 0)
		{
			application::loop();
		}

		application::shutdown();

		return 0;
	}

	int32_t application::init(const std::vector<std::string>& argList)
	{
		std::cout << "Initialization Begin" << std::endl;

		std::cout << "Initializing Allegro Library: ";
		if (!al_init())
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Initializing Image Addon: ";
		if (!al_init_image_addon())
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		// set the directory to the path of the exe
		path_t* base_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
		if (base_path)
		{
			al_make_path_canonical(base_path);
			al_change_directory(al_path_cstr(base_path, ALLEGRO_NATIVE_PATH_SEP));
			al_destroy_path(base_path);
		}

		std::cout << "Initializing Mouse: ";
		if (!al_install_mouse())
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Initializing Keyboard: ";
		if (!al_install_keyboard())
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Display: ";
		al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
		al_set_new_window_title(application::APPNAME);
		m_display = al_create_display(application::DISPLAY_SIZE.x, application::DISPLAY_SIZE.y);
		if (!m_display)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;
		al_clear_to_color(color::map_rgb(0x0));

		bitmap_t* icon = al_load_bitmap("icon.png");
		if (icon)
		{
			al_convert_mask_to_alpha(icon, color::map_rgb(0xff00ff));
			al_set_display_icon(m_display, icon);
			al_destroy_bitmap(icon);
		}

		std::cout << "Creating Bitmap Buffer: ";
		m_buffer = al_create_bitmap(application::BUFFER_SIZE.x, application::BUFFER_SIZE.y);
		if (!m_buffer)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Default Font: ";
		m_font_default = font::create_default();
		if (!m_font_default)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Game Font: ";
		m_font_game = font::create_default();
		if (!m_font_game)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Event Queue: ";
		m_event_queue = al_create_event_queue();
		if (!m_event_queue)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Logic Timer: ";
		m_timer = al_create_timer(1.0 / application::TIMING);
		if (!m_timer)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Console: ";
		m_console = console::create(game::grid::width, game::grid::height);
		if (!m_console)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Game Object: ";
		m_game = game::create();
		if (!m_game)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		game::set_palette(m_console);
		game::modify_game_font(m_font_game);

		console::font::set(m_console, m_font_game);

		al_register_event_source(m_event_queue, al_get_display_event_source(m_display));
		al_register_event_source(m_event_queue, al_get_timer_event_source(m_timer));
		al_register_event_source(m_event_queue, al_get_keyboard_event_source());
		al_register_event_source(m_event_queue, al_get_mouse_event_source());

		srand(time(nullptr));

		al_start_timer(m_timer);

		std::cout << "Initialization Complete" << std::endl << std::endl;

		return 0;
	}

	void application::shutdown()
	{
		std::cout << std::endl << "Shutdown Begin" << std::endl;

		if (m_game)
		{
			game::destroy(m_game);
			m_game = nullptr;
			std::cout << "Game Object Destroyed" << std::endl;
		}

		if (m_console)
		{
			console::destroy(m_console);
			m_console = nullptr;
			std::cout << "Console Destroyed" << std::endl;
		}

		if (m_timer)
		{
			al_stop_timer(m_timer);
			al_destroy_timer(m_timer);
			m_timer = nullptr;
			std::cout << "Timer Destroyed" << std::endl;
		}

		if (m_event_queue)
		{
			al_destroy_event_queue(m_event_queue);
			m_event_queue = nullptr;
			std::cout << "Event Queue Destroyed" << std::endl;
		}

		if (m_font_game)
		{
			font::destroy(m_font_game);
			m_font_game = nullptr;
			std::cout << "Game Font Destroyed" << std::endl;
		}

		if (m_font_default)
		{
			font::destroy(m_font_default);
			m_font_default = nullptr;
			std::cout << "Default Font Destroyed" << std::endl;
		}

		if (m_buffer)
		{
			al_destroy_bitmap(m_buffer);
			m_buffer = nullptr;
			std::cout << "Bitmap Buffer Destroyed" << std::endl;
		}

		if (m_display)
		{
			al_destroy_display(m_display);
			m_display = nullptr;
			std::cout << "Display Destroyed" << std::endl;
		}

		std::cout << "Shutdown Complete" << std::endl << std::endl;
	}

	int32_t application::loop()
	{
		static bitmap_t* target = nullptr;
		static dim_t display_size = { 0.0f, 0.0f };
		static dim_t buffer_size = { 0.0f, 0.0f };

		while (!m_kill)
		{
			buffer_size = dim_t(al_get_bitmap_width(m_buffer), al_get_bitmap_height(m_buffer));
			display_size = dim_t(al_get_display_width(m_display), al_get_display_height(m_display));

			float y = display_size.y / (buffer_size.y + (2.0f * padding::width));
			float x = display_size.x / (buffer_size.x+ (2.0f * padding::height));
			float a = y;

			if (y > x)
			{
				a = x;
			}

			while (m_counter > 0)
			{
				logic();
				input::acknowledge_button_presses();
				--m_counter;
			}
			
			al_clear_to_color(color::map_rgb(0x202050));

			target = al_get_target_bitmap();
			al_set_target_bitmap(m_buffer);


			draw();

			al_set_target_bitmap(target);
			al_draw_scaled_bitmap(m_buffer,
				0.0f,
				0.0f,
				buffer_size.x,
				buffer_size.y,
				(display_size.x - buffer_size.x * a) / 2.0f,
				(display_size.y - buffer_size.y * a) / 2.0f,
				buffer_size.x * a,
				buffer_size.y * a, 0);
			al_flip_display();

			input();

			al_rest(0.01);
		}

		return 0;
	}

	void application::draw()
	{
		pacman::font_t* font = m_font_game;

		if (input::keyboard::m_button[ALLEGRO_KEY_LSHIFT].m_is_pressed)
		{
			font = m_font_default;
		}

		console::font::set(m_console, m_font_game);

		game::draw(m_console, m_game);
		console::draw(m_console, { 0.0f, 0.0f });
	}

	void application::logic()
	{
		if (input::keyboard::m_button[ALLEGRO_KEY_ESCAPE].m_was_pressed)
		{
			m_kill = true;
		}
	}

	void application::input()
	{
		static ALLEGRO_EVENT event;

		while (!al_event_queue_is_empty(m_event_queue))
		{
			al_get_next_event(m_event_queue, &event);

			switch (event.type)
			{
			case ALLEGRO_EVENT_TIMER:
			{
				++m_counter;
			} break;

			case ALLEGRO_EVENT_DISPLAY_RESIZE:
			{
				al_acknowledge_resize(m_display);
			} break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				m_kill = true;
			} break;

			case ALLEGRO_EVENT_MOUSE_AXES:
			{
				input::mouse::m_pos.x = (float)event.mouse.x;
				input::mouse::m_pos.y = (float)event.mouse.y;
				input::mouse::m_wheel.x = (float)event.mouse.w;
				input::mouse::m_wheel.y = (float)event.mouse.z;
			} break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			{
				input::mouse::m_button[event.mouse.button].m_is_pressed = false;
			} break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			{
				input::mouse::m_button[event.mouse.button].m_is_pressed = true;
				input::mouse::m_button[event.mouse.button].m_was_pressed = true;
			} break;

			case ALLEGRO_EVENT_KEY_DOWN:
			{
				input::keyboard::m_button[event.keyboard.keycode].m_is_pressed = true;
				input::keyboard::m_button[event.keyboard.keycode].m_was_pressed = true;
			} break;

			case ALLEGRO_EVENT_KEY_UP:
			{
				input::keyboard::m_button[event.keyboard.keycode].m_is_pressed = false;
			} break;
			}
		}
	}
}
