
#include "CppUnitTest.h"

#include "world/data/Light.h"

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

			TEST_METHOD(LightPropagator_propagateInCenter)
			{
				const auto data = {
					std::make_pair(2u, glm::ivec3{ 5, 5, 5 }),
					std::make_pair(1u, glm::ivec3{ 4, 5, 5 }),
					std::make_pair(1u, glm::ivec3{ 6, 5, 5 }),
					std::make_pair(1u, glm::ivec3{ 5, 4, 5 }),
					std::make_pair(1u, glm::ivec3{ 5, 6, 5 }),
					std::make_pair(1u, glm::ivec3{ 5, 5, 4 }),
					std::make_pair(1u, glm::ivec3{ 5, 5, 6 }),
					std::make_pair(0u, glm::ivec3{ 3, 5, 5 }),
					std::make_pair(0u, glm::ivec3{ 6, 6, 5 }),
					std::make_pair(0u, glm::ivec3{ 5, 4, 6 }),
				};

				World world;
				world.write({ 5, 5, 5 }, BlockData{ 1u, 2u }, ColorData{ { 0u, 0u, 0u } });

				LightPropagator worker{ world, { 0, 0, 0 } };
				worker.propagate();

				for (const auto & it : data)
				{
					BlockData block;
					ColorData color;
					world.read(it.second, block, color);

					Assert::AreEqual(it.first, block.getLight());
				}
			}
		};
	}
}