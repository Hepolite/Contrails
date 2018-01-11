
#pragma once

#include "asset/AssetRegistry.h"
#include "io/File.h"
#include "io/Folder.h"
#include "util/StringGeneric.h"

namespace asset
{
	namespace util
	{
		// Builder must implement 'void build(Type & asset, const Args & ...args)'
		template<typename Type, class Builder, typename ...Args> void setupBuilderFactory(
			AssetRegistry & registry,
			const std::string& name,
			const Args & ...args
		);

		// Loader must implement 'void load(Type & asset, const io::File & file, const Args & ...args)'
		template<typename Type, class Loader, typename ...Args> void setupLoaderFactory(
			AssetRegistry & registry,
			const io::Folder & root,
			const std::string & extension,
			const std::string & trimmed,
			const Args & ...args
		);
	}
}

template<typename Type, class Builder, typename ...Args>
void asset::util::setupBuilderFactory(
	AssetRegistry & registry,
	const std::string & name,
	const Args & ...args)
{
	registry.add<Type>(name).m_factory = [&args...]()
	{
		auto asset = std::make_unique<Type>();
		Builder{}.build(*asset, args...);
		return asset;
	};
}
template<typename Type, class Loader, typename ...Args>
void asset::util::setupLoaderFactory(
	AssetRegistry & registry,
	const io::Folder & root,
	const std::string & extension,
	const std::string & trimmed,
	const Args & ...args
){
	for (const auto file : root.getFiles())
	{
		if (file.getExtension() != extension)
			continue;

		const auto name = string::replace(string::replace(file.getPath(), "." + extension, ""), trimmed, "");
		registry.add<Type>(name).m_factory = [file, &args...]()
		{
			auto asset = std::make_unique<Type>();
			Loader{}.load(*asset, file, args...);
			return asset;
		};
	}
	for (const auto folder : root.getFolders())
		setupLoaderFactory<Type, Loader, Args...>(registry, folder, extension, trimmed, args...);
}