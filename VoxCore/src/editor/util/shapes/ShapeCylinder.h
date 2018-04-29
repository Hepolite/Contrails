
#pragma once

#include "editor/util/shapes/Shape.h"
#include "util/MathGeometry.h"

namespace editor
{
	namespace util
	{
		class ShapeCylinder : public Shape
		{
		public:
			ShapeCylinder() { setName("cylinder"); }
			~ShapeCylinder() = default;

			inline void setAxis(math::Axis axis) { m_axis = axis; updateMesh(); }
			inline auto getAxis() const { return m_axis; }

		private:
			virtual world::data::WorldQuery query(const world::Block & block) const override final;
			virtual void mesh(Vertices & vertices, Indices & indices) const override final;

			math::Axis m_axis = math::Axis::Z;
		};
	}
}