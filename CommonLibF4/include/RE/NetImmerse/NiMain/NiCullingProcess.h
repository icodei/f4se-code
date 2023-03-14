#pragma once
#include "RE/Bethesda/BSCompoundFrustum.h"
#include "RE/Bethesda/BSPortalGraph.h"
#include "RE/NetImmerse/NiAccumulator.h"
#include "RE/NetImmerse/NiMain/NiFrustum.h"
#include "RE/NetImmerse/NiMain/NiFrustumPlanes.h"

namespace RE
{
	class bhkBlendCollisionObject;
	class bhkLimitedHingeConstraint;
	class bhkNiCollisionObject;
	class bhkNPCollisionObject;
	class bhkRigidBody;
	class BSDynamicTriShape;
	class BSFadeNode;
	class BSGeometry;
	class BSLines;
	class BSMultiBoundNode;
	class BSSegmentedTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class NiAVObject;
	class NiCamera;
	class NiGeometry;
	class NiLight;
	class NiNode;
	class NiParticles;
	class NiParticleSystem;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;
	class NiVisibleArray;
	struct NiRTTI;

	class NiCullingProcess
	{
	public:
		static constexpr auto RTTI{ RTTI::NiCullingProcess };
		static constexpr auto VTABLE{ VTABLE::NiCullingProcess };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiCullingProcess };

		NiCullingProcess() = delete;
		NiCullingProcess(NiVisibleArray* a_array) { ctor(a_array); };

		//add
		virtual const NiRTTI* GetRTTI() const { return nullptr; }                             // 02
		virtual const NiNode* IsConstNode() const { return nullptr; }                         // 03
		virtual NiNode* IsNode() { return nullptr; }                                          // 04
		virtual NiSwitchNode* IsSwitchNode() { return nullptr; }                              // 05
		virtual BSFadeNode* IsFadeNode() { return nullptr; }                                  // 06
		virtual BSMultiBoundNode* IsMultiBoundNode() { return nullptr; }                      // 07
		virtual BSGeometry* IsGeometry() { return nullptr; }                                  // 08
		virtual NiTriStrips* IsTriStrips() { return nullptr; }                                // 09
		virtual BSTriShape* IsTriShape() { return nullptr; }                                  // 0A
		virtual BSDynamicTriShape* IsDynamicTriShape() { return nullptr; }                    // 0B
		virtual BSSegmentedTriShape* IsSegmentedTriShape() { return nullptr; }                // 0C
		virtual BSSubIndexTriShape* IsSubIndexTriShape() { return nullptr; }                  // 0D
		virtual NiGeometry* IsNiGeometry() { return nullptr; }                                // 0E
		virtual NiTriBasedGeom* IsNiTriBasedGeom() { return nullptr; }                        // 0F
		virtual NiTriShape* IsNiTriShape() { return nullptr; }                                // 10
		virtual NiParticles* IsParticlesGeom() { return nullptr; }                            // 11
		virtual NiParticleSystem* IsParticleSystem() { return nullptr; }                      // 12
		virtual BSLines* IsLinesGeom() { return nullptr; }                                    // 13
		virtual NiLight* IsLight() { return nullptr; }                                        // 14
		virtual bhkNiCollisionObject* IsBhkNiCollisionObject() { return nullptr; }            // 15
		virtual bhkBlendCollisionObject* IsBhkBlendCollisionObject() { return nullptr; }      // 16
		virtual bhkRigidBody* IsBhkRigidBody() { return nullptr; }                            // 17
		virtual bhkLimitedHingeConstraint* IsBhkLimitedHingeConstraint() { return nullptr; }  // 18
		virtual bhkNPCollisionObject* IsbhkNPCollisionObject() { return nullptr; }            // 19
		virtual ~NiCullingProcess() { return; }
		virtual void Process(NiAVObject*) { return; }
		virtual void Process2(NiCamera*, NiAVObject*, NiVisibleArray*) { return; }
		virtual void AppendVirtual(BSGeometry&) { return; }

		//members
		const bool m_bUseVirtualAppend{ 0 };
		NiVisibleArray* m_pkVisibleSet{ nullptr };
		NiCamera* m_pkCamera{ nullptr };
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
	};
}
