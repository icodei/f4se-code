#pragma once
#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTSingleton.h"

namespace RE
{
	template <
		class T,
		class Key,
		template <class, class> class HandlerCreationMissPolicy,
		template <class, class> class NoInitializationPolicy>
	class BSTObjectDictionary :
		public HandlerCreationMissPolicy<T, Key>,                                                               // 00
		public NoInitializationPolicy<T, Key>,                                                                  // 08
		public BSTSingletonSDM<BSTObjectDictionary<T, Key, HandlerCreationMissPolicy, NoInitializationPolicy>>  // 10
	{
	public:
		std::uint8_t pad11;                    // 11
		std::uint16_t pad12;                   // 12
		std::uint32_t pad14;                   // 14
		BSTHashMap<Key, T> objectDefinitions;  // 18
		mutable BSSpinLock definitionLock;     // 48
	};
	//static_assert(sizeof(BSTObjectDictionary) == 0x50);
}
