
#include "Attribute.h"

#include "render/opengl/OpenGL.h"

bool render::opengl::Attribute::enable(unsigned int stride) const
{
	switch (m_format)
	{
	case DataFormat::BYTE:
	case DataFormat::INT:
	case DataFormat::SHORT:
	case DataFormat::UNSIGNED_BYTE:
	case DataFormat::UNSIGNED_INT:
	case DataFormat::UNSIGNED_SHORT:
		glVertexAttribIPointer(m_index, m_count, static_cast<GLenum>(m_format), stride, (const GLvoid*)m_offset);
		break;
	default:
		glVertexAttribPointer(m_index, m_count, static_cast<GLenum>(m_format), GL_FALSE, stride, (const GLvoid*)m_offset);
	}
	glEnableVertexAttribArray(m_index);
	return !HAS_GL_ERROR;
}
