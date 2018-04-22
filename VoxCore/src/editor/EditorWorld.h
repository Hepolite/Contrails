
#pragma once

#include "editor/Editor.h"
#include "world/World.h"

namespace editor
{
	class EditorWorld : public Editor
	{
	private:
		virtual void init(logic::script::Script & script) override final;
		virtual void process(const Time & t, const Time & dt) override final;

		world::World * m_world = nullptr;
	};
}