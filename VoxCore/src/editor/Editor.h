
#pragma once

#include "asset/AssetRegistry.h"
#include "core/scene/Scene.h"
#include "editor/util/Cursor.h"
#include "logic/event/EventBus.h"
#include "logic/script/Script.h"
#include "render/RenderContext.h"
#include "render/uboRegistry.h"
#include "ui/gui/Gui.h"
#include "util/Physics.h"

#include <memory>
#include <glm/mat4x4.hpp>

namespace editor
{
	class Editor
	{
	public:
		Editor();
		Editor(const Editor &) = delete;
		Editor(Editor &&) = delete;
		virtual ~Editor();

		Editor & operator=(const Editor &) = delete;
		Editor & operator=(Editor &&) = delete;

		void inject(const asset::AssetRegistry & assets);
		void inject(const render::uboRegistry & ubos);
		void inject(logic::event::EventBus & bus);
		void inject(ui::gui::Gui & gui);
		void inject(core::scene::Scene & scene);

	protected:
		virtual void init(logic::script::Script & script) {}
		virtual void process(const Time & t, const Time & dt) {}
		virtual void render(const render::RenderContext & context, const Time & t, const Time & dt) const {}

		util::Cursor & getCursor();
		core::scene::Scene & getScene();

		void setTransform(const glm::mat4 & transform) const;

	private:
		class Impl;
		std::unique_ptr<Impl> m_impl;
	};
}