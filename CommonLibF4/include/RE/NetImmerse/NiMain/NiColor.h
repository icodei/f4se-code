#pragma once

namespace RE
{
	class NiColor
	{
	public:
		NiColor() : r(0.0), g(0.0), b(0.0) {}
		NiColor(float red, float green, float blue)
		{
			r = red;
			g = green;
			b = blue;
		}

		static const NiColor WHITE;
		static const NiColor BLACK;

		// members
		float r;  // 0
		float g;  // 4
		float b;  // 8
	};
	static_assert(sizeof(NiColor) == 0xC);

	class NiColorA
	{
	public:
		NiColorA() : r(0.0), g(0.0), b(0.0), a(1.0) {}
		NiColorA(float red, float green, float blue, float alpha) {
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		static const NiColorA WHITE;
		static const NiColorA BLACK;

		// members
		float r;  // 0
		float g;  // 4
		float b;  // 8
		float a;  // C
	};
	static_assert(sizeof(NiColorA) == 0x10);
}
