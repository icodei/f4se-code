#pragma once

namespace RE
{
	namespace BSResource
	{
		template <class T>
		class EntryQueue
		{
		public:
			BSNonReentrantSpinLock Lock;
			T* pHead;
			T** ppTail;
		};

		template <class T>
		class EntryBucketQueue
		{
		public:
			T Buckets[8];
			std::uint32_t uiStep;
		};
	}
}
