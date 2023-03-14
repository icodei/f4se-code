#pragma once

namespace RE
{
	class NiFrustum
	{
	public:
		NiFrustum() = default;
		NiFrustum(bool IsOrtho)
		{
			ortho = IsOrtho;
		}

		//members
		float leftPlane{ -1.0F };      // 00
		float rightPlane{ 1.0F };      // 04
		float topPlane{ 0.563F };      // 08
		float bottomPlane{ -0.563F };  // 0C
		float nearPlane{ 15.0F };      // 10
		float farPlane{ 10240.0F };    // 14
		bool ortho{ false };           // 18
	};
	static_assert(sizeof(NiFrustum) == 0x1C);
}
