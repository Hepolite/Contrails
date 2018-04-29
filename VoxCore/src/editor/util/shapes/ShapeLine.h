
#pragma once

#include "editor/util/shapes/Shape.h"

namespace editor
{
	namespace util
	{
		class ShapeLine : public Shape
		{
		public:
			ShapeLine() { setName("line"); }
			~ShapeLine() = default;

		private:
			virtual world::data::WorldQuery query(const world::Block & block) const override final;
			virtual void mesh(Vertices & vertices, Indices & indices) const override final;
		};
	}
}