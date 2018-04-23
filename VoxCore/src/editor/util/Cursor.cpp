
#include "Cursor.h"

#include "logic/event/Events.h"

void editor::util::Cursor::inject(logic::event::EventBus & bus)
{
	m_mouseClick = bus.add<logic::event::MousePress>([this](auto & event)
	{
		if (m_button != ui::mouse::Button::NONE || !m_hasValidPos)
			return;
		m_button = event.m_button;
		m_clickedPos = m_pos;
	});
	m_mouseRelease = bus.add<logic::event::MouseRelease>([this](auto & event)
	{
		m_button = ui::mouse::Button::NONE;
	});
	m_mouseMove = bus.add<logic::event::MouseMove>([this](auto & event)
	{
		m_mousePos = event.m_pos;
	});
}

void editor::util::Cursor::setPos(const glm::vec3 & pos)
{
	m_pos = pos;
}
glm::vec3 editor::util::Cursor::getPos() const
{
	auto delta = m_pos - m_clickedPos;
	if (m_lockAxisX) delta.x = 0.0f;
	if (m_lockAxisY) delta.y = 0.0f;
	if (m_lockAxisZ) delta.z = 0.0f;
	return m_clickedPos + delta;
}
glm::vec3 editor::util::Cursor::getActualPos() const
{
	return m_pos;
}
glm::vec3 editor::util::Cursor::getClickedPos() const
{
	return m_clickedPos;
}
glm::vec2 editor::util::Cursor::getMousePos() const
{
	return m_mousePos;
}
