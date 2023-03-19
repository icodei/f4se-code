#pragma once
#include "RE/Bethesda/BSHavok/bhkCharProxyManager.h"
#include "RE/Bethesda/BSHavok/bhkCharRigidBodyManager.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Havok/Common/Base/Types/Physics/hkRefPtr.h"
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class bhkIWorldStepListener;
	class bhkNPCollisionObject;
	class bhkTrapListener;
	class hclBSWorld;
	class hkbnpPhysicsInterface;
	class hkTaskQueue;
	class hknpBSWorld;
	struct hknpWorldCinfo;

	class bhkWorld :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkWorld };
		static constexpr auto VTABLE{ VTABLE::bhkWorld };
		static constexpr auto Ni_RTTI{ Ni_RTTI::bhkWorld };

		// add
		virtual bool Update(std::uint32_t a_updateFlags);  // 28
		virtual void Init(const hknpWorldCinfo& a_info);   // 29

		static bool RemoveObjects(NiAVObject* a_object, bool a_recurse, bool a_force)
		{
			using func_t = decltype(&RemoveObjects);
			REL::Relocation<func_t> func{ REL::ID(1514984) };
			return func(a_object, a_recurse, a_force);
		}

		// members
		hkRefPtr<hkTaskQueue> spTaskQueue;
		BSTArray<bhkIWorldStepListener*> StepListenerA;
		hkRefPtr<hkbnpPhysicsInterface> spBehaviorInterface;
		BSReadWriteLock CharProxyManagerLock;
		BSReadWriteLock CharRigidBodyManagerLock;
		BSReadWriteLock StepListenerALock;
		hkVector4f Origin;
		hkRefPtr<hknpBSWorld> spWorldNP;
		bhkCharProxyManager CharProxyManager;
		bhkCharRigidBodyManager CharRigidBodyManager;
		hkRefPtr<hclBSWorld> spClothWorld;
		char* pClothStepBuffer;
		int iClothStepBufferSize;
		int eAdditionMode;  //hknpWorld::AdditionMode
		bhkTrapListener* pTrapListener;
		float fOriginalTau;
		float fOriginalDamping;
		bool bGlobalWindActivated;
		bool bAdded;
		bool bEnabled;
		bool bDebugDisplay;
	};
	static_assert(sizeof(bhkWorld) == 0x180);
}
