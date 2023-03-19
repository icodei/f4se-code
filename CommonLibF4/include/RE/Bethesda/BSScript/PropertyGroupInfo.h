#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTObjectArena.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/Bethesda/BSCore/BSTTuple.h"
#include "RE/Bethesda/BSCore/MemoryManager.h"

namespace RE
{
	namespace BSScript
	{
		class PropertyGroupInfo :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			// members
			BSFixedString groupName;                // 08
			BSFixedString docString;                // 10
			std::uint32_t userFlags;                // 18
			BSTArray<BSFixedString> propertyNames;  // 20
		};
		static_assert(sizeof(PropertyGroupInfo) == 0x38);
	}
}
