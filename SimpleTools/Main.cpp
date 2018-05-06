
#include "Hexifier.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string> 
#include <unordered_map>

namespace
{
	bool RUNNING = true;
}

static void help(const std::unordered_map<std::string, std::function<void()>> & commands)
{
	std::cout << "Valid commands:" << std::endl;
	for (const auto & it : commands)
		std::cout << it.first << std::endl;
}

int main(int argc, char * argv[])
{
	const std::unordered_map<std::string, std::function<void()>> COMMANDS = {
		{ "quit", []() { RUNNING = false; } },
		{ "help", [&]() { help(COMMANDS); } },
		{ "hexifier", []() { hexifier::Hexifier{}.process(); } },
	};

	while (RUNNING)
	{
		std::cout << "Enter a command:" << std::endl;

		std::string command;
		std::cin >> command;
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);

		const auto it = COMMANDS.find(command);
		if (it == COMMANDS.end())
			std::cout << "The command '" << command << "' was not found." << std::endl;
		else
			it->second();

		std::cout << std::endl;
	}
	return 0;
}