
#pragma once

#include "logic/ecs/ComponentStorage.h"
#include "logic/ecs/EntityRegistry.h"
#include "logic/ecs/SystemRegistry.h"
#include "logic/ecs/detail/Entity.h"
#include "util/Physics.h"

namespace logic { namespace ecs { class SystemRegistry; } }

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

			inline void process(const Time & t, const Time & dt) { m_systems.process(t, dt); }

			template<typename ...Systems> void registerSystems();
			void clearSystems();

			template<typename ...Components> logic::ecs::EntityID createEntity();
			template<typename ...Components> void attachEntityComponent(logic::ecs::EntityID entity);
			template<typename ...Components> void detachEntityComponent(logic::ecs::EntityID entity);
			template<typename Component> Component & getEntityData(logic::ecs::EntityID entity);
			void deleteEntity(logic::ecs::EntityID entity);
			void clearEntities();

		private:
			logic::ecs::ComponentStorage m_components;
			logic::ecs::SystemRegistry m_systems;
			logic::ecs::EntityRegistry m_entities;
		};
	}
}

template<typename ...Systems>
inline void core::scene::Scene::registerSystems()
{
	m_systems.addSystem<Systems...>();
}

template<typename ...Components>
inline logic::ecs::EntityID core::scene::Scene::createEntity()
{
	const auto id = m_entities.createEntity();
	m_entities.attachComponent<Components...>(id);
	m_systems.addEntity(m_entities.getEntity(id));
	return id;
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
