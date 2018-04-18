
#include "StateEditorWorld.h"

#include "core/Engine.h"
#include "ui/gui/GuiManager.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "util/Maths.h"

namespace
{
	constexpr char * GUI_PATH = "data/guis/editor_world.xml";

	bool keyLeft = false;
	bool keyRight = false;
	bool keyUp = false;
	bool keyDown = false;
	glm::vec2 mouseDelta{ 0.0f, 0.0f };
}

void logic::state::StateEditorWorld::initialize(core::Engine & engine)
{
	engine.getGuiManager().open(GUI_PATH);

	// Set up basic camera control
	m_keyPress = engine.getEventBus().add<logic::event::KeyPress>([](auto & event)
	{
		switch (event.m_key)
		{
		case ALLEGRO_KEY_A: keyLeft = true;		break;
		case ALLEGRO_KEY_D: keyRight = true;	break;
		case ALLEGRO_KEY_W: keyUp = true;		break;
		case ALLEGRO_KEY_S: keyDown = true;		break;
		default: break;
		}
	});
	m_keyRelease = engine.getEventBus().add<logic::event::KeyRelease>([](auto & event)
	{
		switch (event.m_key)
		{
		case ALLEGRO_KEY_A: keyLeft = false;	break;
		case ALLEGRO_KEY_D: keyRight = false;	break;
		case ALLEGRO_KEY_W: keyUp = false;		break;
		case ALLEGRO_KEY_S: keyDown = false;	break;
		default: break;
		}
	});
	m_mouseMove = engine.getEventBus().add<logic::event::MouseMove>([](auto & event)
	{
		mouseDelta += event.m_posDelta;
	});

	// Place camera in a suitable location
	m_camera = &engine.getScene().getCamera(render::scene::CameraType::NORMAL);
	m_camera->setPosition({ -32, -32, -32 });
	m_camera->lookTowards({ 0, 0, 0 });
}
void logic::state::StateEditorWorld::deinitialize(core::Engine & engine)
{
	engine.getGuiManager().close(GUI_PATH);
}

void logic::state::StateEditorWorld::process(const Time & t, const Time & dt)
{
	float speed = 15.0f * static_cast<float>(dt());
	float sensitivity = 25.f * static_cast<float>(dt());

	glm::vec3 pos = m_camera->getPosition();
	glm::vec2 rot = m_camera->getRotation();

	if (keyUp)
		pos += math::cartesian(rot) * speed;
	if (keyDown)
		pos -= math::cartesian(rot) * speed;
	if (keyLeft)
		pos += math::cartesian(rot.x + 90.0f, 0.0f) * speed;
	if (keyRight)
		pos += math::cartesian(rot.x - 90.0f, 0.0f) * speed;
	rot -= mouseDelta * sensitivity;
	mouseDelta = { 0.0f, 0.0f };

	m_camera->setPosition(pos);
	m_camera->setRotation(rot);
}
