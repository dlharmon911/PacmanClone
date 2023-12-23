#ifndef _PACMAN_APPLICATION_H_
#define _PACMAN_APPLICATION_H_ 

#include <vector>
#include <string>
#include "base.h"

namespace pacman
{
	namespace application
	{
		namespace display
		{
			static constexpr const char* TITLE = "Pacman Clone";
		}
		int32_t run(const std::vector<std::string>& argList);
	}
}



#endif // !_PACMAN_APPLICATION_H_
