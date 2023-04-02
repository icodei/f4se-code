#pragma once
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Math/Matrix/hkRotationf.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Physics/ConstraintSolver/VehicleFriction/hkpVehicleFriction.h"

namespace RE
{

	class hknpVehicleData : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleData };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleData };

		struct WheelComponentParams {
		public:
			/*
			hkTypeInfo <offset aHknpvehicledat_1, offset aHknpvehicledat_0, 0, offset cleanupLoadedObjecthknpVehicleDataWheelComponentParams, 0, 28h>

			hkClassMember <offset aRadius, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 0, 0>
			hkClassMember <offset aMass_0, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 4, 0>
			hkClassMember <offset aWidth_1, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 8, 0>
			hkClassMember <offset aFriction, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 0Ch, 0>
			hkClassMember <offset aViscosityfrict, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 10h, 0>
			hkClassMember <offset aMaxfriction, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 14h, 0>
			hkClassMember <offset aSlipangle, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 18h, 0>
			hkClassMember <offset aForcefeedbackm, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 1Ch, 0>
			hkClassMember <offset aMaxcontactbody, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 20h, 0>
			hkClassMember <offset aAxle, 0, 0, TYPE_INT8, TYPE_VOID, 0, 0, 24h, 0>
			*/

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

		/*
		
		hkClassMember<offset Gravity, 0, 0, TYPE_VECTOR4, TYPE_VOID, 0, 0, 16, 0>;
		hkClassMember<offset Numwheels, 0, 0, TYPE_INT8, TYPE_VOID, 0, 0, 32, 0>;
		hkClassMember<offset Chassisorienta, 0, 0, TYPE_ROTATION, TYPE_VOID, 0, 0, 48, 0>;
		hkClassMember<offset Torquerollfact, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 96, 0>;
		hkClassMember<offset Torquepitchfac, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 100, 0>;
		hkClassMember<offset Torqueyawfacto, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 104, 0>;
		hkClassMember<offset Extratorquefac, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 108, 0>;
		hkClassMember<offset Maxvelocityfor, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 112, 0>;
		hkClassMember<offset Chassisunitine_0, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 116, 0>;
		hkClassMember<offset Chassisunitine_1, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 120, 0>;
		hkClassMember<offset Chassisunitine, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 124, 0>;
		hkClassMember<offset Frictionequali, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 128, 0>;
		hkClassMember<offset Normalclipping, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 132, 0>;
		hkClassMember<offset Maxfrictionsol, 0, 0, TYPE_REAL, TYPE_VOID, 0, 0, 136, 0>;
		hkClassMember<offset Wheelparams, hknpVehicleDataWheelComponentParamsClass, 0, TYPE_ARRAY, TYPE_STRUCT, 0, 0, 144, 0>;
		hkClassMember<offset Numwheelsperax, 0, 0, TYPE_ARRAY, TYPE_INT8, 0, 0, 160, 0>;
		hkClassMember<offset Frictiondescri, hkpVehicleFrictionDescriptionClass, 0, TYPE_STRUCT, TYPE_VOID, 0, 0, 176, 0>;
		hkClassMember<offset Chassisfrictio, 0, 0, TYPE_VECTOR4, TYPE_VOID, 0, 0, 400, 0>;
		hkClassMember<offset Alreadyinitial, 0, 0, TYPE_BOOL, TYPE_VOID, 0, 0, 416, 0>
		*/

		//add
		virtual void Init();

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
