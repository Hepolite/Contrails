
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <utility>

render::allegro::SpriteFrame::SpriteFrame(ALLEGRO_BITMAP * parent, const glm::ivec2 & pos, const glm::ivec2 & size) noexcept
	: m_pos(pos), m_size(size)
{
	if (parent != nullptr)
		m_handle = al_create_sub_bitmap(parent, m_pos.x, m_pos.y, m_size.x, m_size.y);
}
render::allegro::SpriteFrame::~SpriteFrame() noexcept
{
	if (m_handle != nullptr)
		al_destroy_bitmap(m_handle);
}
render::allegro::SpriteFrame::SpriteFrame(SpriteFrame && other) noexcept
{
	*this = std::move(other);
}

render::allegro::SpriteFrame & render::allegro::SpriteFrame::operator=(SpriteFrame && other) noexcept
{
	if (this != &other)
	{
		std::swap(m_handle, other.m_handle);
		m_tint = other.m_tint;
		m_pos = other.m_pos;
		m_size = other.m_size;
		m_flags = other.m_flags;
	}
	return *this;
}

void render::allegro::SpriteFrame::flip(bool horizontal, bool vertical)
{
	m_flags = (horizontal ? ALLEGRO_FLIP_HORIZONTAL : 0) | (vertical ? ALLEGRO_FLIP_VERTICAL : 0);
}
void render::allegro::SpriteFrame::tint(const glm::vec4 & tint)
{
	m_tint = { tint.r * tint.a, tint.g * tint.a, tint.b * tint.a, tint.a };
}

void render::allegro::SpriteFrame::draw(const glm::vec2 & pos, float angle) const
{
	if (m_handle == nullptr)
		return;
	if (angle == 0.0f)
		al_draw_tinted_bitmap(m_handle, m_tint, pos.x, pos.y, m_flags);
	else
	{
		const auto offset = 0.5f * glm::vec2{ m_size };
		al_draw_tinted_rotated_bitmap(m_handle, m_tint, offset.x, offset.y, pos.x + offset.x, pos.y + offset.y, angle, m_flags);
	}
}
void render::allegro::SpriteFrame::draw(const glm::vec2 & pos, const glm::vec2 & size, float angle) const
{
}

// ...

render::allegro::Sprite::~Sprite()
{
	m_frames.clear();
	if (m_handle != nullptr)
		al_destroy_bitmap(m_handle);
}
render::allegro::Sprite::Sprite(Sprite && other) noexcept
{
	*this = std::move(other);
}

render::allegro::Sprite & render::allegro::Sprite::operator=(Sprite && other) noexcept
{
	if (this != &other)
	{
		std::swap(m_handle, other.m_handle);
		m_frames = std::move(other.m_frames);
	}
	return *this;
}

bool render::allegro::Sprite::create(unsigned int width, unsigned int height)
{
	if (m_handle != nullptr)
		return false;
	m_handle = al_create_bitmap(width, height);
	return m_handle != nullptr;
}
bool render::allegro::Sprite::load(const io::File & file)
{
	if (m_handle != nullptr)
		return false;
	m_handle = al_load_bitmap(file.getPath().c_str());
	return m_handle != nullptr;
}

bool render::allegro::Sprite::has(const std::string & name) const
{
	return m_frames.find(name) != m_frames.end();
}
bool render::allegro::Sprite::add(const std::string & name, SpriteFrame && frame)
{
	if (has(name))
		return false;
	m_frames.emplace(name, std::move(frame));
	return true;
}
const render::allegro::SpriteFrame & render::allegro::Sprite::get(const std::string & name) const
{
	const auto it = m_frames.find(name);
	if (it == m_frames.end())
		throw std::invalid_argument("Frame " + name + " does not exist");
	return it->second;
}
