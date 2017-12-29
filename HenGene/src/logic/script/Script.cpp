
#include "Script.h"

#include <chaiscript/chaiscript.hpp>
#include <plog/Log.h>

struct logic::script::Script::Impl
{
	chaiscript::ChaiScript m_script;
};

logic::script::Script::Script()
{
	m_impl = std::make_unique<Impl>();
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
