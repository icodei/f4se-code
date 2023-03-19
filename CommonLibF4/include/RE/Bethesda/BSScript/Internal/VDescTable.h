#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/TypeInfo.h"
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
		class TypeInfo;

		namespace Internal
		{
			class VDescTable
			{
			public:
				using value_type = BSTTuple<BSFixedString, TypeInfo>;
				using size_type = std::uint16_t;

				VDescTable(size_type a_params, size_type a_locals) :
					paramCount(a_params),
					totalEntries(a_params + a_locals)
				{
					const auto total = paramCount + totalEntries;
					if (total > 0) {
						entries = new value_type[total];
					}
				}

				~VDescTable() { delete[] entries; }

				// members
				value_type* entries{ nullptr };  // 00
				size_type paramCount{ 0 };       // 08
				size_type totalEntries{ 0 };     // 0A
			};
			static_assert(sizeof(VDescTable) == 0x10);
		}
	}
}
