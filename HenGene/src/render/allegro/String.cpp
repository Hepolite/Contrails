
#include "String.h"

render::allegro::String::String() : String("") {}
render::allegro::String::String(const std::string & string) { setString(string); }
render::allegro::String::String(const String & other) { *this = other; }
render::allegro::String::String(String && other) { *this = std::move(other); }
render::allegro::String::~String()
{
	al_ustr_free(m_handle);
}

render::allegro::String & render::allegro::String::operator=(const String & other)
{
	if (this != &other)
	{
		if (m_handle != nullptr)
			al_ustr_free(m_handle);
		m_handle = al_ustr_dup(other.m_handle);
	}
	return *this;
}
render::allegro::String & render::allegro::String::operator=(String && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

void render::allegro::String::setString(const std::string & string)
{
	if (m_handle != nullptr)
		al_ustr_free(m_handle);
	m_handle = al_ustr_new(string.c_str());
}

std::string render::allegro::String::getString() const
{
	return al_cstr(m_handle);
}
unsigned int render::allegro::String::length() const
{
	return al_ustr_length(m_handle);
}
unsigned int render::allegro::String::at(unsigned int index) const
{
	const auto codepoint = al_ustr_get(m_handle, index);
	return codepoint < 0 ? '\0' : codepoint;
}
unsigned int render::allegro::String::next(unsigned int & index) const
{
	int i = index;
	const auto codepoint = al_ustr_get_next(m_handle, &i);
	index = i;
	return codepoint < 0 ? '\0' : codepoint;
}
