
#include "CameraHandler.h"

#include "logic/event/Events.h"
#include "util/MathGeometry.h"

namespace
{
	constexpr float MAX_PITCH = 89.9f;
	constexpr glm::vec2 SENSITIVITY_ROTATION{ 15.0f, 10.0f };
}

void editor::util::CameraHandlerOrbital::handleRotation(const glm::vec2 & delta)
{
	const auto sensitivity = m_sensitivity * SENSITIVITY_ROTATION;
	const auto oldRot = getCamera().getRotation();

	auto pos = getCamera().getPosition();
	auto rot = oldRot;

	if (m_holdKeySecondary)
		rot += sensitivity * delta;
	else
	{
		rot -= sensitivity * delta;
		pos += m_distance * (math::cartesian(oldRot) - math::cartesian(rot));
	}
	rot.y = rot.y < -MAX_PITCH ? -MAX_PITCH : rot.y > MAX_PITCH ? MAX_PITCH : rot.y;

	getCamera().setPosition(pos);
	getCamera().setRotation(rot);
}

void editor::util::CameraHandlerOrbital::setupListeners(logic::event::EventBus & bus)
{
	m_mousePress = bus.add<logic::event::MousePress>([this](auto & event)
	{
		m_holdMouseButton = event.m_button == ui::mouse::Button::MIDDLE;
	});
	m_mouseRelease = bus.add<logic::event::MouseRelease>([this](auto & event)
	{
		m_holdMouseButton = false;
	});
	m_mouseMove = bus.add<logic::event::MouseMove>([this](auto & event)
	{
		if (m_holdMouseButton)
			handleRotation(event.m_posDelta);
	});
	m_keyPress = bus.add<logic::event::KeyPress>([this](auto & event)
	{
		m_holdKeyPrimary = event.m_key == ALLEGRO_KEY_LSHIFT;
		m_holdKeySecondary = event.m_key == ALLEGRO_KEY_LCTRL;
	});
	m_keyRelease = bus.add<logic::event::KeyRelease>([this](auto & event)
	{
		m_holdKeyPrimary = m_holdKeySecondary = false;
	});
}
