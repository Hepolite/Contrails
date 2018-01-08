
#include "SetupScripts.h"

#include "logic/event/EventBus.h"
#include "logic/script/ScriptUtil.h"
#include "world/detail/data/WorldQuery.h"
#include "world/Universe.h"
#include "world/World.h"

using namespace logic::script;

void core::setup::setupScripts(Engine & engine)
{
	util::clearScriptData();

	detail::setupEngine(engine);
}

void core::setup::detail::setupEngine(Engine & engine)
{
	using namespace core;
	util::registerScriptData([&engine](Script & script)
	{
		util::addVarGlobal(script, &engine, "ENGINE");
		util::addFun(script, &Engine::stop, "terminate");
		util::addFun(script, &Engine::getEventBus, "getEventBus");
	});
}
void core::setup::detail::setupUniverse(Engine & engine)
{
	using namespace world;
	util::registerScriptData([&universe = engine.getUniverse()](Script & script)
	{
		util::addVarGlobalConst(script, &universe, "UNIVERSE");
		util::addFun(script, &Universe::createWorld, "createWorld");
		util::addFun(script, &Universe::destroyWorld, "destroyWorld");
		util::addFun(script, &Universe::hasWorld, "hasWorld");
		util::addFun(script, &Universe::getWorld, "getWorld");

		util::addFun(script, &World::getBlockRegistry, "getBlockRegistry");
		util::addFun<World, void, data::WorldQuery &>(script, &World::write, "write");
		util::addFun<World, void, const glm::ivec3 &, data::BlockData &, data::ColorData &>(script, &World::write, "write");
		util::addFun<World, void, const glm::ivec3 &, data::BlockData &>(script, &World::write, "write");
		util::addFun<World, void, const glm::ivec3 &, data::ColorData &>(script, &World::write, "write");
		util::addFun(script, &World::read, "read");
		util::addFun(script, &World::readBlock, "readBlock");
		util::addFun(script, &World::readColor, "readColor");
	});
}
