
#include "CppUnitTest.h"

#include "asset/AssetUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
	class BuilderInt
	{
	public:
		void build(int & asset, const bool & a, const bool & b) const
		{
			asset = 42;
		}
	};

	class LoaderInt
	{
	public:
		void load(int & asset, const io::File & file) const
		{
			asset = 1337;
		}
	};
}

namespace asset
{
	TEST_CLASS(AssetUtilTest)
	{
	public:
		TEST_METHOD(AssetUtil_setupLoaderFactory)
		{
			AssetRegistry registry;

			util::setupBuilderFactory<int, BuilderInt>(registry, "mySpecialInt", true, false);
			util::setupLoaderFactory<int, LoaderInt>(registry, "data/assets", "xml", "data/");
		}
	};
}