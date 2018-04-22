
#pragma once

#include "editor/util/Shape.h"

namespace editor
{
	namespace util
	{
		class ShapeBox : public Shape
		{
		public:


		private:
			virtual world::data::WorldQuery query(const world::Block & block) const override final;
			virtual void mesh(std::vector<glm::vec3> & vertices, std::vector<unsigned int> & indices) const override final;
		};
	}
}