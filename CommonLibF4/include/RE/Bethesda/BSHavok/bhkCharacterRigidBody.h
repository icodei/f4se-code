#pragma once
#include "RE/Havok/Common/Base/Types/Physics/hkRefPtr.h"
#include "RE/NetImmerse/NiObject.h"

namespace RE
{
	class hkReferencedObject;

	class bhkCharacterRigidBody : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkCharacterRigidBody };
		static constexpr auto VTABLE{ VTABLE::bhkCharacterRigidBody };
		static constexpr auto Ni_RTTI{ Ni_RTTI::bhkCharacterRigidBody };

		//members
		hkRefPtr<hkReferencedObject> spCharRigidObject;
	};
}
