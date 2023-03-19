#pragma once
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundShape;

	class BSMultiBound : public NiObject
	{
		static constexpr auto RTTI{ RTTI::BSMultiBound };
		static constexpr auto VTABLE{ VTABLE::BSMultiBound };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSMultiBound };

		//members
		std::uint32_t uiBoundFrameCount;
		NiPointer<BSMultiBoundShape> spShape;
	};
}
