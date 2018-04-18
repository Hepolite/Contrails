
#pragma once

#include "asset/AssetRegistry.h"
#include "core/scene/Scene.h"

namespace editor
{
	class Editor
	{
	public:
		Editor();
		Editor(const Editor &) = delete;
		Editor(Editor &&) = delete;
		~Editor();

		Editor & operator=(const Editor &) = delete;
		Editor & operator=(Editor &&) = delete;

		void inject(const asset::AssetRegistry & assets);
		void inject(core::scene::Scene & scene);

		virtual void process();

	private:

	};
}