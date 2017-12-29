
#pragma once

#include "CppUnitTest.h"

#include "logic/event/EventPriority.h"

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<> inline std::wstring ToString(const logic::event::Priority& priority)
	{
		switch (priority)
		{
		case logic::event::Priority::FIRST:		{ RETURN_WIDE_STRING("first"); }
		case logic::event::Priority::EARLY:		{ RETURN_WIDE_STRING("early"); }
		case logic::event::Priority::MIDDLE:	{ RETURN_WIDE_STRING("middle"); }
		case logic::event::Priority::LATE:		{ RETURN_WIDE_STRING("late"); }
		case logic::event::Priority::LAST:		{ RETURN_WIDE_STRING("last"); }
		case logic::event::Priority::MONITOR:	{ RETURN_WIDE_STRING("monitor"); }
		default:								{ RETURN_WIDE_STRING("unknown"); }
		}
	}


}}}