
#include "SetupScripts.h"

#include "logic/script/ScriptUtil.h"
#include "world/Universe.h"

using namespace logic::script;

void core::setup::setupScripts(Engine & engine)
{
	util::clearScriptData();

	detail::setupEngine(engine);
}

void core::setup::detail::setupEngine(Engine & engine)
{
	util::registerScriptData([&engine](Script & script)
	{
		util::addVarGlobal(script, &engine, "ENGINE");
		util::addFun(script, &core::Engine::stop, "terminate");
		util::addFun(script, &core::Engine::getEventBus, "getEventBus");
	});
}
void core::setup::detail::setupUniverse(Engine & engine)
{
	util::registerScriptData([&universe = engine.getUniverse()](Script & script)
	{
		util::addVarGlobalConst(script, &universe, "UNIVERSE");
		util::addFun(script, &world::Universe::hasWorld, "hasWorld");
		util::addFun(script, &world::Universe::getWorld, "getWorld");
	});
}
