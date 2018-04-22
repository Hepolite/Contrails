
#include "EditorWorld.h"

#include "logic/script/ScriptUtil.h"
#include "world/util/Raytrace.h"
#include "util/MathGeneric.h"

void editor::EditorWorld::init(logic::script::Script & script)
{
	logic::script::util::addFun(script, [this](world::World * world) { m_world = world; }, "SET_EDITOR_WORLD");
}

void editor::EditorWorld::process(const Time & t, const Time & dt)
{
	if (m_world == nullptr)
		return;
	auto & cursor = getCursor();

	cursor.setValidPos(false);
	for (world::util::Raytrace ray{ glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 0, 1 }, 1500.0f }; ray.isValid(); ray.next())
	{
		if (m_world->readBlock(ray.getBlockPos()).getId() == 0u)
			continue;
		cursor.setValidPos(true);
		cursor.setPos(math::round(ray.getPos()));
		break;
	}
}
