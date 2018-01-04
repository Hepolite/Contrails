
#pragma once

#include "render/opengl/Enums.h"

namespace render
{
	namespace opengl
	{
		class Attribute
		{
		public:
			Attribute() = default;
			/*
			Specifies an attribute of the vertex in a shader
			@param index The index of the attribute in a shader
			@param count The number of of values associated with the attribute (3 for vec3, 1 for float, etc)
			@param format The format of the internal data (BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, and FLOAT are accepted)
			@param offset The offset of the data given in bytes
			*/
			Attribute(unsigned int index, DataFormat format, int count, unsigned int offset)
				: m_index(index), m_format(format), m_count(count), m_offset(offset)
			{}
			~Attribute() = default;

			/*
			Specifies that the attribute should be enabled in a shader
			@param stride The size of the vertex this attribute should apply to
			*/
			bool enable(unsigned int stride) const;

		private:
			unsigned int m_index = 0;
			unsigned int m_offset = 0;
			DataFormat m_format = DataFormat::FLOAT;
			int m_count = 0;
		};
	}
}