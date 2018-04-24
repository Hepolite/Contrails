
#include "Editor.h"

#include "asset/AssetRef.h"
#include "editor/util/Grid.h"
#include "editor/util/ShapeBox.h"
#include "editor/util/ShapeCylinder.h"
#include "editor/util/ShapeLine.h"
#include "editor/util/ShapePoint.h"
#include "logic/ecs/detail/Entity.h"
#include "logic/script/ScriptUtil.h"
#include "render/opengl/Program.h"
#include "render/scene/components/ComponentGeneric.h"

#include <glm/gtc/matrix_transform.hpp>

#undef TRANSPARENT

namespace
{
	const std::string SCRIPT_INIT = "init();";
	const std::string SCRIPT_PROCESS = "process();";
	const std::string SCRIPT_ACTION_LEFTCLICK = "action(MOUSE_BUTTON_LEFT);";
	const std::string SCRIPT_ACTION_MIDDLECLICK = "action(MOUSE_BUTTON_MIDDLE);";
	const std::string SCRIPT_ACTION_RIGHTCLICK = "action(MOUSE_BUTTON_RIGHT);";
}

class editor::Editor::Impl
{
public:
	Impl() = default;
	~Impl();

	void inject(const asset::AssetRegistry & assets);
	void inject(const render::uboRegistry & ubos);
	void inject(ui::gui::Gui & gui);
	void inject(logic::event::EventBus & bus);
	void inject(core::scene::Scene & scene);

	void process();
	void render() const;

	inline auto & getEntityData() { return m_scene->getEntityData<render::scene::ComponentGeneric>(m_entity); }

	// ...

	inline auto & getCursor() { return m_cursor; }
	inline auto & getScene() { return *m_scene; }

	void setTransform(const glm::mat4 & transform) const;

	// ...

	inline void setShape(util::Shape * shape) { m_shape = shape; }
	inline auto getShape() const { return m_shape; }

private:
	util::Cursor m_cursor;
	util::Grid m_grid;
	util::Shape * m_shape = nullptr;
	util::ShapeBox m_shapeBox;
	util::ShapeCylinder m_shapeCylinder;
	util::ShapeLine m_shapeLine;
	util::ShapePoint m_shapePoint;

	logic::event::Listener m_mouseRelease;

	// ...

	const asset::AssetRegistry * m_assets = nullptr;
	const render::uboRegistry * m_ubos = nullptr;
	ui::gui::Gui * m_gui = nullptr;
	core::scene::Scene * m_scene = nullptr;

	asset::Ref<render::opengl::Program> m_programGrid, m_programShape;
	logic::ecs::EntityID m_entity;
};

editor::Editor::Impl::~Impl()
{
	if (m_scene != nullptr)
		m_scene->deleteEntity(m_entity);
}

