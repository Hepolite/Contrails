
#pragma once

#include "asset/Asset.h"
#include "asset/AssetRef.h"

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace asset
{
	class AssetRegistry
	{
	public:
		AssetRegistry() = default;
		AssetRegistry(const AssetRegistry &) = delete;
		AssetRegistry(AssetRegistry &&) = delete;
		~AssetRegistry() = default;

		AssetRegistry & operator=(const AssetRegistry &) = delete;
		AssetRegistry & operator=(AssetRegistry &&) = delete;

		inline void clear() { m_data.clear(); }

		template<typename Type> Asset<Type> & add(const std::string & name);
		template<typename Type> Ref<Type> get(const std::string & name) const;
		template<typename Type> bool has(const std::string & name) const;

	private:
		struct AssetCollectionBase {};
		template<typename Type> using AssetMap = std::unordered_map<std::string, Asset<Type>>;
		template<typename Type> struct AssetCollection : public AssetCollectionBase { AssetMap<Type> m_assets; };
		using AssetCollectionPtr = std::unique_ptr<AssetCollectionBase>;

		std::unordered_map<std::type_index, AssetCollectionPtr> m_data;
	};
}

template<typename Type>
inline asset::Asset<Type> & asset::AssetRegistry::add(const std::string & name)
{
	auto it = m_data.find(typeid(Type));
	if (it == m_data.end())
		it = m_data.emplace(typeid(Type), std::make_unique<AssetCollection<Type>>()).first;
	return static_cast<AssetCollection<Type>*>(it->second.get())->m_assets[name];
}

template<typename Type>
inline asset::Ref<Type> asset::AssetRegistry::get(const std::string & name) const
{
	const auto it = m_data.find(typeid(Type));
	if (it == m_data.end())
		return nullptr;
	auto & assets = static_cast<AssetCollection<Type>*>(it->second.get())->m_assets;
	const auto it2 = assets.find(name);
	return it2 == assets.end() ? Ref<Type>{ nullptr } : Ref<Type>{ &it2->second };
}

template<typename Type>
inline bool asset::AssetRegistry::has(const std::string & name) const
{
	const auto dataIt = m_data.find(typeid(Type));
	if (dataIt == m_data.end())
		return false;
	const auto& assets = static_cast<AssetCollection<Type>*>(dataIt->second.get())->m_assets;
	return assets.find(name) != assets.end();
}