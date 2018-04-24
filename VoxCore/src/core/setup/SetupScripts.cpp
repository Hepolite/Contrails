
#include "SetupScripts.h"

#include "io/File.h"
#include "io/Folder.h"
#include "logic/script/ScriptUtil.h"
#include "ui/gui/GuiManager.h"
#include "logic/state/StateManager.h"
#include "logic/state/StateEditorWorld.h"
#include "logic/state/StateMainMenu.h"
#include "util/Maths.h"
#include "world/detail/data/WorldQuery.h"
#include "world/Universe.h"
#include "world/util/Query.h"
#include "world/World.h"

#include <glm/glm.hpp>
#include <plog/Log.h>

using namespace logic::script;

namespace script
{
	inline void debug(const std::string & msg) { LOG_DEBUG << msg; }
	inline void info(const std::string & msg) { LOG_INFO << msg; }
	inline void warn(const std::string & msg) { LOG_WARNING << msg; }
}

namespace
{
	template<typename T>
	inline void addGlmVec2(Script & script, const std::string & name)
	{
		util::addType<glm::tvec2<T>>(script, name);
		util::addCtor<glm::tvec2<T>()>(script, name);
		util::addCtor<glm::tvec2<T>(const glm::vec2 &)>(script, name);
		util::addCtor<glm::tvec2<T>(T)>(script, name);
		util::addCtor<glm::tvec2<T>(T, T)>(script, name);

		util::addAttribute(script, &glm::tvec2<T>::x, "x");
		util::addAttribute(script, &glm::tvec2<T>::y, "y");
		util::addFun<glm::tvec2<T>, T &, int>(script, &glm::tvec2<T>::operator[], "[]");
		util::addFun<glm::tvec2<T>, const T &, int>(script, &glm::tvec2<T>::operator[], "[]");
	}
	template<typename T>
	inline void addGlmVec3(Script & script, const std::string & name)
	{
		util::addType<glm::tvec3<T>>(script, name);
		util::addCtor<glm::tvec3<T>()>(script, name);
		util::addCtor<glm::tvec3<T>(const glm::vec3 &)>(script, name);
		util::addCtor<glm::tvec3<T>(T)>(script, name);
		util::addCtor<glm::tvec3<T>(T, T, T)>(script, name);

		util::addAttribute(script, &glm::tvec3<T>::x, "x");
		util::addAttribute(script, &glm::tvec3<T>::y, "y");
		util::addAttribute(script, &glm::tvec3<T>::z, "z");
		util::addFun<glm::tvec3<T>, T &, int>(script, &glm::tvec3<T>::operator[], "[]");
		util::addFun<glm::tvec3<T>, const T &, int>(script, &glm::tvec3<T>::operator[], "[]");
	}
	template<typename T>
	inline void addGlmVec4(Script & script, const std::string & name)
	{
		util::addType<glm::tvec4<T>>(script, name);
		util::addCtor<glm::tvec4<T>()>(script, name);
		util::addCtor<glm::tvec4<T>(const glm::vec4 &)>(script, name);
		util::addCtor<glm::tvec4<T>(T)>(script, name);
		util::addCtor<glm::tvec4<T>(T, T, T, T)>(script, name);

		util::addAttribute(script, &glm::tvec4<T>::x, "x");
		util::addAttribute(script, &glm::tvec4<T>::y, "y");
		util::addAttribute(script, &glm::tvec4<T>::z, "z");
		util::addAttribute(script, &glm::tvec4<T>::w, "w");
		util::addFun<glm::tvec4<T>, T &, int>(script, &glm::tvec4<T>::operator[], "[]");
		util::addFun<glm::tvec4<T>, const T &, int>(script, &glm::tvec4<T>::operator[], "[]");
	}
}

