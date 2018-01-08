
#pragma once

namespace render
{
	enum class RenderPass
	{
		BACKGROUND,		// Rendered before everything, depth writing is off
		SOLID,			// Rendered with full opacity, alpha = 1
		CUTOFF,			// Rendered with either full opacity or not at all, alpha = 1 or alpha = 0
		TRANSPARENT,	// Rendered with any alpha value

		INVISIBLE,		// Not rendered at all
	};
}