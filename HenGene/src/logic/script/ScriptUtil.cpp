
#include "ScriptUtil.h"

#include <plog/Log.h>

bool logic::script::util::execute(const Script & script, const std::function<void()> & shell)
{
	try
	{
		shell();
		return true;
	}
	catch (const std::exception & e)
	{
		LOG_WARNING << "Error executing shell:" << std::endl << e.what();
		return false;
	}
}
bool logic::script::util::execute(const Script & script, const std::string & code)
{
	try
	{
		script.getHandle().eval(code);
		return true;
	}
	catch (const std::exception & e)
	{
		LOG_WARNING << "Error in script " << std::endl << code << std::endl << e.what();
		return false;
	}
}
