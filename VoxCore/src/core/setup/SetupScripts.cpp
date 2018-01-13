
#include "SetupScripts.h"

#include "io/File.h"
#include "io/Folder.h"
#include "logic/script/ScriptUtil.h"
#include "ui/gui/GuiManager.h"
#include "logic/state/StateManager.h"
#include "logic/state/StateEditorWorld.h"
#include "logic/state/StateMainMenu.h"
#include "world/detail/data/WorldQuery.h"
#include "world/Universe.h"
#include "world/World.h"

using namespace logic::script;

void core::setup::setupScripts(Engine & engine)
{
	util::clearScriptData();

	detail::setupEngine(engine);
	detail::setupGui(engine);
	detail::setupIO(engine);
	detail::setupStates(engine);
	detail::setupUniverse(engine);
}

void core::setup::detail::setupEngine(Engine & engine)
{
	using namespace core;
	util::registerScriptData([&engine](Script & script)
	{
		util::addVarGlobal(script, &engine, "ENGINE");
		util::addFun(script, &Engine::stop, "terminate");
	});
}
void core::setup::detail::setupGui(Engine & engine)
{
	using namespace ui::gui;
	util::registerScriptData([&guiManager = engine.getGuiManager()](Script & script)
	{
		util::addVarGlobal(script, &guiManager, "GUI_MANAGER");
		util::addFun(script, &GuiManager::open, "open");
		util::addFun(script, &GuiManager::close, "close");
		util::addFun(script, &GuiManager::get, "get");

		util::addFun<Gui, logic::script::Script &>(script, &Gui::getScript, "getScript");
		util::addFun<Gui, const logic::script::Script &>(script, &Gui::getScript, "getScript");
		util::addFun<Gui, Widgets &>(script, &Gui::getWidgets, "getWidgets");
		util::addFun<Gui, const Widgets &>(script, &Gui::getWidgets, "getWidgets");

		util::addFun(script, &Widgets::has, "has");
		util::addFun(script, &Widgets::create, "create");
		util::addFun<Widgets, Widget &, const std::string &>(script, &Widgets::get, "get");
		util::addFun<Widgets, const Widget &, const std::string &>(script, &Widgets::get, "get");

		// ...

		util::addAttribute(script, &Widget::m_state, "state");
		util::addAttribute(script, &State::m_bool, "bool");
		util::addAttribute(script, &State::m_float, "float");
		util::addAttribute(script, &State::m_string, "string");
	});
}
void core::setup::detail::setupIO(Engine & engine)
{
	using namespace io;
	util::registerScriptData([](Script & script)
	{
		util::addType<File>(script, "File");
		util::addCtor<File(const char *)>(script, "File");
		util::addCtor<File(const std::string &)>(script, "File");
		util::addFun(script, &File::exists, "exists");
		util::addFun(script, &File::create, "create");
		util::addFun(script, &File::erase, "erase");
		util::addFun(script, &File::read, "read");
		util::addFun(script, &File::parse, "parse");
		util::addFun(script, &File::write, "write");
		util::addFun(script, &File::getPath, "getPath");
		util::addFun(script, &File::getFolder, "getFolder");
		util::addFun(script, &File::getName, "getName");
		util::addFun(script, &File::getExtension, "getExtension");

		util::addType<Folder>(script, "Folder");
		util::addCtor<Folder(const char *)>(script, "Folder");
		util::addCtor<Folder(const std::string &)>(script, "Folder");
		util::addFun(script, &Folder::exists, "exists");
		util::addFun(script, &Folder::create, "create");
		util::addFun(script, &Folder::erase, "erase");
		util::addFun(script, &Folder::getFiles, "getFiles");
		util::addFun(script, &Folder::getFolders, "getFolders");
		util::addFun(script, &Folder::getPath, "getPath");
		util::addFun(script, &Folder::getFolder, "getFolder");
		util::addFun(script, &Folder::getName, "getName");
	});
}
void core::setup::detail::setupStates(Engine & engine)
{
	using namespace logic::state;
	util::registerScriptData([&stateManager = engine.getStateManager()](Script & script)
	{
		util::addVarGlobal(script, &stateManager, "STATE_MANAGER");
		util::addFun(script, &StateManager::clear, "clear");
		util::addFun(script, &StateManager::has, "has");
		util::addFun(script, &StateManager::set, "set");
		util::addFun(script, &StateManager::add, "add");
		util::addFun(script, &StateManager::remove, "remove");

		util::addRelation<StateBase, StateEditorWorld>(script);
		util::addRelation<StateBase, StateMainMenu>(script);
		util::addCtor<StateEditorWorld()>(script, "StateEditorWorld");
		util::addCtor<StateMainMenu()>(script, "StateMainMenu");
	});
}
void core::setup::detail::setupUniverse(Engine & engine)
{
	using namespace world;
	util::registerScriptData([&universe = engine.getUniverse()](Script & script)
	{
		util::addVarGlobal(script, &universe, "UNIVERSE");
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
