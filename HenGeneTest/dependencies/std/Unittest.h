
#pragma once

#include "CppUnitTest.h"

#include <typeindex>

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<> inline std::wstring ToString(const std::type_index& t)
	{
		RETURN_WIDE_STRING(t.name());
	}

}}}