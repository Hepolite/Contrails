
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <utility>

render::allegro::Sprite::~Sprite()
{
	release();
}
render::allegro::Sprite::Sprite(Sprite && other) noexcept
{
	*this = std::move(other);
}

render::allegro::Sprite & render::allegro::Sprite::operator=(Sprite && other) noexcept
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

void render::allegro::Sprite::release()
{
	if (m_handle != nullptr)
		al_destroy_bitmap(m_handle);
	m_handle = nullptr;
}
void render::allegro::Sprite::create(unsigned int width, unsigned int height)
{
	release();
	m_handle = al_create_bitmap(width, height);
}
void render::allegro::Sprite::load(const io::File & file)
{
	release();
	m_handle = al_load_bitmap(file.getPath().c_str());
}
