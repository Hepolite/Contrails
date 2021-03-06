
#pragma once

#include "render/Mesh.h"

#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace editor
{
	namespace util
	{
		class Grid
		{
		public:
			Grid() = default;
			Grid(const Grid &) = delete;
			Grid(Grid &&) = delete;
			~Grid() = default;

			Grid & operator=(const Grid &) = delete;
			Grid & operator=(Grid &&) = delete;

			void setPos(const glm::vec3 & pos);
			void setSize(float size);
			void setResolution(float resolution);
			inline void setVisible(bool visible) { m_visible = visible; }

			inline auto getPos() const { return m_pos; }
			inline auto getSize() const { return m_size; }
			inline auto getResolution() const { return m_resolution; }
			inline auto isVisible() const { return m_visible; }

			inline auto getMesh() const { updateMesh(); return m_mesh.get(); }

		private:
			void updateMesh() const;

			mutable std::unique_ptr<render::Mesh<glm::vec3>> m_mesh;
			mutable bool m_updateMesh = false;

			glm::vec3 m_pos{};
			float m_size = 100.0f;
			float m_resolution = 1.0f;
			bool m_visible = false;
		};
	}
}