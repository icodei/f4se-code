#pragma once

namespace RE
{
	class NiFrustumPlanes
	{
	public:
		enum
		{
			NEAR_PLANE = 0x0,
			FAR_PLANE = 0x1,
			LEFT_PLANE = 0x2,
			RIGHT_PLANE = 0x3,
			TOP_PLANE = 0x4,
			BOTTOM_PLANE = 0x5,
			MAX_PLANES = 0x6,
		};

		enum class ActivePlane
		{
			NEAR_PLANE_SET = 1 << 0,
			FAR_PLANE_SET = 1 << 1,
			LEFT_PLANE_SET = 1 << 2,
			RIGHT_PLANE_SET = 1 << 3,
			TOP_PLANE_SET = 1 << 4,
			BOTTOM_PLANE_SET = 1 << 5,
			ALL_PLANES_SET = 1 << 6
		};

		NiFrustumPlanes() { ctor(); }

		// members
		NiPlane m_akCullingPlanes[MAX_PLANES];  // 00
		ActivePlane m_uiActivePlanes;           // 60
		std::uint32_t m_uiBasePlaneStates;      // 64
		std::uint32_t m_Pad[2];                 // 68
	private:
		NiFrustumPlanes* ctor()
		{
			using func_t = decltype(&NiFrustumPlanes::ctor);
			REL::Relocation<func_t> func{ REL::ID(1221948) };
			return func(this);
		}
	};
}
