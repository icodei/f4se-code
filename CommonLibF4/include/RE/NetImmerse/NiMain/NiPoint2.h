#pragma once

namespace RE
{
	class NiPoint2
	{
	public:

		static const NiPoint2 ZERO;
		static const NiPoint2 UNIT_X;
		static const NiPoint2 UNIT_Y;

		NiPoint2() = default;
		NiPoint2(float aValue) :
			x(aValue), y(aValue) {}
		NiPoint2(float aX, float aY) :
			x(aX), y(aY) {}

		// members
		float x{ 0.0F };
		float y{ 0.0F };
	};
	static_assert(sizeof(NiPoint2) == 0x8);
}
