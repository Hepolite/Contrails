
#include "core/Engine.h"

#include "io/File.h"

#include <iostream>
#include <plog/Log.h>

int main(int argc, char* argv[])
{
	io::File logFile{ "data/log.txt" };
	logFile.erase();
	plog::init(plog::debug, logFile.getPath().c_str());

	{
		core::Settings settings;
		core::Engine{ settings }.start();
	}

	return 0;
}