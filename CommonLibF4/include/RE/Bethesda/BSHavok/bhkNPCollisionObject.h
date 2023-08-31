#pragma once
#include "RE/Bethesda/BSHavok/bhkCollisionFilter.h"
#include "RE/Havok/Physics/Physics/Dynamics/Motion/hknpMotionPropertiesId.h"
#include "RE/NetImmerse/NiMain/NiCollisionObject.h"
#include "RE/NetImmerse/NiMain/NiFlags.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	enum class SHAPE_TYPES;

	class bhkCharacterControllerCinfo;
	class bhkCharacterMoveFinishEvent;
	class bhkCharacterStateChangeEvent;
	class bhkICharOrientationController;
	class bhkNonSupportContactEvent;
	class bhkNPCollisionObject;
	class bhkPhysicsSystem;
	class bhkWorld;
	class hknpBody;
	class hknpShape;

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

		void CopyMembers(bhkNPCollisionObject* from, NiCloningProcess& cp)
		{
			using func_t = decltype(&RE::bhkNPCollisionObject::CopyMembers);
			REL::Relocation<func_t> func{ REL::ID(1558409) };
			func(this, from, cp);
		}

		static bhkNPCollisionObject* Getbhk(bhkWorld* world, hknpBodyId& bodyId)
		{
			using func_t = decltype(&RE::bhkNPCollisionObject::Getbhk);
			REL::Relocation<func_t> func{ REL::ID(730034) };
			return func(world, bodyId);
		}

		hknpShape* GetShape()
		{
			using func_t = decltype(&RE::bhkNPCollisionObject::GetShape);
			REL::Relocation<func_t> func{ REL::ID(315427) };
			return func(this);
		}

		bool GetTransform(hkTransformf& transform)
		{
			using func_t = decltype(&RE::bhkNPCollisionObject::GetTransform);
			REL::Relocation<func_t> func{ REL::ID(1508189) };
			return func(this, transform);
		}

		void SetMotionType(hknpMotionPropertiesId::Preset type)
		{
			using func_t = decltype(&RE::bhkNPCollisionObject::SetMotionType);
			REL::Relocation<func_t> func{ REL::ID(200912) };
			return func(this, type);
		}

		bool SetTransform(hkTransformf& transform)
		{
			using func_t = decltype(&RE::bhkNPCollisionObject::SetTransform);
			REL::Relocation<func_t> func{ REL::ID(178085) };
			return func(this, transform);
		}

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
