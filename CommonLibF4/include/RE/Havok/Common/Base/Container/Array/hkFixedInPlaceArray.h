#pragma once

#include "RE/Havok/Common/Base/Container/Array/hkArray.h"

namespace RE
{
	struct hkContainerHeapAllocator;

	template <class T, std::uint32_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArray :
		public hkArray<T, Allocator>  // 00
	{
	public:
		using value_type = T;

	private:
		value_type _buffer[N];  // 10
	};

	template <class T, std::uint32_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArrayAligned16
	{
	public:
		using value_type = T;

	private:
		std::int32_t _padding;                                    // 10
		alignas(0x10) std::byte _buffer[N * sizeof(value_type)];  // 20
	};
}
