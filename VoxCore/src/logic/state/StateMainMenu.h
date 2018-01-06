
#pragma once

#include "asset/AssetRef.h"
#include "logic/state/State.h"
#include "render/Mesh.h"
#include "render/opengl/Program.h"

#include <glm/vec3.hpp>

namespace logic
{
	namespace state
	{
		class StateMainMenu : public State
		{
		public:
			virtual void initialize(core::Engine & engine) override final;
			virtual void deinitialize(core::Engine & engine) override final;
			virtual void process(const Time & t, const Time & dt) override final;

		private:
			void render(const Time & t, const Time & dt) const;

			render::Mesh<glm::vec3> m_mesh;
			asset::Ref<render::opengl::Program> m_program;
		};
	}
}