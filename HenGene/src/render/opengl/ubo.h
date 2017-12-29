
#pragma once

#include "render/opengl/vbo.h"

#include <unordered_map>

namespace render
{
	namespace opengl
	{
		class ubo
		{
		public:
			ubo() = delete;
			ubo(unsigned int port, BufferUse use = BufferUse::DYNAMIC_DRAW);
			ubo(const ubo &) = delete;
			ubo(ubo && other) noexcept;
			~ubo() = default;

			ubo & operator=(const ubo &) = delete;
			ubo & operator=(ubo && other) noexcept;

			inline auto bind() const { return m_vbo.bind(); }
			inline auto unbind() const { return m_vbo.unbind(); }

			bool build() const;

			template<typename T> bool add(const std::string & name);
			template<typename T> bool get(const std::string & name, T & data) const;
			template<typename T> bool set(const std::string & name, const T & data) const;

			inline auto getPort() const { return m_port; }
			inline auto getHandle() const { return m_vbo.getHandle(); }

		private:
			bool add(const std::string & name, unsigned int size);
			bool get(const std::string & name, unsigned int size, void * data) const;
			bool set(const std::string & name, unsigned int size, const void * data) const;

			vbo m_vbo;

			unsigned int m_port;
			unsigned int m_size;

			std::unordered_map<std::string, unsigned int> m_offsets;
			std::unordered_map<std::string, unsigned int> m_sizes;
		};
	}
}

template<typename T>
inline bool render::opengl::ubo::add(const std::string & name)
{
	return add(name, sizeof(T));
}
template<typename T>
inline bool render::opengl::ubo::get(const std::string & name, T & data) const
{
	return get(name, sizeof(T), &data);
}
template<typename T>
inline bool render::opengl::ubo::set(const std::string & name, const T & data) const
{
	return set(name, sizeof(T), &data);
}