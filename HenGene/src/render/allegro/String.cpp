
#include "String.h"

render::allegro::String::String() : String("") {}
render::allegro::String::String(ALLEGRO_USTR * handle) : m_handle(handle) {}
render::allegro::String::String(const std::string & str) : m_handle(al_ustr_new(str.c_str())) {}
render::allegro::String::String(const String & other) { *this = other; }
render::allegro::String::String(String && other) { *this = std::move(other); }
render::allegro::String::~String()
{
	if (m_handle != nullptr)
		al_ustr_free(m_handle);
}

render::allegro::String & render::allegro::String::operator=(const String & other)
{
	if (m_handle != nullptr)
		al_ustr_free(m_handle);
	m_handle = al_ustr_dup(other.m_handle);
	return *this;
}
render::allegro::String & render::allegro::String::operator=(String && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}
render::allegro::String & render::allegro::String::operator=(const std::string & str)
{
	return *this = String{ str };
}

bool render::allegro::String::operator==(const String & other) const
{
	return al_ustr_equal(m_handle, other.m_handle);
}

render::allegro::String & render::allegro::String::operator+=(const String & other)
{
	al_ustr_append(m_handle, other.m_handle);
	return *this;
}

unsigned int render::allegro::String::size() const
{
	return al_ustr_length(m_handle);
}
const char * render::allegro::String::c_str() const
{
	return al_cstr(m_handle);
}
