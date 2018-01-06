
#include "CppUnitTest.h"

#include "logic/ecs/SystemRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace ecs
	{
		bool processedA = false;
		bool processedB = false;

		class SystemMockA : public System<int, double>
		{
		public:
			virtual void process(const Time & t, const Time & dt) const override final { processedA = true; }
		};
		class SystemMockB : public System<float>
		{
		public:
			virtual void process(const Time & t, const Time & dt) const override final { processedB = true; }
		};

		TEST_CLASS(SystemRegistryTest)
		{
		public:
			TEST_METHOD(SystemRegistry_add)
			{
				SystemRegistry registry;
				registry.add<SystemMockA, SystemMockB>();
				registry.process(0.0_s, 0.05_s);

				Assert::IsTrue(processedA);
				Assert::IsTrue(processedB);
			}
		};
	}
}