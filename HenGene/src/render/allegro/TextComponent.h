
#pragma once

#include "util/Physics.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace render
{
	namespace allegro
	{
		class ComponentBase
		{
		public:
			virtual void process(const Time & dt) = 0;
			virtual glm::vec2 render(const glm::vec2 & pos, const glm::vec4 & bbox) const = 0;
		};

		class ComponentEffectBase {};	// Any sort of effect operating on child components
		class ComponentEffectTalk {};	// Text appears in sequence, one by one

		class ComponentText {};			// Plain string
		class ComponentTranslation {};	// Translates a key->value to text
	}
}