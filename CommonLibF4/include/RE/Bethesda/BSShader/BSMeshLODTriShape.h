#pragma once
#include "RE/NetImmerse/NiMain/BSTriShape.h"

namespace RE
{
	class BSMeshLODTriShape : public BSTriShape
	{
		static constexpr auto RTTI{ RTTI::BSMeshLODTriShape };
		static constexpr auto VTABLE{ VTABLE::BSMeshLODTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSMeshLODTriShape };

		//members
		std::uint32_t uiNumPrimitivesA[3];
	};

}
