
#pragma once

#include "util/Physics.h"

#include <functional>

namespace logic
{
	class MainLoop
	{
	public:
		using Function = std::function<void(const Time & t, const Time & dt)>;

		MainLoop() = delete;
		MainLoop(double fps, double ups) : m_fps(fps), m_ups(ups) {}
		MainLoop(const MainLoop &) = default;
		MainLoop(MainLoop &&) = default;
		~MainLoop() = default;

		MainLoop & operator=(const MainLoop &) = default;
		MainLoop & operator=(MainLoop &&) = default;

		void terminate();
		void process(const Function & update, const Function & render);

		inline auto running() const { return m_running; }

	private:
		bool m_running = false;

		double m_fps;
		double m_ups;
	};
}