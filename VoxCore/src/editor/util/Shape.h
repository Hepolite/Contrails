
#pragma once

#include "render/Mesh.h"

#include <glm/vec3.hpp>
#include <vector>

namespace editor
{
	namespace util
	{
		class Shape
		{
		public:
			void setPos(const glm::ivec3 & pos);
			void setSize(const glm::ivec3 & size);
			inline void setSizeX(int x) { setSize({ x, m_size.y, m_size.z }); }
			inline void setSizeY(int y) { setSize({ m_size.x, y, m_size.z }); }
			inline void setSizeZ(int z) { setSize({ m_size.x, m_size.y, z }); }
			void setDynamic(bool dynamic);
			void setCentered(bool centered);

			inline auto getPos() const { return m_pos; }
			inline auto getSize() const { return m_size; }
			inline auto isDynamic() const { return m_dynamic; }
			inline auto isCentered() const { return m_centered; }

			void mesh(render::Mesh<glm::vec3> & mesh) const;

		protected:
			virtual void mesh(std::vector<glm::vec3> & vertices, std::vector<unsigned int> & indices) const = 0;

		private:
			glm::ivec3 m_pos;
			glm::ivec3 m_size;
			bool m_dynamic;
			bool m_centered;
		};
	}
}