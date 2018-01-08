
#pragma once

#include "core/scene/Scene.h"
#include "ui/gui/GuiManager.h"
#include "util/Physics.h"

namespace render
{
	namespace core
	{
		class Pipeline
		{
		public:
			inline void inject(const ::core::scene::Scene & scene) { m_scene = &scene; }
			inline void inject(const ::ui::gui::GuiManager & gui) { m_gui = &gui; }

			void render(const Time & t, const Time & dt) const;

		private:
			const ::core::scene::Scene * m_scene = nullptr;
			const ::ui::gui::GuiManager * m_gui = nullptr;
		};
	}
}