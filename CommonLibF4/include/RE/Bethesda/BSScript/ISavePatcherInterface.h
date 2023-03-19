#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/IVirtualMachine.h"
#include "RE/Bethesda/BSScript/StackFrame.h"
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
		class IVirtualMachine;
		class StackFrame;

		class ISavePatcherInterface
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ISavePatcherInterface };
			static constexpr auto VTABLE{ VTABLE::BSScript__ISavePatcherInterface };

			virtual ~ISavePatcherInterface() = default;  // 00

			// add
			virtual void PatchStackFrame(StackFrame&, IVirtualMachine&) = 0;  // 01
		};
		static_assert(sizeof(ISavePatcherInterface) == 0x8);
	}
}
