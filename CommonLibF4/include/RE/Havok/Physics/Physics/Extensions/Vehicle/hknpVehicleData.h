#pragma once
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Math/Matrix/hkRotationf.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Physics/ConstraintSolver/VehicleFriction/hkpVehicleFriction.h"
#include "RE/Havok/Physics/Physics/Dynamics/Motion/hknpMotion.h"
#include "RE/Havok/Physics/Physics/Extensions/Vehicle/Suspension/hknpVehicleSuspension.h"

namespace RE
{
	class hknpVehicleData : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleData };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleData };

		struct WheelComponentParams
		{
		public:
			//members
			float radius;
			float mass;
			float width;
			float friction;
			float viscosityFriction;
			float maxFriction;
			float slipAngle;
			float forceFeedbackMultiplier;
			float maxContactBodyAcceleration;
			std::int8_t axle;
		};
		static_assert(sizeof(WheelComponentParams) == 0x28);

		//add
		virtual void Init(hkArray<hknpVehicleSuspension::SuspensionWheelParameters> &,hkTransformf &,hknpMotion &);

		//members
		hkVector4f gravity;
		std::int8_t numWheels;
		hkRotationf chassisOrientation;
		float torqueRollFactor;
		float torquePitchFactor;
		float torqueYawFactor;
		float extraTorqueFactor;
		float maxVelocityForPositionalFriction;
		float chassisUnitInertiaYaw;
		float chassisUnitInertiaRoll;
		float chassisUnitInertiaPitch;
		float frictionEqualizer;
		float normalClippingAngleCos;
		float maxFrictionSolverMassRatio;
		hkArray<WheelComponentParams> wheelParams;
		hkArray<std::int8_t> numWheelsPerAxle;
		hkpVehicleFrictionDescription frictionDescription;
		hkVector4f chassisFrictionInertiaInvDiag;
		bool alreadyInitialised;
	};
	static_assert(sizeof(hknpVehicleData) == 0x1B0);
}
