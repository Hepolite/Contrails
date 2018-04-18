
#pragma once

#include "asset/AssetRef.h"
#include "render/Mesh.h"
#include "render/opengl/Program.h"

#include <glm/mat4x4.hpp>

namespace render
{
	namespace scene
	{
		template<typename T>
		struct ComponentMesh
		{
			asset::Ref<render::opengl::Program> m_program;
			render::Mesh<T> m_mesh;

			glm::mat4 m_transform;
		};
	}
}