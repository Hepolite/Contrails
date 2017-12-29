
#pragma once

#include "io/File.h"

#include <functional>
#include <memory>
#include <string>

namespace chaiscript
{
	class ChaiScript;
}

namespace logic
{
	namespace script
	{
		class Script
		{
		public:
			Script();
			Script(const Script &) = delete;
			Script(Script && other);
			~Script();

			Script & operator=(const Script &) = delete;
			Script & operator=(Script && other);

			chaiscript::ChaiScript & getHandle() const;

		private:
			struct Impl;
			std::unique_ptr<Impl> m_impl;
		};
	}
}