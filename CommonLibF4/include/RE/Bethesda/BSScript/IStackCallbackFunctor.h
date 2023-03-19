#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/Variable.h"
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
		class Variable;

		class __declspec(novtable) alignas(0x08) IStackCallbackFunctor :
			public BSIntrusiveRefCounted
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IStackCallbackFunctor };
			static constexpr auto VTABLE{ VTABLE::BSScript__IStackCallbackFunctor };

			virtual ~IStackCallbackFunctor();  // 00

			// add
			virtual void CallQueued() = 0;                    // 01
			virtual void CallCanceled() = 0;                  // 02
			virtual void StartMultiDispatch() = 0;            // 03
			virtual void EndMultiDispatch() = 0;              // 04
			virtual void operator()(BSScript::Variable) = 0;  // 05
			virtual bool CanSave() { return false; };         // 06
		};
		static_assert(sizeof(IStackCallbackFunctor) == 0x10);
	}
}
