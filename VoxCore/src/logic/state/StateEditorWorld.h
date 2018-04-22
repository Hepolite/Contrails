
#pragma once

#include "editor/EditorWorld.h"
#include "logic/event/EventListener.h"
#include "logic/state/State.h"
#include "render/scene/Camera.h"

namespace logic
{
	namespace state
	{
		class StateEditorWorld : public State<StateEditorWorld>
		{
		public:
			virtual void initialize(core::Engine & engine) override final;
			virtual void deinitialize(core::Engine & engine) override final;
			virtual void process(const Time & t, const Time & dt) override final;

		private:
			editor::EditorWorld m_editor;

			logic::event::Listener m_keyPress, m_keyRelease;
			logic::event::Listener m_mouseMove;

			render::scene::Camera * m_camera = nullptr;
		};
	}
}