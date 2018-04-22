
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
		using Vertices = std::vector<glm::vec3>;
		using Indices = std::vector<unsigned int>;

		class Shape
		{
		public:
			Shape() = default;
			Shape(const Shape &) = delete;
			Shape(Shape &&) = delete;
			virtual ~Shape() = default;

			Shape & operator=(const Shape &) = delete;
			Shape & operator=(Shape &&) = delete;

			void stretch(const glm::ivec3 & start, const glm::ivec3 & end);
			void setPos(const glm::ivec3 & pos);
			void setSize(const glm::ivec3 & size);
			inline void setSizeX(int x) { setSize({ x, m_size.y, m_size.z }); }
			inline void setSizeY(int y) { setSize({ m_size.x, y, m_size.z }); }
			inline void setSizeZ(int z) { setSize({ m_size.x, m_size.y, z }); }
			inline void setDynamic(bool dynamic) { m_dynamic = dynamic; }

			inline auto getPos() const { return m_pos; }
			inline auto getSize() const { return m_size; }
			inline auto isDynamic() const { return m_dynamic; }

			render::Mesh<glm::vec3> * getMesh() const;

			inline auto read() const { return query({}); }
			inline auto write(const world::Block & block) const { return query(block); }

		protected:
			glm::ivec3 getStart() const;
			glm::ivec3 getEnd() const;

			void updateMesh() const;

			virtual world::data::WorldQuery query(const world::Block & block) const = 0;
			virtual void mesh(Vertices & vertices, Indices & indices) const = 0;

		private:
			mutable std::unique_ptr<render::Mesh<glm::vec3>> m_mesh;

			glm::ivec3 m_pos{ 0 };
			glm::ivec3 m_size{ 1 };
			bool m_dynamic = false;
		};

		// ...

		namespace detail
		{
			void meshLine(const glm::vec3 & start, const glm::vec3 & end, Vertices & vertices, Indices & indices);
			void meshRectangle(const glm::vec3 & start, const glm::vec3 & end, Vertices & vertices, Indices & indices);
		}
	}
}