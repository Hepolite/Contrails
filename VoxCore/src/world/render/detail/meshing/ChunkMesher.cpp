
#include "ChunkMesher.h"

#include "render/opengl/Enums.h"
#include "world/render/detail/meshing/NaiveGreedyMesher.h"

#include <chrono>
#include <plog/Log.h>

world::render::ChunkMesher::ChunkMesher()
{
	m_worker = std::thread{ [this]() { performWorkInThread(); } };
}
world::render::ChunkMesher::~ChunkMesher()
{
	m_working = false;
	m_worker.join();
}

void world::render::ChunkMesher::scheduleTask(ChunkMeshTask && task)
{
	pushTask(std::move(task), m_input);
}
bool world::render::ChunkMesher::extractTask(ChunkMeshTask & task)
{
	return popTask(task, m_output);
}

void world::render::ChunkMesher::pushTask(ChunkMeshTask && task, std::queue<ChunkMeshTask> & queue)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	queue.emplace(std::move(task));
}
bool world::render::ChunkMesher::popTask(ChunkMeshTask & task, std::queue<ChunkMeshTask> & queue)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	if (queue.empty())
		return false;
	std::swap(task, queue.front());
	queue.pop();
	return true;
}

void world::render::ChunkMesher::startMeasuring()
{
	m_begin = std::chrono::steady_clock::now();
	m_tasksPerformed = 0u;
}
void world::render::ChunkMesher::endMeasuring()
{
	if (m_tasksPerformed == 0u)
		return;

	const auto delta = std::chrono::steady_clock::now() - m_begin;
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
	const auto millisecondsAvg = milliseconds / m_tasksPerformed;

	LOG_INFO	<< "Meshed " << m_tasksPerformed << " chunks in "
				<< std::to_string(milliseconds) << " ms ("
				<< std::to_string(millisecondsAvg) << " ms avg)";
}

void world::render::ChunkMesher::performWorkInThread()
{
	ChunkMeshTask task;
	while (m_working)
	{
		startMeasuring();
		while (popTask(task, m_input))
			performMeshTask(task);
		endMeasuring();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void world::render::ChunkMesher::performMeshTask(ChunkMeshTask & task)
{
	NaiveGreedyMesher mesher;
	mesher.inject(*m_renders);
	mesher.inject(task.m_data);
	mesher.inject(*task.m_mesh);
	mesher.build();
	pushTask(std::move(task), m_output);

	m_tasksPerformed++;
}

