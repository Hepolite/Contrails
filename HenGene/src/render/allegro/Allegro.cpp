
#include "Allegro.h"

#include <plog/Log.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <functional>
#include <string>

namespace
{
	bool install(const std::function<void()> & func, const std::string & succeeded)
	{
		func();
		LOG_INFO << succeeded;
		return false;
	}
	bool install(const std::function<bool()> & func, const std::string & succeeded, const std::string & failed)
	{
		if (func())
		{
			LOG_INFO << succeeded;
			return false;
		}
		else
		{
			LOG_FATAL << failed;
			return true;
		}
	}
}

render::allegro::Allegro::Allegro()
{
	LOG_INFO << "Initializing Allegro...";

	if (!al_init())
		LOG_FATAL << "Failed to initialize Allegro!";
	else
	{
		m_hasErrors = false;
		m_hasErrors |= install(al_init_image_addon, "Initialized image addon", "Failed to initialize image addon");
		m_hasErrors |= install(al_init_primitives_addon, "Initialized primitives addon", "Failed to initialize primitives addon");
		m_hasErrors |= install(al_init_font_addon, "Initialized font addon");
		m_hasErrors |= install(al_init_ttf_addon, "Initialized truetype font addon", "Failed to initialize truetype font addon");
		m_hasErrors |= install(al_install_keyboard, "Initialized keyboard", "Failed to initialize keyboard");
		m_hasErrors |= install(al_install_mouse, "Initialized mouse", "Failed to initialize mouse");
		m_isInitialized = true;
	}
}
render::allegro::Allegro::~Allegro()
{
	if (!m_isInitialized)
		return;

	LOG_INFO << "Shutting down Allegro";

	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_system();
}
