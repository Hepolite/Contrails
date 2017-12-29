
#include "Shader.h"

#include "render/opengl/OpenGL.h"

#include <plog/Log.h>
#include <utility>

render::opengl::Shader::Shader(ShaderType type)
{
	m_handle = glCreateShader(static_cast<GLuint>(type));
}
render::opengl::Shader::~Shader()
{
	if (m_handle != 0u)
		glDeleteShader(m_handle);
}
render::opengl::Shader::Shader(Shader && other)
{
	*this = std::move(other);
}
render::opengl::Shader & render::opengl::Shader::operator=(Shader && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

bool render::opengl::Shader::compile(const std::string & code)
{
	if (m_handle == 0 || code.empty())
		return false;

	const char* data = code.c_str();
	glShaderSource(m_handle, 1, &data, nullptr);
	glCompileShader(m_handle);

	GLint result;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &result);
	GLint length;
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	std::string message{ "", static_cast<unsigned int>(length) };
	glGetShaderInfoLog(m_handle, length, nullptr, &message[0]);

	if (!result)
	{
		LOG_WARNING << message;
		return false;
	}
	return !HAS_GL_ERROR;
}
