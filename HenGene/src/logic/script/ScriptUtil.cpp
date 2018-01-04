
#include "ScriptUtil.h"

#include <plog/Log.h>

namespace
{
	std::vector<std::function<void(logic::script::Script &)>> m_data;
}

void logic::script::util::clearScriptData()
{
}
void logic::script::util::registerScriptData(const std::function<void(Script&)> & data)
{
	if (data != nullptr)
		m_data.push_back(data);
}
void logic::script::util::applyScriptData(Script & script)
{
	for (const auto & data : m_data)
		data(script);
}
