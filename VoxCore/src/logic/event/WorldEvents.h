
#pragma once

#include <string>

namespace logic
{
	namespace event
	{
		struct WorldCreate
		{
			std::string m_name;
		};
		struct WorldDestroy
		{
			std::string m_name;
		};

		struct WorldRename
		{
			std::string m_oldName;
			std::string m_newName;
		};
	}
}