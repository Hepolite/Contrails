
#pragma once

namespace world
{
	namespace data
	{
		constexpr unsigned int MAX_BLOCK_ID = 2047u;	// Highest allowed block id
		constexpr unsigned int MAX_BLOCK_LIGHT = 31u;	// Highest allowed light value
		constexpr unsigned int MAX_CHUNK_SIZE = 32u;	// Highest allowed chunk size

		constexpr unsigned int MAX_QUERY_BYTE_SIZE = 512u * 1024u * 1024u;	// Highest allowed bytecount


		template<typename T> constexpr T CHUNK_SIZE_LG = T(5);
		template<typename T> constexpr T CHUNK_SIZE = T(T(1) << CHUNK_SIZE_LG<T>);
		template<typename T> constexpr T CHUNK_SIZE_BITS = T(CHUNK_SIZE<T> - T(1));
		template<typename T> constexpr T CHUNK_SIZE_VOLUME = T(CHUNK_SIZE<T> * CHUNK_SIZE<T> * CHUNK_SIZE<T>);

		template<typename T> constexpr T REGION_SIZE_LG = T(4);
		template<typename T> constexpr T REGION_SIZE = T(T(1) << REGION_SIZE_LG<T>);
		template<typename T> constexpr T REGION_SIZE_BITS = T(REGION_SIZE<T> - T(1));
		template<typename T> constexpr T REGION_SIZE_VOLUME = T(REGION_SIZE<T> * REGION_SIZE<T> * REGION_SIZE<T>);
	}
}