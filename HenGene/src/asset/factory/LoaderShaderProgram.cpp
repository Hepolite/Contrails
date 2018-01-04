
#include "LoaderShaderProgram.h"

#include "render/opengl/OpenGL.h"

#include <pugixml/pugixml.hpp>
#include <plog/Log.h>

namespace
{
	constexpr const char * ATTR_FILE = "file";
	constexpr const char * ATTR_TYPE = "type";

	const std::string TYPE_FRAGMENT = "fragment";
	const std::string TYPE_GEOMETRY = "geometry";
	const std::string TYPE_VERTEX = "vertex";
}

void asset::util::LoaderShaderProgram::load(render::opengl::Program & asset, const io::File & file, const render::uboRegistry & registry) const
{
	asset.setName(file.getPath());

	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	for (auto node = doc.first_child(); node; node = node.next_sibling())
	{
		std::string attrType = node.attribute(ATTR_TYPE).as_string();
		io::File attrFile = node.attribute(ATTR_FILE).as_string();

		render::opengl::ShaderType type = render::opengl::ShaderType::VERTEX;
		if (attrType == TYPE_FRAGMENT)
			type = render::opengl::ShaderType::FRAGMENT;
		else if (attrType == TYPE_GEOMETRY)
			type = render::opengl::ShaderType::GEOMETRY;
		else if (attrType == TYPE_VERTEX)
			type = render::opengl::ShaderType::VERTEX;
		else
			LOG_WARNING << "Unknown shader type " << attrType;

		render::opengl::Shader shader{ type };
		shader.compile(attrFile.exists() ? attrFile.parse() : node.child_value());
		asset.attach(shader);
	}
	asset.link();

	bindPorts(asset, registry);
}

void asset::util::LoaderShaderProgram::bindPorts(render::opengl::Program & asset, const render::uboRegistry & registry) const
{
	for (const auto & binding : registry.getBindings())
	{
		const auto index = glGetUniformBlockIndex(asset.getHandle(), binding.first.c_str());
		if (index == GL_INVALID_INDEX)
			LOG_WARNING << "Failed to bind " << binding.first << " to shader program " << asset.getName();
		else
			glUniformBlockBinding(asset.getHandle(), index, binding.second);
	}
}
