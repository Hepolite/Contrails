
#pragma once

#include "util/Physics.h"
#include "render/RenderLayer.h"
#include "render/scene/detail/SceneNode.h"

#include <vector>

namespace render
{
	namespace scene
	{
		class SceneLayer
		{
		public:
			SceneLayer() noexcept = default;
			SceneLayer(RenderLayer layer) noexcept : m_layer(layer) {}
			SceneLayer(const SceneLayer &) = delete;
			SceneLayer(SceneLayer &&) noexcept = default;
			~SceneLayer() = default;

			SceneLayer & operator=(const SceneLayer &) = delete;
			SceneLayer & operator=(SceneLayer &&) noexcept = default;

			unsigned int add(const SceneRender & render);
			bool remove(unsigned int id);

			void render(const Time & t, const Time & dt) const;

		private:
			std::vector<SceneNode> m_nodes;

			RenderLayer m_layer = RenderLayer::INVISIBLE;
			unsigned int m_uniqueId = 0u;
		};
	}
}