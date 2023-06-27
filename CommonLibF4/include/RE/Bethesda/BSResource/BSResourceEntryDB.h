#pragma once
#include "RE/Bethesda/BSResource/BSResourceEntryQueue.h"

namespace RE
{
	namespace BSResource
	{
		class IEntryDB
		{
		public:
			static constexpr auto RTTI{ RTTI::BSResource__IEntryDB };
			static constexpr auto VTABLE{ VTABLE::BSResource__IEntryDB };

			virtual ~IEntryDB();

			class PostFlushNotify
			{
			public:
				static constexpr auto RTTI{ RTTI::BSResource__IEntryDB__PostFlushNotify };
				static constexpr auto VTABLE{ VTABLE::BSResource__IEntryDB__PostFlushNotify };

				virtual ~PostFlushNotify();

				//members
				std::uint32_t Next;
				PostFlushNotify* pNext;
			};
			//members
			EntryBucketQueue<PostFlushNotify> PostFlushNotifyQueue;
		};

		template<class T>
		class EntryDB : public IEntryDB
		{

		};

		template<class T>
		struct EntryDBTraits
		{
			struct CArgs
			{

			};
		};
	}
}
