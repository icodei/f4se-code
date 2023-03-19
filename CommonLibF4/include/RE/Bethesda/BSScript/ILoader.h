#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/Object.h"
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
		class IStore;  // stub
		class Object;

		namespace UnlinkedTypes
		{
			struct Object;  // stub
		}

		struct __declspec(novtable) ILoader
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ILoader };
			static constexpr auto VTABLE{ VTABLE::BSScript__ILoader };

			virtual ~ILoader() = default;  // 00

			// add
			virtual ILoader* Clone() const = 0;                                                     // 01
			virtual void SetScriptStore(const BSTSmartPointer<IStore>& a_newStore) = 0;             // 02
			virtual bool GetClass(const char* a_name, UnlinkedTypes::Object& a_unlinkedClass) = 0;  // 03
		};
		static_assert(sizeof(ILoader) == 0x8);
	}
}
