
#include "core/Engine.h"

#include "io/File.h"
#include "logic/state/StateMainMenu.h"

#include <iostream>
#include <plog/Log.h>

int main(int argc, char* argv[])
{
	io::File logFile{ "data/log.txt" };
	logFile.erase();
	plog::init(plog::debug, logFile.getPath().c_str());

	{
		core::Settings settings;
		core::Engine engine{ settings };

		engine.setState(std::make_unique<logic::state::StateMainMenu>());
		engine.start();
	}

	return 0;
}