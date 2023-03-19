#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSCore/BSScrapArray.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTObjectArena.h"
#include "RE/Bethesda/BSCore/BSTTuple.h"
#include "RE/Bethesda/BSCore/MemoryManager.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/IVirtualMachine.h"
#include "RE/Bethesda/BSScript/Variable.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
namespace RE
{
	namespace BSScript
	{
		class IVirtualMachine;
		class Variable;

		template <typename T>
		class ArrayWrapper
		{
		public:
			ArrayWrapper() = delete;

			F4_HEAP_REDEFINE_NEW(ArrayWrapper<T>);

		private:
			// members
			Variable wrappedVar;  // 00
		};
		static_assert(sizeof(ArrayWrapper<void*>) == 0x10);

		template <>
		class ArrayWrapper<BSScript::Variable>
		{
		public:
			ArrayWrapper() = delete;
			ArrayWrapper(BSScrapArray<Variable>& a_copy, IVirtualMachine& a_vm)
			{
				ReplaceArray(a_copy, a_vm);
			}

			F4_HEAP_REDEFINE_NEW(ArrayWrapper<BSScript::Variable>);

			void ReplaceArray(BSScrapArray<Variable>& a_copy, IVirtualMachine& a_vm)
			{
				using func_t = decltype(&ArrayWrapper::ReplaceArray);
				REL::Relocation<func_t> func{ REL::ID(445184) };
				return func(this, a_copy, a_vm);
			}

		private:
			// members
			Variable wrappedVar;  // 00
		};
		static_assert(sizeof(ArrayWrapper<Variable>) == 0x10);
	}
}
