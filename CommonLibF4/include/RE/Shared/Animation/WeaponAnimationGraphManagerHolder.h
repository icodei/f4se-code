#pragma once
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/Shared/Animation/IAnimationGraphManagerHolder.h"

namespace RE
{
	class WeaponAnimationGraphManagerHolder :
		public IAnimationGraphManagerHolder,
		public BSTEventSink<BSAnimationGraphEvent>,
		public BSIntrusiveRefCounted
	{
	public:
		static constexpr auto RTTI{ RTTI::WeaponAnimationGraphManagerHolder };
		static constexpr auto VTABLE{ VTABLE::WeaponAnimationGraphManagerHolder };

		//members
		std::uint64_t unk;
		std::uint32_t unk1;
	};
	static_assert(sizeof(WeaponAnimationGraphManagerHolder) == 0x28);
}
