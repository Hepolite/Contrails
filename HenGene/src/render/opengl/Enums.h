
#pragma once

namespace render
{
	namespace opengl
	{
		/* Types of buffer objects; used for VBOs and VAOs, etc */
		enum class BufferType
		{
			ARRAY_BUFFER			= 0x8892,	// Vertex attributes
			ELEMENT_ARRAY_BUFFER	= 0x8893,	// Vertex array indices
			UNIFORM_BUFFER			= 0x8A11,	// Uniform block storage
		};

		/* Types of buffer object uses; this is merely a hint for how the data will be used */
		enum class BufferUse
		{
			DYNAMIC_DRAW	= 0x88E8,	// Data will be modified repeatedly and used many times
			STATIC_DRAW		= 0x88E4,	// Data will be modified once and used many times
			STREAM_DRAW		= 0x88E0,	// Data will be modified once and used at most a few times
		};

		/* Types of data format used by OpenGL */
		enum class DataFormat
		{
			BYTE			= 0x1400,
			UNSIGNED_BYTE	= 0x1401,
			SHORT			= 0x1402,
			UNSIGNED_SHORT	= 0x1403,
			INT				= 0x1404,
			UNSIGNED_INT	= 0x1405,
			FLOAT			= 0x1406,
			DOUBLE			= 0x140A,
		};

		/* Types of methods for rendering geometry */
		enum class RenderMode
		{
			POINTS			= 0x0000,
			LINES			= 0x0001,
			LINE_LOOP		= 0x0002,
			LINE_STRIP		= 0x0003,
			TRIANGLES		= 0x0004,
			TRIANGLE_STRIP	= 0x0005,
			TRIANGLE_FAN	= 0x0006,
			QUADS			= 0x0007,
			QUAD_STRIP		= 0x0008,
			POLYGON			= 0x0009,
		};

		/* Types of shaders */
		enum class ShaderType
		{
			FRAGMENT	= 0x8B30,
			GEOMETRY	= 0x8DD9,
			VERTEX		= 0x8B31,
		};

		/* Various types of textures */
		enum class TextureType
		{
			TEXTURE_2D			= 0x0DE1,
			TEXTURE_2D_ARRAY	= 0x8C1A,
		};
	}
}