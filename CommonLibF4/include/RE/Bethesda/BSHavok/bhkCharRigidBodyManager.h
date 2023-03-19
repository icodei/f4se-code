#pragma once
#include "RE/Bethesda/BSHavok/bhkIWorldstepListener.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Types/Physics/ContactPoint/hkContactPoint.h"
#include "RE/Havok/Common/Base/Types/Physics/hkBaseTypes.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class bhkCharRigidBodyController;
	class hknpCharacterRigidBody;
	class hknpSolverData;
	class bhkCharacterController;

	class bhkCharRigidBodyManager : public bhkIWorldStepListener
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkCharRigidBodyManager };
		static constexpr auto VTABLE{ VTABLE::bhkCharRigidBodyManager };

		struct AddConstraintImmediateCmd
		{
		public:
			//members
			hkContactPoint ContactPoint;
			hknpSolverData* pSolverData;
			hknpBodyId BodyId;
			hknpBodyId OtherBodyId;
			float MaterialFriction;
		};

		struct HandleBumpedCharacterCmd
		{
		public:
			//members
			hkContactPoint ContactPoint;
			bhkCharacterController* pMyController;
			bhkCharacterController* pOtherController;
		};

		struct SetCharRBLinVelCmd
		{
		public:
			//members
			hknpCharacterRigidBody* pCharRb;
			hkVector4f LinearVel;
			float TimeStep;
		};

		struct ThreadLocalCharRBDeferredCmds
		{
		public:
			//members
			BSTAlignedArray<bhkCharRigidBodyManager::SetCharRBLinVelCmd, 16> SetCharRBLinVelCmdA;
			BSTAlignedArray<bhkCharRigidBodyManager::AddConstraintImmediateCmd, 16> AddConstraintImmCmdA;
			BSTAlignedArray<bhkCharRigidBodyManager::HandleBumpedCharacterCmd, 16> HandleBumpedCharacterCmdA;
		};

		//members
		BSTArray<bhkCharRigidBodyController*> RigidBodyControllersA;
		BSTHashMap<bhkCharRigidBodyController*, std::uint32_t> mRigidBodyControllerIndex;
		BSTAlignedArray<bhkCharRigidBodyManager::ThreadLocalCharRBDeferredCmds, 16> DeferredCommandsA;
	};

}
