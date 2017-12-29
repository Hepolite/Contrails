
#include "Engine.h"

#include "core/allegro/Allegro.h"
#include "ui/Display.h"

struct core::Engine::Impl
{
	allegro::Allegro m_allegro;
	ui::Display m_display;
};

core::Engine::Engine()
{
}
core::Engine::~Engine() = default;

