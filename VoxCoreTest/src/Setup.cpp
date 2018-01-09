
#include "Setup.h"

#include "render/allegro/Allegro.h"
#include "ui/Display.h"

#include <memory>

namespace
{
	std::unique_ptr<render::allegro::Allegro> allegro;
	std::unique_ptr<ui::Display> display;
}

setup::Context::Context()
{
	if (allegro == nullptr)
		allegro = std::make_unique<render::allegro::Allegro>();
	if (display == nullptr)
		display = std::make_unique<ui::Display>(glm::ivec2{ 640, 480 }, false);
}

ui::Display & setup::Context::getDisplay() const
{
	return *display;
}
