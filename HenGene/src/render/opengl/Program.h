
#pragma once

#include "render/opengl/Enums.h"
#include "render/opengl/Shader.h"

#include <string>

namespace render
{
	namespace opengl
	{
		class Program
		{
		public:
			Program();
			Program(const std::string & name);
			Program(const Program &) = delete;
			Program(Program && other);
			~Program();

			Program & operator=(const Program &) = delete;
			Program & operator=(Program && other);

			bool attach(const Shader & shader) const;
			bool link() const;

			bool bind() const;
			bool unbind() const;

			inline void setName(const std::string & name) { m_name = name; }
			inline auto getName() const { return m_name; }
			inline auto getHandle() const { return m_handle; }

		private:
			std::string m_name = "Unnamed";
			unsigned int m_handle = 0u;
		};
	}
}