
#pragma once

#include "logic/ecs/ComponentStorage.h"
#include "logic/ecs/detail/ComponentMask.h"
#include "logic/ecs/detail/Entity.h"

#include <vector>

namespace logic
{
	namespace ecs
	{
		class EntityRegistry
		{
		public:
			EntityRegistry() noexcept = default;
			EntityRegistry(const EntityRegistry &) = delete;
			EntityRegistry(EntityRegistry &&) = delete;
			~EntityRegistry() noexcept = default;

			EntityRegistry & operator=(const EntityRegistry &) = delete;
			EntityRegistry & operator=(EntityRegistry &&) = delete;

			inline void inject(ComponentStorage & components) { m_components = &components; }

			bool hasEntity(EntityID entity) const;
			Entity & getEntity(EntityID entity);
			EntityID createEntity();
			bool deleteEntity(EntityID entity);

			template<typename ...Components> void attachComponent(EntityID entity);
			template<typename ...Components> void detachComponent(EntityID entity);

			inline void clear() { m_uniqueId = 0u; m_entities.clear(); }
			inline auto & getEntities() const { return m_entities; }

		private:
			template<typename First, typename Second, typename ...Remaining> void attachComponent(Entity & entity);
			template<typename Component> void attachComponent(Entity & entity);
			template<typename First, typename Second, typename ...Remaining> void detachComponent(Entity & entity);
			template<typename Component> void detachComponent(Entity & entity);

			std::vector<Entity>::iterator findAmongEntities(EntityID entity);
			std::vector<Entity>::const_iterator findAmongEntities(EntityID entity) const;
			std::vector<EntityID>::const_iterator findAmongAvailable(EntityID entity) const;

			std::vector<Entity> m_entities;		// Sorted lowest to highest
			std::vector<EntityID> m_available;	// Sorted highest to lowest
			unsigned int m_uniqueId = 0u;

			ComponentStorage * m_components = nullptr;
		};
	}
}

template<typename ...Components>
inline void logic::ecs::EntityRegistry::attachComponent(EntityID entity)
{
	attachComponent<Components...>(getEntity(entity));
}
template<typename First, typename Second, typename ...Remaining>
inline void logic::ecs::EntityRegistry::attachComponent(Entity & entity)
{
	attachComponent<First>(entity);
	attachComponent<Second, Remaining...>(entity);
}
template<typename Component>
inline void logic::ecs::EntityRegistry::attachComponent(Entity & entity)
{
	entity.m_mask[m_components->getId<Component>()] = true;
	m_components->getData<Component>()[entity.m_id];
}
template<typename ...Components>
inline void logic::ecs::EntityRegistry::detachComponent(EntityID entity)
{
	detachComponent<Components...>(getEntity(entity));
}
template<typename First, typename Second, typename ...Remaining>
inline void logic::ecs::EntityRegistry::detachComponent(Entity & entity)
{
	detachComponent<First>(entity);
	detachComponent<Second, Remaining...>(entity);
}
template<typename Component>
inline void logic::ecs::EntityRegistry::detachComponent(Entity & entity)
{
	entity.m_mask[m_components->getId<Component>()] = false;
	m_components->getData<Component>().remove(entity.m_id);
}