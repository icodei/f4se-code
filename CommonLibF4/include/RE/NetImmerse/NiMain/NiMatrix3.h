#pragma once

#include "RE/NetImmerse/NiMain/NiPoint4.h"

namespace RE
{
	class alignas(0x10) NiMatrix3
	{
	public:
		void MakeIdentity() noexcept
		{
			entry[0].v = { 1.0F, 0.0F, 0.0F, 0.0F };
			entry[1].v = { 0.0F, 1.0F, 0.0F, 0.0F };
			entry[2].v = { 0.0F, 0.0F, 1.0F, 0.0F };
		}

		bool ToEulerAnglesXYZ(float* angleX, float* angleY, float* angleZ)
		{
			using func_t = decltype(&NiMatrix3::ToEulerAnglesXYZ);
			REL::Relocation<func_t> func{ REL::ID(34114) };
			return func(this, angleX, angleY, angleZ);
		}

		// members
		NiPoint4 entry[3];  // 00
	};
	static_assert(sizeof(NiMatrix3) == 0x30);
}
