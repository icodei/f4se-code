#pragma once

namespace RE
{
	class NiFrustum
	{
	public:
		float leftPlane{ -1.0 };      // 00
		float rightPlane{ 1.0 };      // 04
		float topPlane{ 0.563 };      // 08
		float bottomPlane{ -0.563 };  // 0C
		float nearPlane{ 15.0 };      // 10
		float farPlane{ 10240.0 };    // 14
		bool ortho{ false };          // 18
	};
	static_assert(sizeof(NiFrustum) == 0x1C);
}
