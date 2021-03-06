
#pragma once

#include "world/detail/Block.h"
#include "world/detail/data/WorldQuery.h"
#include "util/MathGeometry.h"

namespace world
{
	namespace util
	{
		class Query
		{
		public:
			data::WorldQuery readBlock(const glm::ivec3 & pos) const;
			data::WorldQuery readCylinder(const glm::ivec3 & start, const glm::ivec3 & end, math::Axis axis) const;
			data::WorldQuery readEllipse(const glm::ivec3 & start, const glm::ivec3 & end) const;
			data::WorldQuery readRectangle(const glm::ivec3 & start, const glm::ivec3 & end) const;
			data::WorldQuery readLine(const glm::ivec3 & start, const glm::ivec3 & end) const;
			data::WorldQuery readSphere(const glm::ivec3 & center, unsigned int diameter) const;

			data::WorldQuery writeBlock(const Block & block, const glm::ivec3 & pos) const;
			data::WorldQuery writeCylinder(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end, math::Axis axis) const;
			data::WorldQuery writeEllipse(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end) const;
			data::WorldQuery writeRectangle(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end) const;
			data::WorldQuery writeLine(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end) const;
			data::WorldQuery writeSphere(const Block & block, const glm::ivec3 & center, unsigned int diameter) const;
		
		private:
			data::BlockData getBlockData(const Block & block) const;
			data::ColorData getColorData(const Block & block) const;
		};
	}
}