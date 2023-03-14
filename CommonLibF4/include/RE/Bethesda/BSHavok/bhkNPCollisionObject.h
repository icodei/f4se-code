#pragma once
#include "RE/Bethesda/BSHavok/bhkCollisionFilter.h"
#include "RE/Havok/Common/Base/Types/Physics/hkBaseTypes.h"
#include "RE/Havok/Common/Base/Types/Physics/hkRefPtr.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/NetImmerse/NiMain/NiCollisionObject.h"
#include "RE/NetImmerse/NiMain/NiFlags.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class bhkPhysicsSystem;
	class bhkWorld;

	class __declspec(novtable) bhkNPCollisionObjectBase :
		public NiCollisionObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkNPCollisionObjectBase };
		static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObjectBase };

		// add
		virtual void LockMotionImpl() = 0;  // 2C

		// members
		NiTFlags<std::uint16_t, bhkNPCollisionObjectBase> flags;  // 18
	};
	static_assert(sizeof(bhkNPCollisionObjectBase) == 0x20);

	class __declspec(novtable) bhkNPCollisionObject :
		public bhkNPCollisionObjectBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkNPCollisionObject };
		static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObject };

		// add
		virtual void CreateInstance(bhkWorld& a_world);             // 2D
		virtual void AddToWorld(bhkWorld& a_world);                 // 2E
		virtual void RemoveFromWorld();                             // 2F
		virtual bool SetCollisionFilterInfo(CFilter a_filterInfo);  // 30

		// members
		NiPointer<bhkPhysicsSystem> spSystem;  // 20
		std::uint32_t systemBodyIdx;           // 28
	};
	static_assert(sizeof(bhkNPCollisionObject) == 0x30);

	class __declspec(novtable) bhkNPCollisionObjectUnlinked :
		public bhkNPCollisionObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkNPCollisionObjectUnlinked };
		static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObjectUnlinked };
	};
	static_assert(sizeof(bhkNPCollisionObjectUnlinked) == 0x30);
}
