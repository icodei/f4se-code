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
		class __declspec(novtable) IClientVM
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IClientVM };
			static constexpr auto VTABLE{ VTABLE::BSScript__IClientVM };

			virtual ~IClientVM();  // 00

			// add
			virtual bool IsVMFrozen() const;  // 01
			virtual void PreSave();           // 02
		};
		static_assert(sizeof(IClientVM) == 0x8);
	}
}
