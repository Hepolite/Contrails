
#include "EditorWorld.h"

#include "logic/script/ScriptUtil.h"
#include "world/util/Raytrace.h"
#include "util/MathGeneric.h"

void editor::EditorWorld::init(logic::script::Script & script)
{
	logic::script::util::addFun(script, [this](world::World * world) { m_world = world; }, "SET_EDITOR_WORLD");
	logic::script::util::addFun(script, [this]() { return m_world; }, "GET_EDITOR_WORLD");
}

void editor::EditorWorld::process(const Time & t, const Time & dt)
{
	if (m_world == nullptr)
		return;
	auto & cursor = getCursor();
	auto & camera = getScene().getCamera(render::scene::CameraType::NORMAL);
	cursor.setValidPos(false);

	const auto dir = camera.getLookVector(camera.getMouseVector(cursor.getMousePos()));
	for (world::util::Raytrace ray{ camera.getPosition(), dir, 150.0f }; ray.isValid(); ray.next())
	{
		if (m_world->readBlock(ray.getBlockPos()).getId() == 0u)
			continue;
		cursor.setValidPos(true);
		cursor.setPos(ray.getBlockPos());
		break;
	}
}
