#pragma once
#include "RE/Bethesda/BSResource/BSResourceEntryQueue.h"

namespace RE
{
	namespace BSResource
	{
		class Location;
		class EntryBase;

		class IEntryDB
		{
		public:
			static constexpr auto RTTI{ RTTI::BSResource__IEntryDB };
			static constexpr auto VTABLE{ VTABLE::BSResource__IEntryDB };

			class NotifyLoadDone
			{
			public:
				virtual ~NotifyLoadDone();  // 00

				// add
				virtual void operator()() = 0;  // 01
			};
			static_assert(sizeof(NotifyLoadDone) == 0x08);

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
			static_assert(sizeof(PostFlushNotify) == 0x18);

			virtual ~IEntryDB();  // 00

			// add
			virtual void CancelLoads() = 0;                                                              // 01
			virtual void FlushReleases() = 0;                                                            // 02
			virtual bool DoLoadIfSameOrBetter(std::uint32_t a_priority) = 0;                             // 03
			virtual void DoMergeLoadsFromTo(std::uint32_t a_from, std::uint32_t a_to) = 0;               // 04
			virtual std::uint32_t UserFlush(NotifyLoadDone* a_notify, std::uint32_t a_maxPriority) = 0;  // 05

			//members
			EntryBucketQueue<PostFlushNotify, 8> PostFlushNotifyQueue;
		};

		template<class T>
		class EntryDB : public IEntryDB
		{

		};

		template <class T_DBTraits, class T_EntryDB>
		class EntryDBTraits
		{
		public:
			using U_DBTraits = T_DBTraits;
			using U_EntryDB = T_EntryDB;

			class CArgs
			{
			public:
				// members
				T_DBTraits::ArgsType args;  // 00
				BSFixedString name;         // ??
			};
		};
		static_assert(std::is_empty_v<EntryDBTraits<void, void>>);

		class EntryDBBaseUtil
		{
		public:
			static bool ReleaseEntryAction(EntryBase* a_entry)
			{
				using func_t = decltype(&EntryDBBaseUtil::ReleaseEntryAction);
				REL::Relocation<func_t> func{ REL::ID(777279) };
				return func(a_entry);
			}

			// members
			Location* rootLocation;              // 00
			std::uint32_t resourcePriorityBase;  // 08
			bool allowDeadLoadSkipping;          // 0C
		};
		static_assert(sizeof(EntryDBBaseUtil) == 0x10);
	}
}
