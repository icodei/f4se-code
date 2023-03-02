#pragma once
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Types/Physics/hkBaseTypes.h"
#include "RE/Havok/Common/Base/Types/Physics/hkRefPtr.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4.h"
#include "RE/Havok/hknpBodyId.h"

namespace RE
{
	class hknpWorld;

	class hknpCharacterRigidBodyListener : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterRigidBodyListener };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterRigidBodyListener };
	};

	class hknpCharacterRigidBody : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterRigidBody };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterRigidBody };

		enum ContactType : std::int32_t
		{
			STANDARD = 0x0,
			BLOCKING = 0x1,
		};

		struct ContactPointInfo
		{
		public:
			//members
			hkContactPoint m_contactPoint;
			hknpBodyId m_otherBodyId;
			float m_stickyFactor;
			std::uint32_t m_characterShapeKey;
			std::uint32_t m_otherBodyShapeKey;
			hkEnum<hknpCharacterRigidBody::ContactType, std::uint8_t> m_contactType;
			hkDebugOnlyMember<hkBool> m_debugWasOtherBodyRemoved;
		};

		//members
		hknpBodyId m_bodyId;
		hknpShape* m_shape;
		hknpWorld* m_world;
		hkRefPtr<hknpCharacterRigidBodyListener> m_listener;
		hkVector4f m_up;
		float m_maxSlopeCosine;
		float m_maxSpeedForSimplexSolver;
		float m_supportDistance;
		float m_hardSupportDistance;
		hkVector4f m_acceleration;
		float m_maxForce;
		hkArray<hknpCharacterRigidBody::ContactPointInfo> m_manifold;
	};

}
