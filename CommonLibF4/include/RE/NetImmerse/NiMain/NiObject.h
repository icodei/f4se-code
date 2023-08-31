#pragma once

#include "RE/NetImmerse/NiMain/NiRefObject.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

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
	class NiCloningProcess;
	class NiControllerManager;
	class NiGeometry;
	class NiLight;
	class NiNode;
	class NiObjectGroup;
	class NiParticles;
	class NiParticleSystem;
	class NiStream;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;

	struct NiRTTI;

	class __declspec(novtable) NiObject :
		public NiRefObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiObject };
		static constexpr auto VTABLE{ VTABLE::NiObject };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiObject };

		NiObject() { stl::emplace_vtable(this); }
		virtual ~NiObject() = default;  // NOLINT(modernize-use-override) 00

		// add
		virtual const NiRTTI* GetRTTI() const { return nullptr; }                                          // 02
		virtual const NiNode* IsConstNode() const { return nullptr; }                                      // 03
		virtual NiNode* IsNode() { return nullptr; }                                                       // 04
		virtual NiSwitchNode* IsSwitchNode() { return nullptr; }                                           // 05
		virtual BSFadeNode* IsFadeNode() { return nullptr; }                                               // 06
		virtual BSMultiBoundNode* IsMultiBoundNode() { return nullptr; }                                   // 07
		virtual BSGeometry* IsGeometry() { return nullptr; }                                               // 08
		virtual NiTriStrips* IsTriStrips() { return nullptr; }                                             // 09
		virtual BSTriShape* IsTriShape() { return nullptr; }                                               // 0A
		virtual BSDynamicTriShape* IsDynamicTriShape() { return nullptr; }                                 // 0B
		virtual BSSegmentedTriShape* IsSegmentedTriShape() { return nullptr; }                             // 0C
		virtual BSSubIndexTriShape* IsSubIndexTriShape() { return nullptr; }                               // 0D
		virtual NiGeometry* IsNiGeometry() { return nullptr; }                                             // 0E
		virtual NiTriBasedGeom* IsNiTriBasedGeom() { return nullptr; }                                     // 0F
		virtual NiTriShape* IsNiTriShape() { return nullptr; }                                             // 10
		virtual NiParticles* IsParticlesGeom() { return nullptr; }                                         // 11
		virtual NiParticleSystem* IsParticleSystem() { return nullptr; }                                   // 12
		virtual BSLines* IsLinesGeom() { return nullptr; }                                                 // 13
		virtual NiLight* IsLight() { return nullptr; }                                                     // 14
		virtual bhkNiCollisionObject* IsBhkNiCollisionObject() { return nullptr; }                         // 15
		virtual bhkBlendCollisionObject* IsBhkBlendCollisionObject() { return nullptr; }                   // 16
		virtual bhkRigidBody* IsBhkRigidBody() { return nullptr; }                                         // 17
		virtual bhkLimitedHingeConstraint* IsBhkLimitedHingeConstraint() { return nullptr; }               // 18
		virtual bhkNPCollisionObject* IsbhkNPCollisionObject() { return nullptr; }                         // 19
		virtual NiObject* CreateClone([[maybe_unused]] NiCloningProcess& a_cloneData) { return nullptr; }  // 1A
		virtual void LoadBinary([[maybe_unused]] NiStream& a_stream) { return; }                           // 1B
		virtual void LinkObject([[maybe_unused]] NiStream& a_stream) { return; }                           // 1C
		virtual bool RegisterStreamables([[maybe_unused]] NiStream& a_stream) { return false; }            // 1D
		virtual void SaveBinary([[maybe_unused]] NiStream& a_stream) { return; }                           // 1E
		virtual bool IsEqual([[maybe_unused]] NiObject* a_object) { return false; }                        // 1F
		virtual void ProcessClone([[maybe_unused]] NiCloningProcess& a_cloning) { return; }                // 20
		virtual void PostLinkObject([[maybe_unused]] NiStream& a_stream) { return; }                       // 21
		virtual bool StreamCanSkip() { return false; }                                                     // 22
		virtual const NiRTTI* GetStreamableRTTI() { return GetRTTI(); }                                    // 23
		virtual std::uint32_t GetBlockAllocationSize() const { return 0; }                                 // 24
		virtual NiObjectGroup* GetGroup() const { return nullptr; }                                        // 25
		virtual void SetGroup([[maybe_unused]] NiObjectGroup* a_group) { return; }                         // 26
		virtual NiControllerManager* IsNiControllerManager() { return nullptr; }                           // 27

		NiObject* DynamicCast(const NiRTTI* type) const
		{
			using func_t = decltype(&NiObject::DynamicCast);
			REL::Relocation<func_t> func{ REL::ID(80812) };
			return func(this, type);
		}

		NiObject* Clone(void)
		{
			using func_t = decltype(&NiObject::Clone);
			REL::Relocation<func_t> func{ REL::ID(604942) };
			return func(this);
		}

		NiObject* CloneParam(NiCloningProcess& a_process)
		{
			using func_t = decltype(&NiObject::CloneParam);
			REL::Relocation<func_t> func{ REL::ID(418201) };
			return func(this, a_process);
		}

		NiObject* CreateSharedClone(NiCloningProcess& a_process)
		{
			using func_t = decltype(&NiObject::CreateSharedClone);
			REL::Relocation<func_t> func{ REL::ID(1029727) };
			return func(this, a_process);
		}

		NiObject* CreateDeepCopy(NiPointer<NiObject>& a_object)
		{
			using func_t = decltype(&NiObject::CreateDeepCopy);
			REL::Relocation<func_t> func{ REL::ID(750380) };
			return func(this, a_object);
		}

		F4_HEAP_REDEFINE_NEW(NiObject);
	};
	static_assert(sizeof(NiObject) == 0x10);
}
