
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