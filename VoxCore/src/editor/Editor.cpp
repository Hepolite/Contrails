
#include "Editor.h"

#include "asset/AssetRef.h"
#include "editor/util/Grid.h"
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

	const asset::AssetRegistry * m_assets = nullptr;
	const render::uboRegistry * m_ubos = nullptr;
	core::scene::Scene * m_scene = nullptr;

	asset::Ref<render::opengl::Program> m_program;
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
	m_program = assets.get<render::opengl::Program>("editor");
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
}
void editor::Editor::Impl::render() const
{
	if (m_program == nullptr)
		return;
	m_program->bind();

	setTransform(glm::translate(glm::mat4{ 1.0f }, m_grid.getPos()));
	m_grid.getMesh()->render();
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
