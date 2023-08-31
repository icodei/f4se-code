#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"

namespace RE
{
	class hknpWorld : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpWorld };
		static constexpr auto VTABLE{ VTABLE::hknpWorld };

		enum AdditionFlagsEnum : __int32
		{
			NO_FLAGS = 0x0,
			START_INACTIVE = 0x1,
		};

		enum AdditionMode : __int32
		{
			DO_NOT_ADD_BODY = 0x0,
			ADD_BODY_NOW = 0x1,
			ADD_BODY_IN_NEXT_STEP = 0x2,
		};

		enum PivotLocation : __int32
		{
			PIVOT_BODY_POSITION = 0x0,
			PIVOT_CENTER_OF_MASS = 0x1,
		};

		enum RebuildCachesMode : __int32
		{
			REBUILD_COLLISION_CACHES = 0x0,
			KEEP_COLLISION_CACHES = 0x1,
		};

		enum RebuildMassPropertiesMode : __int32
		{
			REBUILD_NOW = 0x0,
			REBUILD_DELAYED = 0x1,
		};

		enum SimulationStage : std::uint32_t
		{
			SIMULATION_DONE = 0x1,
			SIMULATION_PRE_COLLIDE = 0x2,
			SIMULATION_COLLIDE = 0x4,
			SIMULATION_POST_COLLIDE = 0x8,
			SIMULATION_PRE_SOLVE = 0x10,
			SIMULATION_SOLVE = 0x20,
			SIMULATION_POST_SOLVE = 0x40,
		};

		//using UpdateMassPropertiesMode = hknpBodyManager::ScheduledBodyFlagsEnum;

		//members
		//hknpBodyManager m_bodyManager;
		//hknpMotionManager m_motionManager;
		//hknpConstraintManager m_constraintManager;
		//hknpModifierManager* m_modifierManager;
		//hkRefPtr<hkBlockStreamAllocator> m_persistentStreamAllocator;
		//hkBlockStreamAllocator* m_stepLocalStreamAllocator;
		//hknpSimulation* m_simulation;
		//hknpSpaceSplitter* m_spaceSplitter;
		//hknpBroadPhase* m_broadPhase;
		//hkIntSpaceUtil m_intSpaceUtil;
		//hkSimdFloat32 m_collisionTolerance;
		//hknpCollisionCacheManager* m_collisionCacheManager;
		//hknpCollisionDispatcher* m_collisionDispatcher;
		//hknpCollisionQueryDispatcherBase* m_collisionQueryDispatcher;
		//hkBool m_contactCachingEnabled;
		//hkBlockStream<char> m_lastFrameContactData;
		//hknpContactSolverType::Enum m_contactSolverType;
		//hknpContactConstraintSolver* m_contactSolver;
		//hknpConstraintAtomSolver* m_constraintAtomSolver;
		//hknpSolverInfo m_solverInfo;
		//hkBool m_enableSolverDynamicScheduling;
		//hkArray<hknpSolverVelocity, hkContainerHeapAllocator> m_solverVelocities;
		//hkArray<hknpSolverSumVelocity, hkContainerHeapAllocator> m_solverSumVelocities;
		//hkBool m_deactivationEnabled;
		//hknpDeactivationManager* m_deactivationManager;
		//hkBool m_deleteCachesOnDeactivation;
		//hknpWorldSignals m_signals;
		//hkPrimaryCommandDispatcher* m_commandDispatcher;
		//hkRefPtr<hkSecondaryCommandDispatcher> m_traceDispatcher;
		//std::uint64_t m_userData;
		//hkVector4f m_gravity;
		//hkRefPtr<hkReferencedObject> m_defaultModifierSet;
		//hkRefPtr<hknpMaterialLibrary> m_materialLibrary;
		//hkRefPtr<hknpMotionPropertiesLibrary> m_motionPropertiesLibrary;
		//hkRefPtr<hknpBodyQualityLibrary> m_qualityLibrary;
		//hkBitField m_dirtyMaterials;
		//hkBitField m_dirtyQualities;
		//hknpShapeManager m_shapeManager;
		//hkRefPtr<hknpShapeTagCodec> m_shapeTagCodec;
		//hknpNullShapeTagCodec* m_nullShapeTagCodec;
		//hkRefPtr<hknpEventDispatcher> m_eventDispatcher;
		//hkRefPtr<hknpInternalCommandProcessor> m_internalPhysicsCommandDispatcher;
		//hkBool m_consistencyChecksEnabled;
		//hknpPostCollideTask* m_postCollideTask;
		//hknpPostSolveTask* m_postSolveTask;
		//hkEnum<hknpWorld::SimulationStage, std::uint32_t> m_simulationStage;
		//hknpSimulationContext* m_simulationContext;
		//hknpActionManager* m_actionManager;
		//hkEnum<hknpWorldCinfo::SimulationType, unsigned char> m_simulationType;
		//hkBool m_mergeEventsBeforeDispatch;
		//hkEnum<hknpWorldCinfo::LeavingBroadPhaseBehavior, unsigned char> m_leavingBroadPhaseBehavior;
	};
}
