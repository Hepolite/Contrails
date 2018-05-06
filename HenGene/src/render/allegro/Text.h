
#pragma once

#include "render/allegro/String.h"
#include "render/allegro/TextComponent.h"

#include <vector>

namespace render
{
	namespace allegro
	{
		class Text
		{
		private:
			std::vector<std::unique_ptr<ComponentBase>> m_strings;
		};
	}
}