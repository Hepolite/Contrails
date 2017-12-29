
#include "Display.h"

#include <algorithm>

ui::Display::Display(const glm::ivec2 & size, bool fullscreen)
{
	const auto OPENGL = ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0;
	if (fullscreen)
		al_set_new_display_flags(OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
	else
		al_set_new_display_flags(OPENGL | ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

	al_set_new_display_option(ALLEGRO_COLOR_SIZE, 32, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 24, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_STENCIL_SIZE, 8, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_AUX_BUFFERS, 0, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

	m_handle = al_create_display(size.x, size.y);
}
ui::Display::~Display()
{
	if (m_handle != nullptr)
		al_destroy_display(m_handle);
}
ui::Display::Display(Display && other)
{
	std::swap(*this, other);
}
ui::Display & ui::Display::operator=(Display && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

glm::ivec2 ui::Display::getSize() const
{
	return glm::ivec2{ al_get_display_width(m_handle), al_get_display_height(m_handle) };
}
bool ui::Display::isFullscreen() const
{
	return al_get_display_flags(m_handle) & (ALLEGRO_FULLSCREEN | ALLEGRO_FULLSCREEN_WINDOW);
}
