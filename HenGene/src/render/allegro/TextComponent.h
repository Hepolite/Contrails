
#pragma once

#include "util/Physics.h"

namespace render
{
	namespace allegro
	{
		class ComponentBase
		{
		public:
			virtual void process(const Time & t, const Time & dt) = 0;
		};

		class ComponentEffectBase {};	// Any sort of effect operating on child components
		class ComponentEffectTalk {};	// Text appears in sequence, one by one

		class ComponentText {};			// Plain string
		class ComponentTranslation {};	// Translates a key->value to text
	}
}