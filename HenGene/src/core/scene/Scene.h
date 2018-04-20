
#pragma once

#include "logic/ecs/ComponentStorage.h"
#include "logic/ecs/EntityRegistry.h"
#include "logic/ecs/SystemRegistry.h"
#include "logic/ecs/detail/Entity.h"
#include "render/scene/CameraStorage.h"
#include "render/scene/RendererRegistry.h"
#include "render/RenderPass.h"
#include "render/uboRegistry.h"
#include "util/Physics.h"

namespace core
{
	namespace scene
	{
		class Scene
		{
		public:
			Scene();
			Scene(const Scene &) = delete;
			Scene(Scene &&) = delete;
			~Scene() = default;

			Scene & operator=(const Scene &) = delete;
			Scene & operator=(Scene &&) = delete;

			inline void inject(core::Engine & engine) { m_systems.inject(engine); }
			inline void inject(const ui::Display & display) { m_cameras.inject(display); }
			inline void inject(const render::uboRegistry & registry) { m_cameras.inject(registry); }

			void process(const Time & t, const Time & dt);
			void render(const Time & t, const Time & dt, float pt) const;

			// ...

			inline render::scene::Camera & getCamera(render::scene::CameraType type) { return m_cameras.getCamera(type); }

			template<typename ...Systems> void registerSystems();
			void clearSystems();

			template<typename First, typename Second, typename ...Remaining> void registerRenderers();
			template<typename Renderer> Renderer & registerRenderers();
			void clearRenderers();

			template<typename ...Components> logic::ecs::EntityID createEntity();
			template<typename ...Components> void attachEntityComponent(logic::ecs::EntityID entity);
			template<typename ...Components> void detachEntityComponent(logic::ecs::EntityID entity);
			template<typename Component> Component & getEntityData(logic::ecs::EntityID entity);
			bool hasEntity(logic::ecs::EntityID entity) const;
			void deleteEntity(logic::ecs::EntityID entity);
			void clearEntities();

		private:
			logic::ecs::ComponentStorage m_components;
			logic::ecs::SystemRegistry m_systems;
			logic::ecs::EntityRegistry m_entities;

			render::scene::RendererRegistry m_renderers;
			render::scene::CameraStorage m_cameras;
		};
	}
}

template<typename ...Systems>
inline void core::scene::Scene::registerSystems()
{
	m_systems.addSystem<Systems...>();
}

template<typename First, typename Second, typename ...Remaining>
inline void core::scene::Scene::registerRenderers()
{
	registerRenderers<First>();
	registerRenderers<Second, Remaining...>();
}
template<typename Renderer>
inline Renderer & core::scene::Scene::registerRenderers()
{
	auto renderer = &m_systems.addSystem<Renderer>();
	m_renderers.add(renderer);
	return *renderer;
}

template<typename ...Components>
inline logic::ecs::EntityID core::scene::Scene::createEntity()
{
	const auto & entity = m_entities.getEntity(m_entities.createEntity());
	m_entities.attachComponent<Components...>(entity.m_id);
	m_systems.addEntity(entity);
	return entity.m_id;
}
template<typename ...Components>
inline void core::scene::Scene::attachEntityComponent(logic::ecs::EntityID entity)
{
	auto & e = m_entities.getEntity(entity);
	m_systems.removeEntity(e);
	m_entities.attachComponent<Components...>(entity);
	m_systems.addEntity(e);
}
template<typename ...Components>
inline void core::scene::Scene::detachEntityComponent(logic::ecs::EntityID entity)
{
	auto & e = m_entities.getEntity(entity);
	m_systems.removeEntity(e);
	m_entities.detachComponent<Components...>(entity);
	m_systems.addEntity(e);
}

template<typename Component>
inline Component & core::scene::Scene::getEntityData(logic::ecs::EntityID entity)
{
	return m_components.getData<Component>()[entity];
}
