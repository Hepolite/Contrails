
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"
#include "world/detail/data/Light.h"
#include "world/World.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(LightRemoverTest)
		{
		public:
			TEST_METHOD(LightRemover_ctor)
			{
				World world;
				LightRemover remover{ world, { 0, 0, 0 } };
			}

			TEST_METHOD(LightRemover_propagateTo)
			{
				const auto expected = {
					std::make_pair(glm::ivec3{ 0, 0, 0 }, glm::uvec4{ 0u, 0u, 0u, 0u }),
					std::make_pair(glm::ivec3{ 0, 0, 1 }, glm::uvec4{ 31u, 0u, 0u, 26u }),
					std::make_pair(glm::ivec3{ 0, 0, 2 }, glm::uvec4{ 31u, 31u, 31u, 6u }),
				};

				World world;
				auto & chunk = world.createChunk({ 0, 0, 0 });
				world.write({ 0, 0, 0 }, BlockData{ 0u, 31u }, ColorData{ { 31u, 31u, 31u } });
				world.write({ 0, 0, 1 }, BlockData{ 0u, 26u }, ColorData{ { 31u, 9u, 15u } });
				world.write({ 0, 0, 2 }, BlockData{ 0u, 6u }, ColorData{ { 31u, 31u, 31u } });
				Index index;
				while (chunk.pollLightPropagation(index));

				LightRemover remover{ world, { 0, 0, 0 } };
				remover.propagateTo(chunk, { 0u, 0u, 0u }, { 31u, 31u, 31u, 31u });
				remover.propagateTo(chunk, { 0u, 0u, 1u }, { 20u, 20u, 20u, 20u });
				remover.propagateTo(chunk, { 0u, 0u, 2u }, { 5u, 5u, 5u, 5u });

				validate(world, { 0, 0, 0 }, expected);

				Assert::IsTrue(chunk.pollLightPropagation(index));
				Assert::IsTrue(chunk.pollLightPropagation(index));
				Assert::IsFalse(chunk.pollLightPropagation(index));
			}
			TEST_METHOD(LightRemover_propagateFrom)
			{
				Assert::Fail();
			}

		private:
			template<typename Data>
			void validate(const World & world, const glm::ivec3 & offset, const Data & expected)
			{
				for (const auto & it : expected)
				{
					const auto block = world.readBlock(it.first + offset);
					const auto color = world.readColor(it.first + offset);

					Assert::AreEqual(it.second.a, block.getLight());
					Assert::AreEqual({ it.second }, color.getColor());
				}
			}
		};
	}
}