
#include "Font.h"

#include <allegro5/allegro_font.h>

render::allegro::Font::Font(Font && other) noexcept
{
	*this = std::move(other);
}
render::allegro::Font::~Font()
{
	for (auto & it : m_handles)
		al_destroy_font(it.second);
}

render::allegro::Font & render::allegro::Font::operator=(Font && other) noexcept
{
	if (this != &other)
	{
		std::swap(m_handles, other.m_handles);
		std::swap(m_file, other.m_file);
	}
	return *this;
}

bool render::allegro::Font::load(const io::File & file)
{
	m_file = file;
	return m_file.exists();
}

ALLEGRO_FONT * render::allegro::Font::get(unsigned int size, unsigned int flags)
{
	const auto key = std::to_string(size) + "-" + std::to_string(flags);
	const auto it = m_handles.find(key);
	if (it == m_handles.end())
	{
		auto * font = al_load_font(m_file.getPath().c_str(), static_cast<int>(size), static_cast<int>(flags));
		return font == nullptr ? nullptr : m_handles.emplace(key, font).first->second;
	}
	return it->second;
}
