#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class bhkNPCollisionObject;
	class hknpSolverData;
	class hkTaskGraph;

	class bhkIWorldStepListener
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkIWorldStepListener };
		static constexpr auto VTABLE{ VTABLE::bhkIWorldStepListener };

		virtual ~bhkIWorldStepListener();

		//add
		virtual void BeforeWholePhysicsUpdate_GenerateGraphImpl(int, hkTaskGraph*);
		virtual void BeforeWholePhysicsUpdate_FinishImpl(void);
		virtual void BeforeAnyPhysicsStep_GenerateGraphImpl(int, hkTaskGraph*, float, float);
		virtual void BeforeAnyPhysicsStep_FinishImpl(float, float);
		virtual void BetweenPhysicsCollideAndSolve_GenerateGraphImpl(int, hkTaskGraph*, hknpSolverData*, float, float);
		virtual void BetweenPhysicsCollideAndSolve_FinishImpl(hknpSolverData*, float, float);
		virtual void AfterAnyPhysicsStep_GenerateGraphImpl(int, hkTaskGraph*, float, float);
		virtual void AfterAnyPhysicsStep_FinishImpl(float, float);
		virtual void AfterWholePhysicsUpdate_GenerateGraphImpl(int, hkTaskGraph*);
		virtual void AfterWholePhysicsUpdate_FinishImpl(void);

		//members
		BSTArray<BSTArray<NiPointer<bhkNPCollisionObject>>>* pDeferredReleaseColObjs;
	};
}
