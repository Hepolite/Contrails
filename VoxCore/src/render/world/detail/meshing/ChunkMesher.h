
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