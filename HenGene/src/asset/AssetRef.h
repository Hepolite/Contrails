
#pragma once

#include "asset/Asset.h"

#include <utility>

namespace asset
{
	template<typename Type>
	class Ref
	{
	public:
		Ref() = default;
		Ref(Asset<Type> * handle);
		Ref(const Ref & other);
		Ref(Ref && other);
		~Ref();

		Ref & operator=(const Ref & other);
		Ref & operator=(Ref && other);

		bool operator==(const Ref & other) const;
		bool operator!=(const Ref & other) const;
		bool operator==(const std::nullptr_t &) const;
		bool operator!=(const std::nullptr_t &) const;

		Type & operator*() const;
		Type * operator->() const;

	private:
		void increment();
		void decrement();

		Asset<Type> * m_handle = nullptr;
	};
}

template<typename Type>
inline asset::Ref<Type>::Ref(Asset<Type> * handle)
	: m_handle(handle)
{
	increment();
}
template<typename Type>
inline asset::Ref<Type>::Ref(const Ref & other)
{
	*this = other;
}
template<typename Type>
inline asset::Ref<Type>::Ref(Ref && other)
{
	*this = std::move(other);
}
template<typename Type>
inline asset::Ref<Type>::~Ref()
{
	decrement();
}

template<typename Type>
inline asset::Ref<Type> & asset::Ref<Type>::operator=(const Ref & other)
{
	decrement();
	m_handle = other.m_handle;
	increment();
	return *this;
}
template<typename Type>
inline asset::Ref<Type> & asset::Ref<Type>::operator=(Ref && other)
{
	if (this != &other)
	{
		decrement();
		m_handle = other.m_handle;
		other.m_handle = nullptr;
	}
	return *this;
}

template<typename Type>
inline bool asset::Ref<Type>::operator==(const Ref & other) const
{
	return m_handle == other.m_handle;
}
template<typename Type>
inline bool asset::Ref<Type>::operator!=(const Ref & other) const
{
	return m_handle != other.m_handle;
}
template<typename Type>
inline bool asset::Ref<Type>::operator==(const std::nullptr_t &) const
{
	return m_handle == nullptr || m_handle->m_handle == nullptr;
}
template<typename Type>
inline bool asset::Ref<Type>::operator!=(const std::nullptr_t &) const
{
	return m_handle != nullptr && m_handle->m_handle != nullptr;
}

template<typename Type>
inline Type & asset::Ref<Type>::operator*() const
{
	return *m_handle->m_handle;
}
template<typename Type>
inline Type * asset::Ref<Type>::operator->() const
{
	return m_handle == nullptr ? nullptr : m_handle->m_handle.get();
}

template<typename Type>
inline void asset::Ref<Type>::increment()
{
	if (m_handle == nullptr)
		return;
	if (m_handle->m_references == 0u && m_handle->m_factory != nullptr)
		m_handle->m_handle = m_handle->m_factory();
	m_handle->m_references++;
}
template<typename Type>
inline void asset::Ref<Type>::decrement()
{
	if (m_handle == nullptr || m_handle->m_references == 0u)
		return;
	m_handle->m_references--;
	if (m_handle->m_references == 0u)
		m_handle->m_handle = nullptr;
}
