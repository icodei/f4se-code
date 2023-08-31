#pragma once

namespace RE
{
	namespace BSResource
	{
		template <class T>
		class EntryQueue
		{
		public:
			//members
			BSNonReentrantSpinLock Lock;
			T* pHead;
			T** ppTail;
		};

		template <class T, std::uint32_t SIZE>
		class EntryBucketQueue
		{
		public:
			// members
			EntryQueue<T> buckets[SIZE];  // 00
			volatile std::uint32_t step;  // ??
		};
		static_assert(sizeof(EntryBucketQueue<void, 8>) == 0xC8);
	}
}
