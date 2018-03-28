
#pragma once

#include "io/File.h"
#include "world/render/detail/data/BlockModel.h"

#include <glm/vec3.hpp>
#include <pugixml/pugixml.hpp>

namespace world
{
	namespace render
	{
		class BlockModelLoader
		{
		public:
			BlockModelLoader() = default;
			BlockModelLoader(const glm::vec3 & offset, const glm::vec3 & rotation, const glm::vec3 & scale);
			~BlockModelLoader() = default;

			void loadModel(const io::File & file);
			void loadGeometry(const pugi::xml_node & node);
			void loadSide(const pugi::xml_node & node, const util::Side & side);
			void loadVertices(const pugi::xml_node & node, const util::Side & side);
			void loadIndices(const pugi::xml_node & node, const util::Side & side);

			inline auto extractModel() { return m_model; }

		private:
			data::BlockModel m_model;

			glm::vec3 m_offset{ 0.0f };
			glm::vec3 m_rotation{ 0.0f };
			glm::vec3 m_scale{ 1.0f };
		};
	}
}