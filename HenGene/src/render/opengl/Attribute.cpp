
#include "Attribute.h"

#include "render/opengl/OpenGL.h"

bool render::opengl::Attribute::enable(unsigned int stride) const
{
	glVertexAttribPointer(m_index, m_count, static_cast<GLenum>(m_format), GL_FALSE, stride, (const GLvoid*)m_offset);
	glEnableVertexAttribArray(m_index);
	return !HAS_GL_ERROR;
}
