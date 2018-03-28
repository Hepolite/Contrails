
#include "ChunkMesher.h"

#include "render/world/detail/meshing/NaiveGreedyMesher.h"

#include <chrono>
#include <plog/Log.h>

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
	bool valid = popTask(task, m_output);
	if (valid)
	{
		// TODO: Seriously, this is NOT ChunkMesher's task - move this elsewhere!
		for (unsigned int i = 0u; i < RENDER_PASS_COUNT; ++i)
		{
			auto & mesh = (*task.m_mesh)[i];
			mesh.addAttribute({ 0u, opengl::DataFormat::FLOAT, 3u, 0u });
			mesh.addAttribute({ 1u, opengl::DataFormat::FLOAT, 3u, 12u });
			mesh.addAttribute({ 2u, opengl::DataFormat::FLOAT, 3u, 24u });
			mesh.addAttribute({ 3u, opengl::DataFormat::FLOAT, 4u, 36u });
			mesh.build();
		}
	}
	return valid;
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

void render::world::ChunkMesher::startMeasuring()
{
	m_begin = std::chrono::steady_clock::now();
	m_tasksPerformed = 0u;
}
void render::world::ChunkMesher::endMeasuring()
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

void render::world::ChunkMesher::performWorkInThread()
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
void render::world::ChunkMesher::performMeshTask(ChunkMeshTask & task)
{
	NaiveGreedyMesher mesher;
	mesher.inject(*m_renders);
	mesher.inject(task.m_data);
	mesher.inject(*task.m_mesh);
	mesher.build();
	pushTask(std::move(task), m_output);

	m_tasksPerformed++;
}

