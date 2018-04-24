
#pragma once

#include "editor/util/Shape.h"

namespace editor
{
	namespace util
	{
		class ShapePoint : public Shape
		{
		public:
			ShapePoint() { setName("point"); }
			~ShapePoint() = default;

		private:
			virtual world::data::WorldQuery query(const world::Block & block) const override final;
			virtual void mesh(Vertices & vertices, Indices & indices) const override final;
		};
	}
}