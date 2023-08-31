#pragma once
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Math/Matrix/hkTransformf.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"
#include "RE/Havok/hknpBodyId.h"

namespace RE
{
	class hknpShape;
	class hknpWorld;

	class hknpCharacterProxyListener : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterProxyListener };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterProxyListener };
		//members
	};

	class hknpCharacterProxy : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterProxy };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterProxy };

		struct Contact
		{
		public:
			//members
			hkVector4f m_position;
			hkVector4f m_normal;
			float m_distance;
			float m_fraction;
			hknpBodyId m_bodyB;
			std::uint32_t m_shapeKeyB;
			std::uint32_t m_shapeKeyA;
			std::uint32_t m_collisionFilterInfoB;
			hkDebugOnlyMember<hkBool> m_debugWasBodyBRemoved;
		};

		struct ObjectInteraction
		{
		public:
			//members
			hknpBodyId m_bodyId;
			hkVector4f m_impulse;
			hkVector4f m_impulsePosition;
		};

		struct TriggerShape
		{
		public:
			//members
			hknpBodyId m_bodyId;
			std::uint32_t m_shapeKey;
			hkBool m_isOverlapping;
		};

		//members
		hkArray<hknpCharacterProxy::Contact> m_manifold;
		hknpShape* m_shape;
		std::uint64_t m_userData;
		hknpBodyId m_bodyId;
		std::uint32_t m_collisionFilterInfo;
		hknpWorld* m_world;
		hkTransformf m_transform;
		hkAabb m_aabb;
		hkVector4f m_velocity;
		hkVector4f m_lastDisplacement;
		float m_dynamicFriction;
		float m_staticFriction;
		hkVector4f m_up;
		float m_keepDistance;
		float m_keepContactTolerance;
		float m_contactAngleSensitivity;
		std::int32_t m_userPlanes;
		float m_maxCharacterSpeedForSolver;
		float m_characterStrength;
		float m_characterMass;
		hkArray<hknpCharacterProxyListener*> m_listeners;
		hkArray<hknpCharacterProxy::TriggerShape> m_overlappingTriggers;
		float m_maxSlopeCosine;
		float m_penetrationRecoverySpeed;
		std::uint32_t m_maxCastIterations;
		hkBool m_refreshManifoldInCheckSupport;
	};

}