void core::setup::setupScripts(Engine & engine)
{
	util::clearScriptData();

	detail::setupEngine(engine);
	detail::setupGui(engine);
	detail::setupIO(engine);
	detail::setupLogging(engine);
	detail::setupMath(engine);
	detail::setupStates(engine);
	detail::setupUI();
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

		util::addAttribute(script, &Widget::m_activation, "activation");
		util::addAttribute(script, &Widget::m_render, "render");
		util::addAttribute(script, &Widget::m_state, "state");

		util::addAttribute(script, &Activation::m_locked, "locked");
		util::addAttribute(script, &Render::m_visible, "visible");
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
void core::setup::detail::setupLogging(Engine & engine)
{
	util::registerScriptData([](Script & script)
	{
		util::addFun(script, &script::info, "LOG_INFO");
		util::addFun(script, &script::warn, "LOG_WARN");
		util::addFun(script, &script::debug, "LOG_DEBUG");
	});
}
void core::setup::detail::setupMath(Engine & engine)
{
	util::registerScriptData([](Script & script)
	{
		util::addEnum<math::Axis>(script, "Axis", {
			{ math::Axis::X, "AXIS_X" },
			{ math::Axis::Y, "AXIS_Y" },
			{ math::Axis::Z, "AXIS_Z" }
		});

		addGlmVec2<bool>(script, "bvec2");
		addGlmVec2<double>(script, "dvec2");
		addGlmVec2<float>(script, "vec2");
		addGlmVec2<int>(script, "ivec2");
		addGlmVec2<unsigned int>(script, "uvec2");

		addGlmVec3<bool>(script, "bvec3");
		addGlmVec3<double>(script, "dvec3");
		addGlmVec3<float>(script, "vec3");
		addGlmVec3<int>(script, "ivec3");
		addGlmVec3<unsigned int>(script, "uvec3");

		addGlmVec4<bool>(script, "bvec4");
		addGlmVec4<double>(script, "dvec4");
		addGlmVec4<float>(script, "vec4");
		addGlmVec4<int>(script, "ivec4");
		addGlmVec4<unsigned int>(script, "uvec4");
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
void core::setup::detail::setupUI()
{
	util::registerScriptData([](Script & script)
	{
		using namespace ui::mouse;
		util::addEnum<Button>(script, "MouseButton", {
			{ Button::LEFT, "MOUSE_BUTTON_LEFT" },
			{ Button::MIDDLE, "MOUSE_BUTTON_MIDDLE" },
			{ Button::NONE, "MOUSE_BUTTON_NONE" },
			{ Button::RIGHT, "MOUSE_BUTTON_RIGHT" },
		});
	});
}
void core::setup::detail::setupUniverse(Engine & engine)
{
	util::registerScriptData([&universe = engine.getUniverse()](Script & script)
	{
		using namespace world::data;
		using namespace world::util;
		util::addVarGlobal(script, &universe, "UNIVERSE");
		util::addType<world::World>(script, "World");
		util::addFun(script, &world::Universe::createWorld, "createWorld");
		util::addFun(script, &world::Universe::destroyWorld, "destroyWorld");
		util::addFun(script, &world::Universe::hasWorld, "hasWorld");
		util::addFun(script, &world::Universe::getWorld, "getWorld");

		util::addFun(script, &world::World::process, "process");
		util::addFun(script, &world::World::getBlockRegistry, "getBlockRegistry");
		util::addFun<world::World, void, WorldQuery &>(script, &world::World::write, "write");
		util::addFun<world::World, void, const glm::ivec3 &, BlockData &, ColorData &>(script, &world::World::write, "write");
		util::addFun<world::World, void, const glm::ivec3 &, BlockData &>(script, &world::World::write, "write");
		util::addFun<world::World, void, const glm::ivec3 &, ColorData &>(script, &world::World::write, "write");
		util::addFun(script, &world::World::read, "read");
		util::addFun(script, &world::World::readBlock, "readBlock");
		util::addFun(script, &world::World::readColor, "readColor");

		util::addVarGlobal(script, Query{}, "QUERY");
		util::addFun(script, &Query::readBlock, "readBlock");
		util::addFun(script, &Query::readRectangle, "readRectangle");
		util::addFun(script, &Query::writeBlock, "writeBlock");
		util::addFun(script, &Query::writeRectangle, "writeRectangle");

		util::addFun(script, &world::BlockRegistry::size, "size");
		util::addFun<world::BlockRegistry, const world::Block &, const unsigned int &>(script, &world::BlockRegistry::operator[], "[]");
		util::addFun<world::BlockRegistry, const world::Block &, const std::string &>(script, &world::BlockRegistry::operator[], "[]");
	});
}
