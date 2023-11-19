#include "hex.h"

namespace pacman
{
	namespace hex
	{
		uint32_t from_char(int32_t c)
		{
			uint32_t out = 0;

			if (c >= '0' && c <= '9')
			{
				out = c - '0';
			}
			else
			{
				if (c >= 'a' && c <= 'f')
				{
					out = c - 'a' + 10;
				}
				else
				{
					if (c >= 'A' && c <= 'F')
					{
						out = c - 'A' + 10;
					}
				}
			}

			return out;
		}

		int32_t to_char(uint32_t v)
		{
			int32_t out = 0;

			if (v >= 0 && v <= 9)
			{
				out = '0' + v;
			}
			else
			{
				if (v >= 10 && v <= 15)
				{
					out = 'a' + v - 10;
				}
			}

			return out;
		}
	}
}
