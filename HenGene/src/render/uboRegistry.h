
#pragma once

#include "render/opengl/ubo.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace render
{
	class uboRegistry
	{
	public:
		bool has(const std::string & name) const;
		render::opengl::ubo & add(const std::string & name);
		const render::opengl::ubo & get(const std::string & name) const;

		std::vector<std::pair<std::string, unsigned int>> getBindings() const;

	private:
		std::unordered_map<std::string, opengl::ubo> m_ubos;
	};
}