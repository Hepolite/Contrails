
#pragma once

#include "logic/event/EventBus.h"
#include "logic/event/EventListener.h"
#include "ui/Mouse.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace editor
{
	namespace util
	{
		class Cursor
		{
		public:
			Cursor() = default;
			Cursor(const Cursor &) = delete;
			Cursor(Cursor &&) = delete;
			~Cursor() = default;

			Cursor & operator=(const Cursor &) = delete;
			Cursor & operator=(Cursor &&) = delete;

			void inject(logic::event::EventBus & bus);

			void setPos(const glm::vec3 & pos);
			glm::vec3 getPos() const;
			glm::vec3 getActualPos() const;
			glm::vec3 getClickedPos() const;
			glm::vec2 getMousePos() const;

			inline auto getClickedButton() const { return m_button; }

			inline void setValidPos(bool valid) { m_hasValidPos = valid; }
			inline bool hasValidPos() const { return m_hasValidPos; }

			inline void lockAxisX(bool locked) { m_lockAxisX = locked; }
			inline void lockAxisY(bool locked) { m_lockAxisY = locked; }
			inline void lockAxisZ(bool locked) { m_lockAxisZ = locked; }
			inline auto isAxisXLocked() const { return m_lockAxisX; }
			inline auto isAxisYLocked() const { return m_lockAxisY; }
			inline auto isAxisZLocked() const { return m_lockAxisZ; }

		private:
			logic::event::Listener m_mouseClick;
			logic::event::Listener m_mouseRelease;
			logic::event::Listener m_mouseMove;

			ui::mouse::Button m_button = ui::mouse::Button::NONE;

			bool m_hasValidPos = false;
			glm::vec3 m_pos{};
			glm::vec3 m_clickedPos{};
			glm::vec2 m_mousePos{};

			bool m_lockAxisX = false;
			bool m_lockAxisY = false;
			bool m_lockAxisZ = false;
		};
	}
}