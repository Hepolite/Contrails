
#include "MainLoop.h"

#include <allegro5/allegro5.h>
#include <plog/Log.h>

void logic::MainLoop::terminate()
{
	m_running = false;
}
void logic::MainLoop::process(const Function & update, const Function & render)
{
	if (update == nullptr || render == nullptr)
	{
		LOG_FATAL << "Main loop has no logic or rendering specified";
		return;
	}
	if (m_ups <= 0.0 || m_fps <= 0.0)
	{
		LOG_FATAL << "Main loop cannot run with 0 cps and/or 0 fps";
		return;
	}

	m_running = true;

	const Time deltaTime = 1.0_s / m_ups;
	Time time = 0.0_s;
	Time accumulatedTime{};
	Time currentTime{ al_current_time() };

	while (m_running)
	{
		const Time newTime{ al_current_time() };
		accumulatedTime += newTime - currentTime;
		currentTime = newTime;

		while (accumulatedTime >= deltaTime)
		{
			update(time, deltaTime);
			accumulatedTime -= deltaTime;
			time += deltaTime;
		}
		render(time, accumulatedTime);
	}
}
