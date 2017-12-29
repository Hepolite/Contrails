
#include "uboRegistry.h"

bool render::uboRegistry::has(const std::string & name) const
{
	return m_ubos.find(name) != m_ubos.end();
}
render::opengl::ubo & render::uboRegistry::add(const std::string & name)
{
	if (has(name))
		throw std::invalid_argument("ubo with name " + name + " has already been added");
	return m_ubos.emplace(std::piecewise_construct,
		std::make_tuple(name),
		std::make_tuple(m_ubos.size())
	).first->second;
}
const render::opengl::ubo & render::uboRegistry::get(const std::string & name) const
{
	if (!has(name))
		throw std::invalid_argument("ubo with name " + name + " does not exist");
	return m_ubos.find(name)->second;
}

std::vector<std::pair<std::string, unsigned int>> render::uboRegistry::getBindings() const
{
	std::vector<std::pair<std::string, unsigned int>> bindings{};
	for (const auto & it : m_ubos)
		bindings.emplace_back(it.first, it.second.getPort());
	return bindings;
}
