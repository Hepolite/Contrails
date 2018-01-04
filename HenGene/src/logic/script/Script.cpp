
#include "Script.h"

#include "logic/script/ScriptUtil.h"

#include <chaiscript/chaiscript.hpp>
#include <plog/Log.h>

struct logic::script::Script::Impl
{
	chaiscript::ChaiScript m_script;
};

logic::script::Script::Script()
{
	m_impl = std::make_unique<Impl>();
	util::applyScriptData(*this);
}
logic::script::Script::~Script() = default;
logic::script::Script::Script(Script && other)
{
	*this = std::move(other);
}
logic::script::Script & logic::script::Script::operator=(Script && other)
{
	if (this != &other)
		std::swap(m_impl, other.m_impl);
	return *this;
}

chaiscript::ChaiScript & logic::script::Script::getHandle() const
{
	return m_impl->m_script;
}

bool logic::script::Script::execute(const std::function<void()> & shell) const
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
bool logic::script::Script::execute(const std::string & code) const
{
	try
	{
		m_impl->m_script.eval(code);
		return true;
	}
	catch (const std::exception & e)
	{
		LOG_WARNING << "Error in script " << std::endl << code << std::endl << e.what();
		return false;
	}
}
