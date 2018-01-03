
#pragma once

#include "core/Settings.h"

#include <memory>

namespace core { namespace allegro { class Allegro; } }

namespace core
{
	class Engine
	{
	public:
		Engine();
		Engine(const Settings & settings);
		Engine(const Engine &) = delete;
		Engine(Engine &&) = delete;
		~Engine();

		Engine & operator=(const Engine &) = delete;
		Engine & operator=(Engine &&) = delete;

		void start();
		void stop();

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}