
#include "Editor.h"

#include "asset/AssetRef.h"
#include "editor/util/Grid.h"
#include "editor/util/ShapeBox.h"
#include "editor/util/ShapeLine.h"
#include "logic/ecs/detail/Entity.h"
#include "render/opengl/Program.h"
#include "render/scene/components/ComponentGeneric.h"

#include <glm/gtc/matrix_transform.hpp>

class editor::Editor::Impl
{
public:
	Impl() = default;
	~Impl();

	void inject(const asset::AssetRegistry & assets);
	void inject(const render::uboRegistry & ubos);
	void inject(core::scene::Scene & scene);

	void process();
	void render() const;

	inline auto & getEntityData() { return m_scene->getEntityData<render::scene::ComponentGeneric>(m_entity); }

	void setTransform(const glm::mat4 & transform) const;

private:
	util::Grid m_grid;
	util::ShapeBox m_shapeBox;
	util::ShapeLine m_shapeLine;

	const asset::AssetRegistry * m_assets = nullptr;
	const render::uboRegistry * m_ubos = nullptr;
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
void editor::Editor::Impl::inject(core::scene::Scene & scene)
{
	m_scene = &scene;
	m_entity = scene.createEntity<render::scene::ComponentGeneric>();
}

void editor::Editor::Impl::process()
{
	m_shapeBox.stretch({ 0, 0, 10 }, { 0, 1, 12 });
	m_shapeLine.stretch({ 3, 7, 11 }, { 5, 0, 10 });
}
void editor::Editor::Impl::render() const
{
	if (m_programGrid != nullptr)
	{
		m_programGrid->bind();
		setTransform(glm::translate(glm::mat4{ 1.0f }, m_grid.getPos()));
		m_grid.getMesh()->render();
	}
	if (m_programShape != nullptr)
	{
		m_programShape->bind();
		setTransform(glm::translate(glm::mat4{ 1.0f }, { m_shapeBox.getPos() }));
		m_shapeBox.getMesh()->render();
		setTransform(glm::translate(glm::mat4{ 1.0f }, { m_shapeLine.getPos() }));
		m_shapeLine.getMesh()->render();
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

void editor::Editor::inject(const asset::AssetRegistry & assets)
{
	m_impl->inject(assets);
}
void editor::Editor::inject(const render::uboRegistry & ubos)
{
	m_impl->inject(ubos);
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

void editor::Editor::setTransform(const glm::mat4 & transform) const
{
	m_impl->setTransform(transform);
}
