
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"
#include "world/detail/data/Light.h"
#include "world/World.h"

#include <glm/Unittest.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(LightTest)
		{
		public:
			TEST_METHOD(LightPropagator_ctor)
			{
				World world;
				LightPropagator worker{ world, { 0, 0, 0} };
			}

			TEST_METHOD(LightPropagator_propagateTo)
			{
				World world;
				auto & chunk = world.createChunk({ 0, 0, 0 });
				LightPropagator propagator{ world, glm::ivec3{ 0, 0, 0 } };

				propagator.propagateTo(chunk, { 3, 6, 5 }, { 3u, 9u, 9u, 31u });

				const auto block = chunk.readBlock(toIndex(glm::uvec3{ 3u, 6u, 5u }));
				const auto color = chunk.readColor(toIndex(glm::uvec3{ 3u, 6u, 5u }));
				Assert::AreEqual(30u, block.getLight());
				Assert::AreEqual({ 2u, 8u, 8u }, color.getColor());
			}
			TEST_METHOD(LightPropagator_propagateFrom)
			{
				const auto data = {
					std::make_pair(glm::ivec3{ 6, 5, 5 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
					std::make_pair(glm::ivec3{ 4, 5, 5 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
					std::make_pair(glm::ivec3{ 5, 6, 5 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
					std::make_pair(glm::ivec3{ 5, 4, 5 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
					std::make_pair(glm::ivec3{ 5, 5, 6 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
					std::make_pair(glm::ivec3{ 5, 5, 4 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
				};

				World world;
				auto & chunk = world.createChunk({ 0, 0, 0 });
				LightPropagator propagator{ world, glm::ivec3{ 0, 0, 0 } };

				propagator.propagateFrom(chunk, { 5, 5, 5 }, { 3u, 9u, 1u, 31u });

				validate(world, { 0, 0, 0 }, data);
			}

			TEST_METHOD(LightPropagator_propagateInCenter)
			{
				World world = getWorld({ 15, 15, 15 });
				LightPropagator{ world, { 0, 0, 0 } }.propagate();

				validate(world, { 15, 15, 15 }, m_data);
			}
			TEST_METHOD(LightPropagator_propagateOnEdge)
			{
				World world = getWorld({ 0, 15, 15 });
				world.propagateLight();

				validate(world, { 0, 15, 15 }, m_data);
			}
			TEST_METHOD(LightPropagator_propagateOnCorner)
			{
				World world = getWorld({ 0, 0, 0 });
				world.propagateLight();

				validate(world, { 0, 0, 0 }, m_data);
			}

		private:
			World getWorld(const glm::ivec3 & offset)
			{
				const auto pos = m_data.begin()->first;
				const auto light = m_data.begin()->second;

				World world;
				world.write(pos + offset, BlockData { 1u, light.a }, ColorData{ light });
				return world;
			}

			template<typename Data>
			void validate(const World & world, const glm::ivec3 & offset, const Data & data)
			{
				for (const auto & it : data)
				{
					const auto block = world.readBlock(it.first + offset);
					const auto color = world.readColor(it.first + offset);

					Assert::AreEqual(it.second.a, block.getLight());
					Assert::AreEqual({ it.second }, color.getColor());
				}
			}

			const std::vector<std::pair<glm::ivec3, glm::uvec4>> m_data = {
				std::make_pair(glm::ivec3{ 0, 0, 0 }, glm::uvec4{ 3u, 9u, 1u, 31u }),

				std::make_pair(glm::ivec3{ 1, 0, 0 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
				std::make_pair(glm::ivec3{ -1, 0, 0 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
				std::make_pair(glm::ivec3{ 0, 1, 0 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
				std::make_pair(glm::ivec3{ 0, -1, 0 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
				std::make_pair(glm::ivec3{ 0, 0, 1 }, glm::uvec4{ 2u, 8u, 0u, 30u }),
				std::make_pair(glm::ivec3{ 0, 0, -1 }, glm::uvec4{ 2u, 8u, 0u, 30u }),

				std::make_pair(glm::ivec3{ 2, 0, 0 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 1, 1, 0 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ -2, 0, 0 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ -1, -1, 0 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 0, 2, 0 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 0, 1, 1 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 0, -2, 0 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 0, -1, -1 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 0, 0, 2 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 1, 0, 1 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ 0, 0, -2 }, glm::uvec4{ 1u, 7u, 0u, 29u }),
				std::make_pair(glm::ivec3{ -1, 0, -1 }, glm::uvec4{ 1u, 7u, 0u, 29u }),

				std::make_pair(glm::ivec3{ 3, 0, 0 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 2, 1, 0 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 1, 1, 1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ -3, 0, 0 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ -2, -1, 0 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ -1, -1, -1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 0, 3, 0 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 0, 2, 1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ -1, 1, 1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 0, -3, 0 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 0, -2, -1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 1, -1, -1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 0, 0, 3 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 1, 0, 2 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 1, -1, 1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ 0, 0, -3 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ -1, 0, -2 }, glm::uvec4{ 0u, 6u, 0u, 28u }),
				std::make_pair(glm::ivec3{ -1, 1, -1 }, glm::uvec4{ 0u, 6u, 0u, 28u }),

				std::make_pair(glm::ivec3{ -2, -2, -2 }, glm::uvec4{ 0u, 3u, 0u, 25u }),
				std::make_pair(glm::ivec3{ 3, -3, -2 }, glm::uvec4{ 0u, 1u, 0u, 23u }),
				std::make_pair(glm::ivec3{ 5, -4, -3 }, glm::uvec4{ 0u, 0u, 0u, 19u }),
			};
		};
	}
}