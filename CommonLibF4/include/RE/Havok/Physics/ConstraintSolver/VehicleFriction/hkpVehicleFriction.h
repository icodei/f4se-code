#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"

namespace RE
{

	class hkpVehicleFrictionDescription : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkpVehicleFrictionDescription };
		static constexpr auto VTABLE{ VTABLE::hkpVehicleFrictionDescription };


		struct AxisDescription
		{
		public:

			//members
			float frictionCircleYtab[16];
			float xStep;
			float xStart;
			float wheelSurfaceInertia;
			float wheelSurfaceInertiaInv;
			float wheelChassisMassRatio;
			float wheelRadius;
			float wheelRadiusInv;
			float wheelDownForceFactor;
			float wheelDownForceSumFactor;
		};
		static_assert(sizeof(AxisDescription) == 0x64);

		//members
		float wheelDistance;
		float chassisMassInv;
		AxisDescription axleDescr[2];
	};
	static_assert(sizeof(hkpVehicleFrictionDescription) == 0xE0);

	class hkpVehicleFrictionStatus
	{
	public:

		struct AxisStatus
		{
		public:

			//members
			float forward_slip_velocity;
			float side_slip_velocity;
			float skid_energy_density;
			float side_force;
			float delayed_forward_impulse;
			float sideRhs;
			float forwardRhs;
			float relativeSideForce;
			float relativeForwardForce;
		};
		static_assert(sizeof(AxisStatus) == 0x24);
		

		//members
		AxisStatus axis[2];
	};
	static_assert(sizeof(hkpVehicleFrictionStatus) == 0x48);
}
