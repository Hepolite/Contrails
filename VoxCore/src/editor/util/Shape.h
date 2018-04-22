
#pragma once

#include "render/Mesh.h"
#include "world/detail/Block.h"
#include "world/detail/data/WorldQuery.h"

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

namespace editor
{
	namespace util
	{
		class Shape
		{
		public:
			Shape() = default;
			Shape(const Shape &) = delete;
			Shape(Shape &&) = delete;
			virtual ~Shape() = default;

			Shape & operator=(const Shape &) = delete;
			Shape & operator=(Shape &&) = delete;

			void setPos(const glm::ivec3 & pos);
			void setSize(const glm::ivec3 & size);
			inline void setSizeX(int x) { setSize({ x, m_size.y, m_size.z }); }
			inline void setSizeY(int y) { setSize({ m_size.x, y, m_size.z }); }
			inline void setSizeZ(int z) { setSize({ m_size.x, m_size.y, z }); }
			inline void setDynamic(bool dynamic) { m_dynamic = dynamic; }

			inline auto getPos() const { return m_pos; }
			inline auto getSize() const { return m_size; }
			inline auto isDynamic() const { return m_dynamic; }

			inline auto getMesh() const { return m_mesh.get(); }

			inline auto read() const { return query({}); }
			inline auto write(const world::Block & block) const { return query(block); }

		protected:
			inline auto getStart() const { return getPos() - getSize() / 2; }
			inline auto getEnd() const { return getStart() + getSize() - 1; }

			void updateMesh();

			virtual world::data::WorldQuery query(const world::Block & block) const = 0;
			virtual void mesh(std::vector<glm::vec3> & vertices, std::vector<unsigned int> & indices) const = 0;

		private:
			std::unique_ptr<render::Mesh<glm::vec3>> m_mesh;

			glm::ivec3 m_pos{ 0 };
			glm::ivec3 m_size{ 1 };
			bool m_dynamic = false;
		};
	}
}