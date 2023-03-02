#pragma once
#include "RE/Bethesda/BSCompoundFrustum.h"
#include "RE/Bethesda/BSPortalGraph.h"
#include "RE/NetImmerse/NiAccumulator.h"
#include "RE/NetImmerse/NiFrustumPlanes.h"
#include "RE/NetImmerse/NiFrustum.h"

namespace RE
{
	class NiVisibleArray;
	class NiCamera;

	class NiCullingProcess
	{
	public:
		static constexpr auto RTTI{ RTTI::NiCullingProcess };
		static constexpr auto VTABLE{ VTABLE::NiCullingProcess };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiCullingProcess };

		NiCullingProcess() = delete;
		NiCullingProcess(NiVisibleArray* a_array) { ctor(a_array); };

		//add
		virtual void GetRTTI(){};
		virtual void IsNode(){};
		virtual void IsNode2(){};
		virtual void IsSwitchNode(){};
		virtual void IsFadeNode(){};
		virtual void IsMultiBoundNode(){};
		virtual void IsGeometry(){};
		virtual void IsTriStrips(){};
		virtual void IsTriShape(){};
		virtual void IsDynamicTriShape(){};
		virtual void IsSegmentedTriShape(){};
		virtual void IsSubIndexTriShape(){};
		virtual void IsNiGeometry(){};
		virtual void IsNiTriBasedGeom(){};
		virtual void IsNiTriShape(){};
		virtual void IsParticlesGeom(){};
		virtual void IsParticleSystem(){};
		virtual void IsLinesGeom(){};
		virtual void IsLight(){};
		virtual void IsBhkNiCollisionObject(){};
		virtual void IsBhkBlendCollisionObject(){};
		virtual void IsBhkRigidBody(){};
		virtual void IsBhkLimitedHingeConstraint(){};
		virtual void IsbhkNPCollisionObject(){};
		virtual ~NiCullingProcess(){};
		virtual void Process(){};
		virtual void Process2(){};
		virtual void AppendVirtual(){};

		//members
		const bool m_bUseVirtualAppend{ 0 };
		NiVisibleArray* m_pkVisibleSet{ nullptr };
		NiCamera* m_pkCamera;
		NiFrustum m_kFrustum;
		NiFrustumPlanes m_kPlanes;
		NiFrustumPlanes kCustomCullPlanes;
		bool m_bCameraRelatedUpdates;
		bool bUpdateAccumulateFlag;
		bool bIgnorePreprocess;
		bool bCustomCullPlanes;
		bool bUnknownBool1;
		bool bUnknownBool2;

	private:
		NiCullingProcess* ctor(NiVisibleArray* a_array)
		{
			using func_t = decltype(&NiCullingProcess::ctor);
			REL::Relocation<func_t> func{ REL::ID(12355) };
			return func(this, a_array);
		}
		void* dtor()
		{
			using func_t = decltype(&NiCullingProcess::dtor);
			REL::Relocation<func_t> func{ REL::ID(717983) };
			return func(this);
		}
	};
}
