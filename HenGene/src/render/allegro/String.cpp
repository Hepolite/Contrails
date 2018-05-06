
#include "String.h"

#include <allegro5/allegro_font.h>

render::allegro::String::String(const std::string & str)
	: m_handle(al_ustr_new(str.c_str()))
{}
render::allegro::String::~String()
{
	if (m_handle != nullptr)
		al_ustr_free(m_handle);
}

void render::allegro::String::draw(const glm::vec2 & pos) const
{
	if (m_font)
		al_draw_ustr(m_font->get(m_size, m_flags), m_color, pos.x, pos.y, ALLEGRO_ALIGN_INTEGER, m_handle);
}
