
#pragma once

#include "world/render/BlockRenderRegistry.h"
#include "world/render/detail/meshing/ChunkMeshTask.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <mutex>
#include <thread>
#include <vector>
#include <unordered_map>

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

			void schedule(ChunkMeshTask && task);
			bool extract(ChunkMeshTask & task);
			void finish();

		private:
			void work();
			bool performTask(ChunkMeshTask & task);
			void completeTask(ChunkMeshTask && task);

			const BlockRenderRegistry * m_renders;

			std::vector<std::thread> m_workers;
			std::unordered_map<glm::ivec3, ChunkMeshTask> m_input, m_output;
			std::mutex m_mutex;

			unsigned int m_tasks = 0u;
			bool m_working = true;
		};
	}
}