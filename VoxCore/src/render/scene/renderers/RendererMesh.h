
#pragma once

#include "core/Engine.h"
#include "render/scene/components/ComponentMesh.h"
#include "render/scene/Renderer.h"
#include "render/uboRegistry.h"

namespace render
{
	namespace scene
	{
		template<typename T>
		class RendererMesh : public Renderer<ComponentMesh<T>>
		{
		public:
			virtual void initialize(core::Engine & engine) override final;
			virtual void render(const RenderContext & context, const Time & t, const Time & dt) const override final;

		private:
			const opengl::ubo * m_model;
		};
	}
}

template<typename T>
inline void render::scene::RendererMesh<T>::initialize(core::Engine & engine)
{
	m_model = &engine.getUboRegistry().get("Model");
}
template<typename T>
inline void render::scene::RendererMesh<T>::render(const RenderContext & context, const Time & t, const Time & dt) const
{
	auto & data = getData<ComponentMesh<T>>();
	for (auto entity : *this)
	{
		auto & entry = data[entity];
		m_model->set("transform", entry.m_transform);
		entry.m_program->bind();
		entry.m_mesh.render();
	}
}
