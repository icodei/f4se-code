#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/IStackCallbackFunctor.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTObjectArena.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/Bethesda/BSCore/BSTTuple.h"
#include "RE/Bethesda/BSCore/MemoryManager.h"

namespace RE
{
	class BSStorage;

	namespace BSScript
	{
		class IStackCallbackFunctor;

		class __declspec(novtable) IStackCallbackSaveInterface
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IStackCallbackSaveInterface };
			static constexpr auto VTABLE{ VTABLE::BSScript__IStackCallbackSaveInterface };

			virtual ~IStackCallbackSaveInterface();  // 00

			// add
			virtual bool SaveStackCallback(BSStorage& a_buffer, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) const;         // 01
			virtual bool LoadStackCallback(const BSStorage& a_buffer, bool&, BSTSmartPointer<IStackCallbackFunctor>& a_callback) const;  // 02
		};
		static_assert(sizeof(IStackCallbackSaveInterface) == 0x8);
	}
}
