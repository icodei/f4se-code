#pragma once

namespace RE
{
	class NiFrustum
	{
	public:
		float leftPlane;    // 00
		float rightPlane;   // 04
		float topPlane;     // 08
		float bottomPlane;  // 0C
		float nearPlane;    // 10
		float farPlane;     // 14
		bool ortho;         // 18
	};
	static_assert(sizeof(NiFrustum) == 0x1C);
}
