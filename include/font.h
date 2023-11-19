#ifndef _PACMAN_FONT_H_
#define _PACMAN_FONT_H_

#include <fstream>
#include "base.h"
#include "hex.h"
#include "color.h"

namespace pacman
{
	typedef struct font_t font_t;
	namespace font
	{
		font_t* create_default();
		font_t* create_from_data_array(const uint8_t* data, int32_t count, int32_t start = 0x20);
		bool save_to_file(font_t* font, const std::string& filename);
		void destroy(font_t* font);

#ifdef INCLUDE_JSON_FONT_FUNCTIONS
		font_t* load_from_json_file(const std::string& filename);
		font_t* load_from_bitmap_file(const std::string& filename, int32_t start);
		bool save_to_json_file(font_t* font, const std::string& filename);
#endif // INCLUDE_JSON_FONT_FUNCTIONS

		typedef struct glyph_t glyph_t;
		namespace glyph
		{
			static constexpr int32_t size = 8;

			glyph_t* get(font_t* font, int32_t index);
			bool set(glyph_t* glyph, const uint8_t* data);
			bool set(glyph_t* glyph, const std::string& string_16);
			void set(font_t* font, int32_t index, const std::string& string_16);
		}

		enum class alignment_t
		{
			left,
			right,
			centre
		};

		void draw(const font_t* font, color_t color, const point_t& point, uint8_t c);
		void draw(const font_t* font, color_t color, const point_t& point, alignment_t alignment, const std::string& text);
		void draw(const font_t* font, color_t color, const point_t& point, alignment_t alignment, const char* format, ...);
	}
}

#endif // !_PACMAN_FONT_H_

