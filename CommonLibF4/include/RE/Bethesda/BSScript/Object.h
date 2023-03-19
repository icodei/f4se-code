#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/ObjectTypeInfo.h"
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
		class ObjectTypeInfo;
		class Variable;

		class Object
		{
		public:
			~Object();

			ObjectTypeInfo* GetTypeInfo();
			[[nodiscard]] const ObjectTypeInfo* GetTypeInfo() const;
			[[nodiscard]] constexpr bool IsConstructed() const noexcept { return static_cast<bool>(constructed); }
			[[nodiscard]] constexpr bool IsInitialized() const noexcept { return static_cast<bool>(initialized); }
			[[nodiscard]] constexpr bool IsValid() const noexcept { return static_cast<bool>(valid); }

			[[nodiscard]] void* Resolve(std::uint32_t a_typeID) const;

			[[nodiscard]] std::uint32_t DecRef() const
			{
				using func_t = decltype(&Object::DecRef);
				REL::Relocation<func_t> func{ REL::ID(541793) };
				return func(this);
			}

			[[nodiscard]] std::size_t GetHandle() const
			{
				using func_t = decltype(&Object::GetHandle);
				REL::Relocation<func_t> func{ REL::ID(1452752) };
				return func(this);
			}

			void IncRef() const
			{
				using func_t = decltype(&Object::IncRef);
				REL::Relocation<func_t> func{ REL::ID(461710) };
				return func(this);
			}

			Variable* GetProperty(const BSFixedString& a_name);
			[[nodiscard]] const Variable* GetProperty(const BSFixedString& a_name) const;

			// TODO: Figure out if F4_HEAP_REDEFINE_NEW is necessary here
			//			F4_HEAP_REDEFINE_NEW(Object);

			// members
			std::uint32_t constructed: 1;            // 00:00
			std::uint32_t initialized: 1;            // 00:01
			std::uint32_t valid: 1;                  // 00:02
			std::uint32_t remainingPropsToInit: 29;  // 00:03
			BSTSmartPointer<ObjectTypeInfo> type;    // 08
			BSFixedString currentState;              // 10
			void* lockStructure;                     // 18
			std::size_t handle;                      // 20
			std::uint32_t refCountAndHandleLock;     // 28
			Variable variables[0];                   // 30
		};
		static_assert(sizeof(Object) == 0x30);
	}
}
