
#pragma once

#include "world/render/BlockRenderRegistry.h"
#include "world/render/detail/meshing/ChunkMeshTask.h"

#include <chrono>
#include <queue>
#include <mutex>
#include <thread>

namespace world
{
	namespace render
	{
		class ChunkMesher
		{
		public:
			ChunkMesher();
			ChunkMesher(const ChunkMesher &) = delete;
			ChunkMesher(ChunkMesher &&) = delete;
			~ChunkMesher();

			ChunkMesher & operator=(const ChunkMesher &) = delete;
			ChunkMesher & operator=(ChunkMesher &&) = delete;

			inline void inject(const BlockRenderRegistry & renders) { m_renders = &renders; }

			void scheduleTask(ChunkMeshTask && task);
			bool extractTask(ChunkMeshTask & task);

		private:
			void pushTask(ChunkMeshTask && task, std::queue<ChunkMeshTask> & queue);
			bool popTask(ChunkMeshTask & task, std::queue<ChunkMeshTask> & queue);

			void startMeasuring();
			void endMeasuring();
			void performWorkInThread();
			void performMeshTask(ChunkMeshTask & task);

			const BlockRenderRegistry * m_renders;

			std::queue<ChunkMeshTask> m_input, m_output;
			std::thread m_worker;
			std::mutex m_mutex;

			bool m_working = true;

			std::chrono::steady_clock::time_point m_begin;
			unsigned int m_tasksPerformed;
		};
	}
}