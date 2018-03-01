
#pragma once

#include "render/world/BlockRenderRegistry.h"
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

			inline void inject(const BlockRenderRegistry & renders) { m_renders = &renders; }

			void scheduleTask(ChunkMeshTask && task);
			bool extractTask(ChunkMeshTask & task);

		private:
			void performWorkInThread();
			void pushTask(ChunkMeshTask && task, std::queue<ChunkMeshTask> & queue);
			bool popTask(ChunkMeshTask & task, std::queue<ChunkMeshTask> & queue);

			const BlockRenderRegistry * m_renders;

			std::queue<ChunkMeshTask> m_input, m_output;
			std::thread m_worker;
			std::mutex m_mutex;

			bool m_working = true;
		};
	}
}