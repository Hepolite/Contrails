
#pragma once

#include "util/Physics.h"
#include "render/RenderLayer.h"
#include "render/scene/detail/SceneLayer.h"

#include <unordered_map>

namespace render
{
	namespace scene
	{
		using SceneRef = std::pair<RenderLayer, unsigned int>;

		class Scene
		{
		public:
			SceneRef add(const SceneRender & render, RenderLayer layer);
			bool remove(const SceneRef & ref);

			void render(const Time & t, const Time & dt) const;
			void render(const Time & t, const Time & dt, RenderLayer layer) const;

		private:
			std::unordered_map<RenderLayer, SceneLayer> m_layers;
		};
	}
}