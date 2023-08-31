#pragma once

#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiExtraDataContainer;
	class NiTimeController;

	class __declspec(novtable) NiObjectNET :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiObjectNET };
		static constexpr auto VTABLE{ VTABLE::NiObjectNET };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiObjectNET };

		enum CopyType : std::int32_t
		{
			COPY_NONE = 0x0,
			COPY_EXACT = 0x1,
			COPY_UNIQUE = 0x2,
		};

		NiObjectNET();
		virtual ~NiObjectNET();  // NOLINT(modernize-use-override) 00

		[[nodiscard]] std::string_view GetName() const { return name; }

		void SetNameConst(const BSFixedString& a_name)
		{
			using func_t = decltype(&NiObjectNET::SetNameConst);
			REL::Relocation<func_t> func{ REL::ID(493272) };
			return func(this, a_name);
		}

		static char GetDefaultAppendCharacter(void)
		{
			using func_t = decltype(&NiObjectNET::GetDefaultAppendCharacter);
			REL::Relocation<func_t> func{ REL::ID(468580), 0xE };
			return func();
		}

		static CopyType GetDefaultCopyType(void)
		{
			using func_t = decltype(&NiObjectNET::GetDefaultCopyType);
			REL::Relocation<func_t> func{ REL::ID(468580), 0x1E };
			return func();
		}

		static void SetDefaultCopyType(CopyType a_copy) {
			using func_t = decltype(&NiObjectNET::SetDefaultCopyType);
			REL::Relocation<func_t> func{ REL::ID(1129741), 0x30 };
			return func(a_copy);
		}

		// members
		BSFixedString name{ "" };                 // 10
		NiPointer<NiTimeController> controllers;  // 18
		NiExtraDataContainer* extra{ nullptr };   // 20

		F4_HEAP_REDEFINE_NEW(NiObjectNET);
	};
	static_assert(sizeof(NiObjectNET) == 0x28);
}
