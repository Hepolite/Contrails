
#include "ChunkMesher.h"

#include "world/render/detail/meshing/NaiveGreedyMesher.h"

#include <chrono>
#include <plog/Log.h>

world::render::ChunkMesher::ChunkMesher()
{
	for (unsigned int i = 0u; i < 3u; ++i)
		m_workers.emplace_back([this]() {work(); });
}
world::render::ChunkMesher::~ChunkMesher()
{
	m_working = false;
	for (auto & worker : m_workers)
		worker.join();
}

// ...

void world::render::ChunkMesher::schedule(ChunkMeshTask && task)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	m_input[task.m_cpos] = std::move(task);
}
bool world::render::ChunkMesher::extract(ChunkMeshTask & task)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	if (m_output.empty())
		return false;
	std::swap(m_output.begin()->second, task);
	m_output.erase(task.m_cpos);
	return true;
}

void world::render::ChunkMesher::finish()
{
	while (m_tasks != 0u || !m_input.empty())
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void world::render::ChunkMesher::work()
{
	ChunkMeshTask task;
	while (m_working)
	{
		std::chrono::steady_clock::time_point m_begin = std::chrono::steady_clock::now();
		unsigned int m_tasksPerformed = 0u;

		while (performTask(task))
		{
			completeTask(std::move(task));
			m_tasksPerformed++;
		}

		if (m_tasksPerformed != 0u)
		{
			const auto delta = std::chrono::steady_clock::now() - m_begin;
			const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
			const auto millisecondsAvg = milliseconds / m_tasksPerformed;

			LOG_INFO << "Meshed " << m_tasksPerformed << " chunks in "
				<< std::to_string(milliseconds) << " ms ("
				<< std::to_string(millisecondsAvg) << " ms avg)";
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
bool world::render::ChunkMesher::performTask(ChunkMeshTask & task)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	if (m_input.empty())
		return false;
	m_tasks++;
	std::swap(m_input.begin()->second, task);
	m_input.erase(task.m_cpos);
	return true;
}
void world::render::ChunkMesher::completeTask(ChunkMeshTask && task)
{
	if (m_renders != nullptr && task.m_mesh != nullptr)
	{
		NaiveGreedyMesher mesher;
		mesher.inject(*m_renders);
		mesher.inject(task.m_data);
		mesher.inject(*task.m_mesh);
		mesher.build();
	}

	{
		std::lock_guard<std::mutex> guard{ m_mutex };
		m_output[task.m_cpos] = std::move(task);
		m_tasks--;
	}
}
