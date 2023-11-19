#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace pacman
{
	namespace application
	{
		int32_t run(const std::vector<std::string>& argList);
	}
}

int main(int argc, char** argv)
{
	std::vector<std::string> argList;
	int rv = 0;
	std::fstream fileOut;
	std::streambuf* streamBuf = nullptr;

	fileOut.open("logs\\output.txt", std::ios::out);

	if (fileOut.is_open())
	{
		streamBuf = std::cout.rdbuf();
		std::cout.rdbuf(fileOut.rdbuf());
	}

	for (int i = 0; i < argc; ++i)
	{
		argList.push_back(argv[i]);
	}

	rv = pacman::application::run(argList);

	if (fileOut.is_open())
	{
		std::cout.rdbuf(streamBuf);
		fileOut.close();
	}

	return rv;
}

