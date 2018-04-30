
#include "CameraHandler.h"

#include "logic/event/Events.h"
#include "util/Maths.h"

#include <plog/Log.h>

namespace
{
	constexpr float MAX_PITCH = 89.9f;
	constexpr float SENSITIVITY_ZOOMING = 0.5f;
	constexpr glm::vec2 SENSITIVITY_ROTATION{ 15.0f, 10.0f };

	constexpr float DISTANCE_MIN = 5.0f;
	constexpr float DISTANCE_MAX = 1000.0f;
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
void editor::util::CameraHandlerOrbital::handleZooming(float zoom)
{
	const auto sensitivity = m_sensitivity * math::pow(m_distance, 0.5f) * SENSITIVITY_ZOOMING;
	const auto oldDistance = m_distance;

	auto pos = getCamera().getPosition();
	auto rot = getCamera().getRotation();

	m_distance = math::max(DISTANCE_MIN, math::min(DISTANCE_MAX, m_distance * (1.0f - zoom * sensitivity)));
	pos -= (m_distance - oldDistance) * math::cartesian(rot);

	getCamera().setPosition(pos);
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
		handleZooming(event.m_scrollDelta.x);
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
