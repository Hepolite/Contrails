
#include "ubo.h"

#include "render/opengl/opengl.h"

#include <plog/Log.h>
#include <utility>

render::opengl::ubo::ubo(unsigned int port, BufferUse use)
	: m_port(port), m_size(0u), m_vbo(BufferType::UNIFORM_BUFFER, use)
{}
render::opengl::ubo::ubo(ubo && other) noexcept
{
	*this = std::move(other);
}

render::opengl::ubo & render::opengl::ubo::operator=(ubo && other) noexcept
{
	if (this != &other)
	{
		std::swap(m_vbo, other.m_vbo);
		std::swap(m_port, other.m_port);
		std::swap(m_size, other.m_size);
		std::swap(m_offsets, other.m_offsets);
		std::swap(m_sizes, other.m_sizes);
	}
	return *this;
}

bool render::opengl::ubo::build() const
{
	if (!m_vbo.reserve(m_size))
		return false;
	glBindBufferBase(GL_UNIFORM_BUFFER, m_port, getHandle());
	return !HAS_GL_ERROR;
}

bool render::opengl::ubo::add(const std::string & name, unsigned int size)
{
	if (m_offsets.find(name) != m_offsets.end())
		return false;
	m_offsets[name] = m_size;
	m_sizes[name] = size;
	m_size += size;
	return true;
}
bool render::opengl::ubo::get(const std::string & name, unsigned int size, void * data) const
{
	const auto itOffset = m_offsets.find(name);
	const auto itSize = m_sizes.find(name);
	if (itOffset == m_offsets.end() || itSize == m_sizes.end() || itSize->second != size)
	{
		LOG_WARNING << name << " does not exist or wrong input size " << size << " (expected " << itSize->second << ")";
		return false;
	}
	return m_vbo.retrieve(size, data, itOffset->second);
}
bool render::opengl::ubo::set(const std::string & name, unsigned int size, const void * data) const
{
	const auto itOffset = m_offsets.find(name);
	const auto itSize = m_sizes.find(name);
	if (itOffset == m_offsets.end() || itSize == m_sizes.end() || itSize->second != size)
	{
		LOG_WARNING << name << " does not exist or wrong input size " << size << " (expected " << itSize->second << ")";
		return false;
	}
	return m_vbo.buffer(size, data, itOffset->second);
}
