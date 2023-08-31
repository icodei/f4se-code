#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSHavok/bhkCharProxyManager.h"
#include "RE/Bethesda/BSHavok/bhkCharRigidBodyManager.h"
#include "RE/Bethesda/BSHavok/bhkCollisionFilter.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Types/hkRefPtr.h"
#include "RE/Havok/Physics/Physics/Collide/Query/Collector/hknpCollisionQueryCollector.h"
#include "RE/Havok/Physics/Physics/Collide/Query/hknpCollisionQuery.h"
#include "RE/Havok/Physics/Physics/Collide/Query/hknpCollisionResult.h"
#include "RE/Havok/Physics/Physics/Dynamics/World/hknpWorld.h"
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class bhkIWorldStepListener;
	class bhkNPCollisionObject;
	class bhkTrapListener;
	class hclBSWorld;
	class hkbnpPhysicsInterface;
	class hkTaskQueue;
	class hknpBody;
	class hknpBSWorld;
	class NiAVObject;
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
		std::int32_t iClothStepBufferSize;
		std::int32_t eAdditionMode;  //hknpWorld::AdditionMode
		bhkTrapListener* pTrapListener;
		float fOriginalTau;
		float fOriginalDamping;
		bool bGlobalWindActivated;
		bool bAdded;
		bool bEnabled;
		bool bDebugDisplay;
	};
	static_assert(sizeof(bhkWorld) == 0x180);

	class hknpBSWorld : hknpWorld
	{
	public:
		void MarkForRead()
		{
			using func_t = decltype(&RE::hknpBSWorld::MarkForRead);
			REL::Relocation<func_t> func{ REL::ID(1190448) };
			return func(this);
		}

		void UnmarkForRead()
		{
			using func_t = decltype(&RE::hknpBSWorld::UnmarkForRead);
			REL::Relocation<func_t> func{ REL::ID(485648) };
			return func(this);
		}

		void MarkForWrite()
		{
			using func_t = decltype(&RE::hknpBSWorld::MarkForWrite);
			REL::Relocation<func_t> func{ REL::ID(1017544) };
			return func(this);
		}

		void UnmarkForWrite()
		{
			using func_t = decltype(&RE::hknpBSWorld::UnmarkForWrite);
			REL::Relocation<func_t> func{ REL::ID(312883) };
			return func(this);
		}

		//members
		//void* m_userData;
		//BSReadWriteLock WorldLock;
		//BSTSet<hknpBodyId, BSTScatterTableDefaultHashPolicy> ActivateBodyPostCollideSet;
		//BSSpinLock ActivateBodyPostCollideLock;
		//hkMultiMap<unsigned int, unsigned int, hkMultiMapOperations<unsigned int>, hkContainerHeapAllocator> ConstrainedBodyFromBody;
	};

	struct __declspec(novtable) bhkPickData
	{
	public:
		//using COLLECTOR_TYPE = hkcdShapeType::ShapeTypeEnum;

		bhkPickData()
		{
			typedef bhkPickData* func_t(bhkPickData*);
			REL::Relocation<func_t> func{ REL::ID(526783) };
			func(this);
		}

		void SetStartEnd(const NiPoint3& start, const NiPoint3& end)
		{
			using func_t = decltype(&bhkPickData::SetStartEnd);
			REL::Relocation<func_t> func{ REL::ID(747470) };
			return func(this, start, end);
		}

		void Reset()
		{
			using func_t = decltype(&bhkPickData::Reset);
			REL::Relocation<func_t> func{ REL::ID(438299) };
			return func(this);
		}

		bool HasHit()
		{
			using func_t = decltype(&bhkPickData::HasHit);
			REL::Relocation<func_t> func{ REL::ID(1181584) };
			return func(this);
		}

		float GetHitFraction()
		{
			using func_t = decltype(&bhkPickData::GetHitFraction);
			REL::Relocation<func_t> func{ REL::ID(476687) };
			return func(this);
		}

		int32_t GetAllCollectorRayHitSize()
		{
			using func_t = decltype(&bhkPickData::GetAllCollectorRayHitSize);
			REL::Relocation<func_t> func{ REL::ID(1288513) };
			return func(this);
		}

		bool GetAllCollectorRayHitAt(uint32_t i, hknpCollisionResult& res)
		{
			using func_t = decltype(&bhkPickData::GetAllCollectorRayHitAt);
			REL::Relocation<func_t> func{ REL::ID(583997) };
			return func(this, i, res);
		}

		void SortAllCollectorHits()
		{
			using func_t = decltype(&bhkPickData::SortAllCollectorHits);
			REL::Relocation<func_t> func{ REL::ID(1274842) };
			return func(this);
		}

		NiAVObject* GetNiAVObject()
		{
			using func_t = decltype(&bhkPickData::GetNiAVObject);
			REL::Relocation<func_t> func{ REL::ID(863406) };
			return func(this);
		}

		hknpBody* GetBody()
		{
			using func_t = decltype(&bhkPickData::GetBody);
			REL::Relocation<func_t> func{ REL::ID(1223055) };
			return func(this);
		}

		//members
		//hknpRayCastQuery npCastQuery;
		//hknpRayCastQueryResult npResult;
		//hkRefPtr<hknpBSWorld const> spCastWorld;
		//std::uint64_t CustomCollideLayers;
		//hknpCollisionQueryCollector* pnpCollector;
		//std::uint32_t eCollectorType;  //COLLECTOR_TYPE
		//bool bPickFailed;

		//members COMMONLIB
		std::uint64_t field_0;
		std::uint16_t field_8;
		CFilter collisionFilter;
		std::uint64_t field_10;
		std::uint32_t field_18;
		hkVector4f rayOrigin;
		hkVector4f rayDest;
		char gap40[16];
		int field_50;
		hknpCollisionResult result;
		hknpCollisionResult* field_C0;
		std::uint64_t collisionLayer;
		__int64 collector;
		int field_D8;
		__int16 field_DC;
		char field_DE;
		char field_DF;

		F4_HEAP_REDEFINE_NEW(bhkPickData);
	};
	static_assert(sizeof(bhkPickData) == 0xE0);
}
