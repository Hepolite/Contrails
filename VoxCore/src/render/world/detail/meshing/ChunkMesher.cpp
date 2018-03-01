
#include "ChunkMesher.h"

#include "render/world/detail/meshing/NaiveGreedyMesher.h"

#include <chrono>

render::world::ChunkMesher::ChunkMesher()
{
	m_worker = std::thread{ [this]() { performWorkInThread(); } };
}
render::world::ChunkMesher::~ChunkMesher()
{
	m_working = false;
	m_worker.join();
}

void render::world::ChunkMesher::scheduleTask(ChunkMeshTask && task)
{
	pushTask(std::move(task), m_input);
}
bool render::world::ChunkMesher::extractTask(ChunkMeshTask & task)
{
	return popTask(task, m_output);
}

void render::world::ChunkMesher::pushTask(ChunkMeshTask && task, std::queue<ChunkMeshTask> & queue)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	queue.emplace(std::move(task));
}
bool render::world::ChunkMesher::popTask(ChunkMeshTask & task, std::queue<ChunkMeshTask> & queue)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	if (queue.empty())
		return false;
	std::swap(task, queue.front());
	queue.pop();
	return true;
}

void render::world::ChunkMesher::performWorkInThread()
{
	while (m_working)
	{
		ChunkMeshTask task;
		while (popTask(task, m_input))
		{
			NaiveGreedyMesher mesher;
			mesher.inject(*m_renders);
			mesher.inject(task.m_data);
			mesher.inject(*task.m_mesh);
			mesher.build();
			pushTask(std::move(task), m_output);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

