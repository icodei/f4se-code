#pragma once
#include "RE/Bethesda/BSHavok/bhkIWorldstepListener.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h"
#include "RE/Havok/Physics/Physics/Extensions/CharacterControl/Proxy/hknpCharacterProxy.h"
#include "RE/Havok/Physics/Physics/Extensions/CharacterControl/RigidBody/hknpCharacterRigidbody.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class hknpWorld;
	class bhkCharProxyController;
	class bhkCharRigidBodyController;

	class bhkCharProxyManager : public bhkIWorldStepListener
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkCharProxyManager };
		static constexpr auto VTABLE{ VTABLE::bhkCharProxyManager };

		struct TriggerVolumeEventCmd
		{
		public:
			//members
			hknpBodyId TriggerBodyId;
			hknpBodyId OtherBodyId;
			int eStatus;  //hknpTriggerEvent::Status
			hknpWorld* pPhysicsWorld;
		};

		struct DeferredHkObjectInteractionsCmd
		{
		public:
			//members
			hknpCharacterProxy* pHkCharacterProxy;
			hkArray<hknpCharacterProxy::ObjectInteraction> ObjectInteractionsA;
		};

		struct AddDynamicBodyContactCmd
		{
		public:
			//members
			hknpCharacterRigidBody::ContactPointInfo ContactPoint;
			bhkCharRigidBodyController* pOtherController;
		};

		struct HandleBumpedCharacterCmd
		{
		public:
			//members
			hkContactPoint ContactPoint;
			bhkCharacterController* pMyController;
			bhkCharacterController* pOtherController;
		};

		struct ThreadLocalCharRBDeferredCmds
		{
		public:
			//members
			BSTAlignedArray<bhkCharProxyManager::HandleBumpedCharacterCmd, 16> HandleBumpedCharacterCmdA;
			BSTAlignedArray<bhkCharProxyManager::AddDynamicBodyContactCmd, 16> AddDynamicBodyContactCmdA;
			BSTAlignedArray<bhkCharProxyManager::TriggerVolumeEventCmd, 16> TriggerVolumeEventCmdA;
			BSTAlignedArray<bhkCharProxyManager::DeferredHkObjectInteractionsCmd, 16> DeferredHkObjectInteractionsCmdA;
		};

		//memebrs
		BSTArray<bhkCharProxyController*> ProxyControllersA;
		BSTHashMap<bhkCharProxyController*, std::uint32_t> mProxyControllerIndex;
		BSTAlignedArray<bhkCharProxyManager::ThreadLocalCharRBDeferredCmds, 16> DeferredCommandsA;
	};
}
