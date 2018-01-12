
#include "core/Engine.h"

#include "io/File.h"
#include "logic/state/StateMainMenu.h"
#include "logic/state/StateManager.h"

#include <iostream>
#include <plog/Log.h>

int main(int argc, char* argv[])
{
	io::File logFile{ "data/log.log" };
	logFile.erase();
	plog::init(plog::debug, logFile.getPath().c_str());

	{
		core::Settings settings;
		core::Engine engine{ settings };

		engine.initialize();
		engine.getStateManager().set(std::make_shared<logic::state::StateMainMenu>());
		engine.start();
	}

	return 0;
}