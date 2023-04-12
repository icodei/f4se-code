#pragma once
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Math/Matrix/hkTransformf.h"
#include "RE/Havok/Common/Base/Math/Quaternion/hkQuaternionf.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Physics/ConstraintSolver/VehicleFriction/hkpVehicleFriction.h"
#include "RE/Havok/Physics/Physics/Extensions/Actions/hknpAction.h"
#include "RE/Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h"

namespace RE
{
	class hknpTyremarksInfo;
	class hknpVehicleAerodynamics;
	class hknpVehicleBrake;
	class hknpVehicleData;
	class hknpVehicleDriverInput;
	class hknpVehicleDriverInputStatus;
	class hknpVehicleEngine;
	class hknpVehicleSteering;
	class hknpVehicleSuspension;
	class hknpVehicleTransmission;
	class hknpVehicleVelocityDamper;
	class hknpVehicleWheelCollide;
	class hkpVehicleFrictionStatus;
	class hkpVelocityAccumulator;
	struct hknpBodyId;

	class hknpVehicleInstance : public hknpUnaryAction
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleInstance };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleInstance };

		struct WheelInfo
		{
		public:
			hkContactPoint contactPoint;
			float contactFriction;
			std::uint32_t contactBodyId;
			std::uint32_t contactShapeKey;
			hkVector4f hardPointWs;
			hkVector4f rayEndPointWs;
			float currentSuspensionLength;
			hkVector4f suspensionDirectionWs;
			hkVector4f spinAxisChassisSpace;
			hkVector4f spinAxisWs;
			hkQuaternionf steeringOrientationChassisSpace;
			float spinVelocity;
			float noSlipIdealSpinVelocity;
			float spinAngle;
			float skidEnergyDensity;
			float sideForce;
			float forwardSlipVelocity;
			float sideSlipVelocity;
		};
		static_assert(sizeof(WheelInfo) == 0xC0);

		virtual ~hknpVehicleInstance();

		//add
		virtual void init();
		virtual void calcCurrentPositionAndRotation(hkTransformf&, hknpVehicleSuspension*, int, hkVector4f&, hkQuaternionf&);
		virtual float calcRPM() const;
		virtual float calcKMPH() const;
		virtual float calcMPH() const;
		virtual void handleFixedGroundAccum(hknpBodyId, hkpVelocityAccumulator&);

		//members
		void* world;
		hknpVehicleData* data;
		hknpVehicleDriverInput* driverInput;
		hknpVehicleSteering* steering;
		hknpVehicleEngine* engine;
		hknpVehicleTransmission* transmission;
		hknpVehicleBrake* brake;
		hknpVehicleSuspension* suspension;
		hknpVehicleAerodynamics* aerodynamics;
		hknpVehicleWheelCollide* wheelCollide;
		hknpTyremarksInfo* tyreMarks;
		hknpVehicleVelocityDamper* velocityDamper;
		hkArray<WheelInfo> wheelInfo;
		hkpVehicleFrictionStatus frictionStatus;
		hknpVehicleDriverInputStatus* deviceStatus;
		hkArray<bool> isFixed;
		float wheelsTimeSinceMaxPedalInput;
		bool tryingToReverse;
		float torque;
		float rpm;
		float mainSteeringAngle;
		float mainSteeringAngleAssumingNoReduction;
		hkArray<float> wheelsSteeringAngle;
		bool isReversing;
		std::int8_t currentGear;
		bool delayed;
		float clutchDelayCountdown;
	};
	static_assert(sizeof(hknpVehicleInstance) == 0x120);
}