void editor::Editor::Impl::inject(const asset::AssetRegistry & assets)
{
	m_assets = &assets;
	m_programGrid = assets.get<render::opengl::Program>("editor_grid");
	m_programShape = assets.get<render::opengl::Program>("editor_shape");
}
void editor::Editor::Impl::inject(const render::uboRegistry & ubos)
{
	m_ubos = &ubos;
}
void editor::Editor::Impl::inject(ui::gui::Gui & gui)
{
	m_gui = &gui;

	auto & script = gui.getScript();
	logic::script::util::addVarGlobal(script, this, "EDITOR");
	logic::script::util::addFun(script, &Impl::getShape, "getShape");
	logic::script::util::addFun(script, &Impl::setShape, "setShape");
	logic::script::util::addAttribute(script, &Impl::m_shapeBox, "shapeBox");
	logic::script::util::addAttribute(script, &Impl::m_shapeCylinder, "shapeCylinder");
	logic::script::util::addAttribute(script, &Impl::m_shapeLine, "shapeLine");
	logic::script::util::addAttribute(script, &Impl::m_shapePoint, "shapePoint");

	logic::script::util::addAttribute(script, &Impl::m_cursor, "cursor");
	logic::script::util::addFun(script, &util::Cursor::setPos, "setPos");
	logic::script::util::addFun(script, &util::Cursor::getPos, "getPos");
	logic::script::util::addFun(script, &util::Cursor::getActualPos, "getActualPos");
	logic::script::util::addFun(script, &util::Cursor::getClickedPos, "getClickedPos");
	logic::script::util::addFun(script, &util::Cursor::isAxisXLocked, "isAxisXLocked");
	logic::script::util::addFun(script, &util::Cursor::isAxisYLocked, "isAxisYLocked");
	logic::script::util::addFun(script, &util::Cursor::isAxisZLocked, "isAxisZLocked");
	logic::script::util::addFun(script, &util::Cursor::lockAxisX, "lockAxisX");
	logic::script::util::addFun(script, &util::Cursor::lockAxisY, "lockAxisY");
	logic::script::util::addFun(script, &util::Cursor::lockAxisZ, "lockAxisZ");

	logic::script::util::addAttribute(script, &Impl::m_grid, "grid");
	logic::script::util::addFun(script, &util::Grid::setPos, "setPos");
	logic::script::util::addFun(script, &util::Grid::setSize, "setSize");
	logic::script::util::addFun(script, &util::Grid::setResolution, "setResolution");
	logic::script::util::addFun(script, &util::Grid::setVisible, "setVisible");
	logic::script::util::addFun(script, &util::Grid::getPos, "getPos");
	logic::script::util::addFun(script, &util::Grid::getSize, "getSize");
	logic::script::util::addFun(script, &util::Grid::getResolution, "getResolution");
	logic::script::util::addFun(script, &util::Grid::isVisible, "isVisible");

	logic::script::util::addType<util::Shape>(script, "Shape");
	logic::script::util::addRelation<util::Shape, util::ShapeBox>(script);
	logic::script::util::addRelation<util::Shape, util::ShapeCylinder>(script);
	logic::script::util::addRelation<util::Shape, util::ShapeLine>(script);
	logic::script::util::addRelation<util::Shape, util::ShapePoint>(script);
	logic::script::util::addFun(script, &util::Shape::getName, "getName");
	logic::script::util::addFun(script, &util::Shape::setDynamic, "setDynamic");
	logic::script::util::addFun(script, &util::Shape::isDynamic, "isDynamic");
	logic::script::util::addFun(script, &util::Shape::stretch, "stretch");
	logic::script::util::addFun(script, &util::Shape::setPos, "setPos");
	logic::script::util::addFun(script, &util::Shape::setSize, "setSize");
	logic::script::util::addFun(script, &util::Shape::setSizeX, "setSizeX");
	logic::script::util::addFun(script, &util::Shape::setSizeY, "setSizeY");
	logic::script::util::addFun(script, &util::Shape::setSizeZ, "setSizeZ");
	logic::script::util::addFun(script, &util::Shape::getSize, "getSize");
	logic::script::util::addFun(script, &util::Shape::getReadQuery, "getReadQuery");
	logic::script::util::addFun(script, &util::Shape::getWriteQuery, "getWriteQuery");
	logic::script::util::addFun(script, &util::ShapeCylinder::getAxis, "getAxis");
	logic::script::util::addFun(script, &util::ShapeCylinder::setAxis, "setAxis");
}
void editor::Editor::Impl::inject(logic::event::EventBus & bus)
{
	m_cursor.inject(bus);

	m_mouseRelease = bus.add<logic::event::MouseRelease>([this](auto & event)
	{
		if (m_gui == nullptr || !m_cursor.hasValidPos())
			return;
		switch (event.m_button)
		{
		case ui::mouse::Button::LEFT:
			m_gui->getScript().execute(SCRIPT_ACTION_LEFTCLICK);
			break;
		case ui::mouse::Button::MIDDLE:
			m_gui->getScript().execute(SCRIPT_ACTION_MIDDLECLICK);
			break;
		case ui::mouse::Button::RIGHT:
			m_gui->getScript().execute(SCRIPT_ACTION_RIGHTCLICK);
			break;
		default:
			break;
		}
	});
}
void editor::Editor::Impl::inject(core::scene::Scene & scene)
{
	m_scene = &scene;
	m_entity = scene.createEntity<render::scene::ComponentGeneric>();
}

void editor::Editor::Impl::process()
{
	if (m_cursor.hasValidPos() && m_shape != nullptr)
	{
		if (m_shape->isDynamic())
		{
			if (m_cursor.getClickedButton() == ui::mouse::Button::NONE)
				m_shape->stretch(m_cursor.getActualPos(), m_cursor.getActualPos());
			else
				m_shape->stretch(m_cursor.getClickedPos(), m_cursor.getPos());
		}
		else
			m_shape->setPos(m_cursor.getPos());
	}

	if (m_gui != nullptr)
		m_gui->getScript().execute(SCRIPT_PROCESS);
}
void editor::Editor::Impl::render() const
{
	if (m_programGrid && m_grid.isVisible())
	{
		m_programGrid->bind();
		setTransform(glm::translate(glm::mat4{ 1.0f }, m_grid.getPos()));
		m_grid.getMesh()->render();
	}
	if (m_programShape && m_shape && m_cursor.hasValidPos())
	{
		m_programShape->bind();
		setTransform(glm::translate(glm::mat4{ 1.0f }, { m_shape->getPos() }));
		m_shape->getMesh()->render();
	}
}

void editor::Editor::Impl::setTransform(const glm::mat4 & transform) const
{
	if (m_ubos != nullptr)
		m_ubos->get("Model").set("transform", transform);
}

// ...

editor::Editor::Editor()
{
	m_impl = std::make_unique<Impl>();
}
editor::Editor::~Editor() = default;

void editor::Editor::inject(const asset::AssetRegistry & assets) { m_impl->inject(assets); }
void editor::Editor::inject(const render::uboRegistry & ubos) {	m_impl->inject(ubos); }
void editor::Editor::inject(logic::event::EventBus & bus) { m_impl->inject(bus); }
void editor::Editor::inject(ui::gui::Gui & gui)
{
	m_impl->inject(gui);
	init(gui.getScript());
	gui.getScript().execute(SCRIPT_INIT);
}
void editor::Editor::inject(core::scene::Scene & scene)
{
	m_impl->inject(scene);

	auto & data = m_impl->getEntityData();
	data.m_processer = [this](auto & t, auto & dt)
	{
		m_impl->process();
		process(t, dt);
	};
	data.m_renderer = [this](auto & context, auto & t, auto & dt)
	{
		if (context.m_renderPass == render::RenderPass::TRANSPARENT)
			m_impl->render();
		render(context, t, dt);
	};
}

editor::util::Cursor & editor::Editor::getCursor() { return m_impl->getCursor(); }
core::scene::Scene & editor::Editor::getScene() { return m_impl->getScene(); }

void editor::Editor::setTransform(const glm::mat4 & transform) const
{
	m_impl->setTransform(transform);
}
