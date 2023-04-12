#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Math/Quaternion/hkQuaternionf.h"

namespace RE
{
	class hknpMotion
	{
	public:
		//members
		hkVector4f centerOfMassAndMassFactor;
		hkQuaternionf orientation;
		std::int16_t inverseInertia[4];	//hkHalf
		std::uint32_t firstAttachedBodyId;
		std::uint32_t solverId;
		__declspec(align(16)) std::int16_t linearVelocityCage[3];	//hkHalf
		std::int16_t integrationFactor;	//hkHalf
		std::uint16_t motionPropertiesId;
		std::int16_t maxLinearAccelerationDistancePerStep;	//hkHalf
		std::int16_t maxRotationToPreventTunneling;	//hkHalf
		std::uint8_t cellIndex;
		std::uint8_t spaceSplitterWeight;
		hkVector4f linearVelocity;
		hkVector4f angularVelocity;
		hkVector4f previousStepLinearVelocity;
		hkVector4f previousStepAngularVelocity;
	};
	static_assert(sizeof(hknpMotion) == 0x80);
}
