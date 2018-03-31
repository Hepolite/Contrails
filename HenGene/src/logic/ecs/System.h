
#pragma once

#include "logic/ecs/ComponentStorage.h"
#include "logic/ecs/detail/ComponentMask.h"
#include "logic/ecs/detail/Entity.h"
#include "util/Physics.h"

#include <vector>

#define SIMPLE_SYSTEM(SystemName, ...) \
	SystemName : public System<__VA_ARGS__> \
	{ \
	public: \
		SystemName() = default; \
		virtual ~SystemName() = default; \
		virtual void process(const Time & t, const Time & dt) override final; \
	}

namespace core { class Engine; }

namespace logic
{
	namespace ecs
	{
		class SystemBase
		{
		public:
			SystemBase() = default;
			SystemBase(const SystemBase &) = delete;
			SystemBase(SystemBase &&) = delete;
			virtual ~SystemBase() = default;

			SystemBase & operator=(const SystemBase &) = delete;
			SystemBase & operator=(SystemBase &&) = delete;

			inline auto getMask() const { return m_mask; }
			inline void clear() { m_entities.clear(); }

			bool has(const Entity & entity) const;
			bool add(const Entity & entity);
			bool remove(const Entity & entity);

			virtual void initialize(core::Engine & engine) {}
			virtual void process(const Time & t, const Time & dt) = 0;

		protected:
			inline auto begin() const { return m_entities.begin(); }
			inline auto end() const { return m_entities.end(); }

			inline void assignMask(const ComponentMask & mask) { m_mask = mask; }

		private:
			using Entities = std::vector<EntityID>;

			bool validate(const Entity & entity) const;
			Entities::const_iterator find(const Entity & entity) const;

			ComponentMask m_mask;
			Entities m_entities;
		};

		// ...

		template<typename ...Components>
		class System : public SystemBase
		{
		public:
			inline void inject(ComponentStorage & storage) { m_storage = &storage; }

			inline void addComponents(ComponentStorage & storage) { storage.add<Components...>(); }
			inline void assignMask() { SystemBase::assignMask(m_storage->getMask<Components...>()); }

			template<typename Component>
			inline ComponentData<Component> & getData() const { return m_storage->getData<Component>(); }

		private:
			ComponentStorage * m_storage = nullptr;
		};
	}
}
