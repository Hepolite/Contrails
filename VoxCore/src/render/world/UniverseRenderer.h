
#pragma once

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "world/Universe.h"

#include <memory>

namespace render
{
	namespace world
	{
		class UniverseRenderer
		{
		public:
			UniverseRenderer();
			UniverseRenderer(const UniverseRenderer &) = delete;
			UniverseRenderer(UniverseRenderer &&) = delete;
			~UniverseRenderer();

			UniverseRenderer & operator=(const UniverseRenderer&) = delete;
			UniverseRenderer & operator=(UniverseRenderer &&) = delete;

			void inject(::logic::event::EventBus & bus);
			void inject(::world::Universe & universe);



		private:
			class Impl;
			std::unique_ptr<Impl> m_impl = nullptr;
		};
	}
}