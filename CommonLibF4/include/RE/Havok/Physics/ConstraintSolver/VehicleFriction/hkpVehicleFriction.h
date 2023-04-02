#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"

namespace RE
{

	class hkpVehicleFrictionDescription : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkpVehicleFrictionDescription };
		static constexpr auto VTABLE{ VTABLE::hkpVehicleFrictionDescription };
		/*
		
		hkClassMember <offset aWheeldistance, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 16, 0>
		hkClassMember <offset aChassismassinv, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 20, 0>
		hkClassMember <offset aAxledescr, offset hkpVehicleFrictionDescriptionAxisDescriptionClass, 0, TYPE_STRUCT, TYPE_VOID, 2, 0, 24, 0>
		*/

		struct AxisDescription
		{
		public:
			/*
			hkTypeInfo <offset aHkpvehiclefric_2, offset aHkpvehiclefric_5, 0, offset cleanupLoadedObjecthkpVehicleFrictionDescriptionAxisDescription, 0, 64h>

			hkClassMember <offset aFrictioncircle, 0, 0, TYPE_REAL, TYPE_VOID, 10h, 0, 0, 0>
			hkClassMember <offset aXstep, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 64, 0>
			hkClassMember <offset aXstart, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 68, 0>
			hkClassMember <offset aWheelsurfacein, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 72, 0>
			hkClassMember <offset aWheelsurfacein_0, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 76, 0>
			hkClassMember <offset aWheelchassisma, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 80, 0>
			hkClassMember <offset aWheelradius, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 84, 0>
			hkClassMember <offset aWheelradiusinv, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 88, 0>
			hkClassMember <offset aWheeldownforce_0, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 92, 0>
			hkClassMember <offset aWheeldownforce, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 96, 0>
			*/

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
			/*
			hkTypeInfo  hkpVehicleFrictionStatusAxisStatus, !hkpVehicleFrictionStatus::AxisStatus, finishLoadedObjecthkpVehicleFrictionStatusAxisStatus, cleanupLoadedObjecthkpVehicleFrictionStatusAxisStatus, 0, 24h>
			 
			hkClassMember <aForwardSlipVel, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 0, 0>
			hkClassMember <aSideSlipVeloci, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 4, 0>
			hkClassMember <aSkidEnergyDens, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 8, 0>
			hkClassMember <aSideForce, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 12, 0>
			hkClassMember <aDelayedForward, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 16, 0>
			hkClassMember <aSiderhs, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 20, 0>
			hkClassMember <aForwardrhs, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 24, 0>
			hkClassMember <aRelativesidefo, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 28, 0>
			hkClassMember <aRelativeforwar, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 32, 0>
			*/

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
