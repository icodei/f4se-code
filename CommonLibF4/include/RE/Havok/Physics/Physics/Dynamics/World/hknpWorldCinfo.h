#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"
#include "RE/Havok/Common/Base/Types/hkRefPtr.h"
#include "RE/Havok/Physics2012/Dynamics/World/hkpWorldCinfo.h"

namespace RE
{
	class hknpShapeTagCodec;
	class hknpCollisionFilter;
	class hknpBroadPhaseConfig;
	class hknpBodyQualityLibrary;
	class hknpMotionPropertiesLibrary;
	class hknpMaterialLibrary;
	class hknpBody;
	class hknpMotion;
	class hknpBody;

	struct hknpWorldCinfo
	{
	public:
		enum LeavingBroadPhaseBehavior : __int32
		{
			ON_LEAVING_BROAD_PHASE_DO_NOTHING = 0x0,
			ON_LEAVING_BROAD_PHASE_REMOVE_BODY = 0x1,
			ON_LEAVING_BROAD_PHASE_FREEZE_BODY = 0x2,
		};

		enum SimulationType : __int32
		{
			SIMULATION_TYPE_SINGLE_THREADED = 0x0,
			SIMULATION_TYPE_MULTI_THREADED = 0x1,
		};

		using SolverType = hkpWorldCinfo::SolverType;

		//members
		std::int32_t m_bodyBufferCapacity;
		hknpBody* m_userBodyBuffer;
		std::int32_t m_motionBufferCapacity;
		hknpMotion* m_userMotionBuffer;
		std::int32_t m_constraintBufferCapacity;
		void* m_userConstraintBuffer;       //hknpConstraint
		void* m_persistentStreamAllocator;  //hkBlockStreamAllocator
		hkRefPtr<hknpMaterialLibrary> m_materialLibrary;
		hkRefPtr<hknpMotionPropertiesLibrary> m_motionPropertiesLibrary;
		hkRefPtr<hknpBodyQualityLibrary> m_qualityLibrary;
		hkEnum<SimulationType, unsigned char> m_simulationType;
		std::int32_t m_numSplitterCells;
		hkVector4f m_gravity;
		hkBool m_enableContactCaching;
		hkBool m_mergeEventsBeforeDispatch;
		hkEnum<LeavingBroadPhaseBehavior, unsigned char> m_leavingBroadPhaseBehavior;
		hkAabb m_broadPhaseAabb;
		hkRefPtr<hknpBroadPhaseConfig> m_broadPhaseConfig;
		hkRefPtr<hknpCollisionFilter> m_collisionFilter;
		hkRefPtr<hknpShapeTagCodec> m_shapeTagCodec;
		float m_collisionTolerance;
		float m_relativeCollisionAccuracy;
		hkBool m_enableWeldingForDefaultObjects;
		hkBool m_enableWeldingForCriticalObjects;
		float m_solverTau;
		float m_solverDamp;
		std::int32_t m_solverIterations;
		std::int32_t m_solverMicrosteps;
		float m_defaultSolverTimestep;
		float m_maxApproachSpeedForHighQualitySolver;
		hkBool m_enableDeactivation;
		hkBool m_deleteCachesOnDeactivation;
		std::int32_t m_largeIslandSize;
		hkBool m_enableSolverDynamicScheduling;
		std::int32_t m_contactSolverType;  //hknpContactSolverType::Enum
		float m_unitScale;
		hkBool m_applyUnitScaleToStaticConstants;
	};

	struct hknpWorldCinfo_DefaultStruct
	{
		std::int32_t s_defaultOffsets[37];
		std::int32_t m_bodyBufferCapacity;
		std::int32_t m_motionBufferCapacity;
		std::int32_t m_constraintBufferCapacity;
		std::uint8_t m_simulationType;
		int m_numSplitterCells;
		float m_gravity[4];
		char m_enableContactCaching;
		char m_mergeEventsBeforeDispatch;
		std::uint8_t m_leavingBroadPhaseBehavior;
		float m_collisionTolerance;
		float m_relativeCollisionAccuracy;
		float m_solverTau;
		float m_solverDamp;
		std::int32_t m_solverIterations;
		std::int32_t m_solverMicrosteps;
		float m_defaultSolverTimestep;
		float m_maxApproachSpeedForHighQualitySolver;
		char m_enableDeactivation;
		std::int32_t m_largeIslandSize;
		std::int32_t m_contactSolverType;  //hknpContactSolverType::Enum
		float m_unitScale;
		char m_applyUnitScaleToStaticConstants;
	};
}
