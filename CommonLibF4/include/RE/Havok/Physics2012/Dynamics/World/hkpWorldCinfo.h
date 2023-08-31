#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"

namespace RE
{
	struct hkpWorldCinfo : public hkReferencedObject
	{
	public:
		enum BroadPhaseBorderBehaviour : __int32
		{
			BROADPHASE_BORDER_ASSERT = 0x0,
			BROADPHASE_BORDER_FIX_ENTITY = 0x1,
			BROADPHASE_BORDER_REMOVE_ENTITY = 0x2,
			BROADPHASE_BORDER_DO_NOTHING = 0x3,
		};
		enum BroadPhaseType : __int32
		{
			BROADPHASE_TYPE_SAP = 0x0,
			BROADPHASE_TYPE_TREE = 0x1,
			BROADPHASE_TYPE_HYBRID = 0x2,
		};
		enum ContactPointGeneration : __int32
		{
			CONTACT_POINT_ACCEPT_ALWAYS = 0x0,
			CONTACT_POINT_REJECT_DUBIOUS = 0x1,
			CONTACT_POINT_REJECT_MANY = 0x2,
		};
		enum SimulationType : __int32
		{
			SIMULATION_TYPE_INVALID = 0x0,
			SIMULATION_TYPE_DISCRETE = 0x1,
			SIMULATION_TYPE_CONTINUOUS = 0x2,
			SIMULATION_TYPE_MULTITHREADED = 0x3,
		};
		enum SolverType : __int32
		{
			SOLVER_TYPE_INVALID = 0x0,
			SOLVER_TYPE_2ITERS_SOFT = 0x1,
			SOLVER_TYPE_2ITERS_MEDIUM = 0x2,
			SOLVER_TYPE_2ITERS_HARD = 0x3,
			SOLVER_TYPE_4ITERS_SOFT = 0x4,
			SOLVER_TYPE_4ITERS_MEDIUM = 0x5,
			SOLVER_TYPE_4ITERS_HARD = 0x6,
			SOLVER_TYPE_8ITERS_SOFT = 0x7,
			SOLVER_TYPE_8ITERS_MEDIUM = 0x8,
			SOLVER_TYPE_8ITERS_HARD = 0x9,
			SOLVER_TYPE_MAX_ID = 0xA,
		};
		//members
	};

	struct hkpWorldCinfo_DefaultStruct
	{
		int s_defaultOffsets[54];
		float m_gravity[4];
		int m_broadPhaseQuerySize;
		float m_collisionTolerance;
		float m_expectedMaxLinearVelocity;
		int m_sizeOfToiEventQueue;
		float m_expectedMinPsiDeltaTime;
		float m_solverDamp;
		int m_solverIterations;
		int m_solverMicrosteps;
		float m_maxConstraintViolation;
		float m_snapCollisionToConvexEdgeThreshold;
		float m_snapCollisionToConcaveEdgeThreshold;
		float m_iterativeLinearCastEarlyOutDistance;
		int m_iterativeLinearCastMaxIterations;
		char m_shouldActivateOnRigidBodyTransformChange;
		float m_deactivationReferenceDistance;
		float m_toiCollisionResponseRotateNormal;
		int m_maxSectorsPerMidphaseCollideTask;
		int m_maxSectorsPerNarrowphaseCollideTask;
		char m_processToisMultithreaded;
		int m_maxEntriesPerToiMidphaseCollideTask;
		int m_maxEntriesPerToiNarrowphaseCollideTask;
		float m_numToisTillAllowedPenetrationSimplifiedToi;
		float m_numToisTillAllowedPenetrationToi;
		float m_numToisTillAllowedPenetrationToiHigher;
		float m_numToisTillAllowedPenetrationToiForced;
		char m_enableDeactivation;
		char m_enableSimulationIslands;
		unsigned int m_minDesiredIslandSize;
		char m_processActionsInSingleThread;
		float m_frameMarkerPsiSnap;
	};
}
