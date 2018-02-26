
#pragma once

#include "render/world/detail/meshing/ChunkMeshTask.h"

#include <queue>
#include <mutex>
#include <thread>

namespace render
{
	namespace world
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

			void scheduleTask(ChunkMeshTask && task);
			bool extractTask(ChunkMeshTask & task);

		private:
			void performWorkInThread();

			std::queue<ChunkMeshTask> m_input, m_output;
			std::thread m_worker;
			std::mutex m_mutex;
		};
	}
}