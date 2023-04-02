#pragma once
#include "RE/NetImmerse/NiMain/NiMatrix3.h"

namespace RE
{
	class NiQuaternion
	{
	public:
		void ToRotation(NiMatrix3& a_rotation)
		{
			using func_t = decltype(&NiQuaternion::ToRotation);
			REL::Relocation<func_t> func{ REL::ID(1379385) };
			return func(this, a_rotation);
		}

		//members
		float w;  // 00
		float x;  // 04
		float y;  // 08
		float z;  // 0C
	};
	static_assert(sizeof(NiQuaternion) == 0x10);
}
