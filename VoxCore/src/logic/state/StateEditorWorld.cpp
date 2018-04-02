
#include "StateEditorWorld.h"

#include "core/Engine.h"
#include "ui/gui/GuiManager.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "util/Maths.h"
#include "world/Universe.h"
#include "world/util/Query.h"
#include "world/World.h"

namespace
{
	bool keyLeft = false;
	bool keyRight = false;
	bool keyUp = false;
	bool keyDown = false;
	glm::vec2 mouseDelta{ 0.0f, 0.0f };
}

void logic::state::StateEditorWorld::initialize(core::Engine & engine)
{
	engine.getGuiManager().open("data/guis/editor_world.xml");
	engine.getUniverse().createWorld("world");

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

	// Set up a small test world
	auto * world = engine.getUniverse().getWorld("world");
	auto & blocks = world->getBlockRegistry();

	world::util::Query query;
	world->write(query.writeRectangle(blocks["stone"], { -31, -31, 0 }, { 31, 31, 3 }));
	world->write(query.writeRectangle(blocks["dirt"], { -31, -31, 4 }, { 31, 31, 5 }));
	world->write(query.writeRectangle(blocks["grass"], { -31, -31, 6 }, { 31, 31, 6 }));
	world->write(query.writeRectangle(blocks["stone"], { 0, 0, 12 }, { 15, 15, 12 }));
	world->write(query.writeRectangle(blocks["dirt"], { 0, 0, 13 }, { 15, 15, 14 }));
	world->write(query.writeRectangle(blocks["grass"], { 0, 0, 15 }, { 15, 15, 15 }));
	world->write(query.writeBlock(blocks["glowstone"], { -15, -15, -3 }));
	world->calculateLight();

	// Place camera in a suitable location
	m_camera = &engine.getScene().getCamera(render::scene::CameraType::NORMAL);
	m_camera->setPosition({ -32, -32, -32 });
	m_camera->lookTowards({ 0, 0, 0 });
}
void logic::state::StateEditorWorld::deinitialize(core::Engine & engine)
{
	engine.getGuiManager().close("data/guis/editor_world.xml");
	engine.getUniverse().destroyWorld("world");
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
