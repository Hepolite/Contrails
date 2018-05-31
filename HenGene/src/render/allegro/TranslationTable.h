
#pragma once

#include "render/allegro/String.h"

#include <string>
#include <unordered_map>

namespace render
{
	namespace allegro
	{
		class TranslationTable
		{
		public:
			void set(const std::string & key, const String & string);

			String get(const std::string & key) const;

		private:
			std::unordered_map<std::string, String> m_strings;
		};
	}
}