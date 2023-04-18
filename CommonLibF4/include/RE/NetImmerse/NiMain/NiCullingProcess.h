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
		virtual const NiRTTI* GetRTTI() const { return nullptr; }                             // 00
		virtual const NiNode* IsConstNode() const { return nullptr; }                         // 01
		virtual NiNode* IsNode() { return nullptr; }                                          // 02
		virtual NiSwitchNode* IsSwitchNode() { return nullptr; }                              // 03
		virtual BSFadeNode* IsFadeNode() { return nullptr; }                                  // 04
		virtual BSMultiBoundNode* IsMultiBoundNode() { return nullptr; }                      // 05
		virtual BSGeometry* IsGeometry() { return nullptr; }                                  // 06
		virtual NiTriStrips* IsTriStrips() { return nullptr; }                                // 07
		virtual BSTriShape* IsTriShape() { return nullptr; }                                  // 08
		virtual BSDynamicTriShape* IsDynamicTriShape() { return nullptr; }                    // 09
		virtual BSSegmentedTriShape* IsSegmentedTriShape() { return nullptr; }                // 0A
		virtual BSSubIndexTriShape* IsSubIndexTriShape() { return nullptr; }                  // 0B
		virtual NiGeometry* IsNiGeometry() { return nullptr; }                                // 0C
		virtual NiTriBasedGeom* IsNiTriBasedGeom() { return nullptr; }                        // 0D
		virtual NiTriShape* IsNiTriShape() { return nullptr; }                                // 0E
		virtual NiParticles* IsParticlesGeom() { return nullptr; }                            // 0F
		virtual NiParticleSystem* IsParticleSystem() { return nullptr; }                      // 10
		virtual BSLines* IsLinesGeom() { return nullptr; }                                    // 11
		virtual NiLight* IsLight() { return nullptr; }                                        // 12
		virtual bhkNiCollisionObject* IsBhkNiCollisionObject() { return nullptr; }            // 13
		virtual bhkBlendCollisionObject* IsBhkBlendCollisionObject() { return nullptr; }      // 14
		virtual bhkRigidBody* IsBhkRigidBody() { return nullptr; }                            // 15
		virtual bhkLimitedHingeConstraint* IsBhkLimitedHingeConstraint() { return nullptr; }  // 16
		virtual bhkNPCollisionObject* IsbhkNPCollisionObject() { return nullptr; }            // 17
		virtual ~NiCullingProcess() { return; }                                               // 18
		virtual void Process(NiAVObject*) { return; }										  // 19
		virtual void Process2(NiCamera*, NiAVObject*, NiVisibleArray*) { return; }			  // 1A
		virtual void AppendVirtual(BSGeometry&) { return; }									  // 1B

		//members
		const bool m_bUseVirtualAppend{ 0 };
		NiVisibleArray* m_pkVisibleSet{ nullptr };
		NiCamera* pkCamera{ nullptr };
		NiFrustum m_kFrustum;
		NiFrustumPlanes m_kPlanes;
		NiFrustumPlanes kCustomCullPlanes;
		bool bCameraRelatedUpdates;
		bool bUpdateAccumulateFlag;
		bool bIgnorePreprocess;
		bool bCustomCullPlanes;

	private:
		NiCullingProcess* ctor(NiVisibleArray* a_array)
		{
			using func_t = decltype(&NiCullingProcess::ctor);
			REL::Relocation<func_t> func{ REL::ID(12355) };
			return func(this, a_array);
		}
	};
}
