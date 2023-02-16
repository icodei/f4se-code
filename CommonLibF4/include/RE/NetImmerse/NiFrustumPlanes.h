#pragma once

namespace RE
{
	class NiFrustumPlanes
	{
	public:
		struct Planes
		{
			enum Plane
			{
				kNear,
				kFar,
				kLeft,
				kRight,
				kTop,
				kBottom,

				kTotal
			};
		};

		enum class ActivePlane
		{
			kNear = 1 << 0,
			kFar = 1 << 1,
			kLeft = 1 << 2,
			kRight = 1 << 3,
			kTop = 1 << 4,
			kBottom = 1 << 5
		};

		NiFrustumPlanes() { ctor(); }

		// members
		NiPlane cullingPlanes[6];       // 00
		ActivePlane activePlanes;       // 60
		std::uint32_t basePlaneStates;  // 64
		std::uint32_t unk68;            // 68
		std::uint32_t unk6C;            // 6C
	private:
		NiFrustumPlanes* ctor()
		{
			using func_t = decltype(&NiFrustumPlanes::ctor);
			REL::Relocation<func_t> func{ REL::ID(1221948) };
			return func(this);
		}
	};
}
