
#pragma once

#include <functional>
#include <memory>

namespace asset
{
	template<typename Type>
	struct Asset
	{
		std::function<std::unique_ptr<Type>()> m_factory = nullptr;

		std::unique_ptr<Type> m_handle = nullptr;
		unsigned int m_references = 0u;
	};
}