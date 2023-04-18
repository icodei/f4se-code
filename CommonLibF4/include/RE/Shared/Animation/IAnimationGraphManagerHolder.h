#pragma once
#include "RE/Bethesda/BSCore/BSScrapArray.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"

namespace RE
{
	class NiAVObject;
	class BSAnimationGraphChannel;
	class BSAnimationGraphManager;
	class BShkbAnimationGraph;

	class __declspec(novtable) IAnimationGraphManagerHolder
	{
	public:
		static constexpr auto RTTI{ RTTI::IAnimationGraphManagerHolder };
		static constexpr auto VTABLE{ VTABLE::IAnimationGraphManagerHolder };

		virtual ~IAnimationGraphManagerHolder() = default;  // 00

		// add
		virtual bool NotifyAnimationGraphImpl([[maybe_unused]] const BSFixedString& a_eventName) { return false; }                                                                                                                   // 01
		virtual void EventSuccessfullyProcessed() { return; }                                                                                                                                                                        // 02
		virtual void ModifyInitialAnimationStateImpl(const bool) { return; }                                                                                                                                                         // 03
		virtual bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const = 0;                                                                                                               // 04
		virtual bool SetAnimationGraphManagerImpl(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) = 0;                                                                                                               // 05
		virtual bool PopulateGraphNodesToTarget([[maybe_unused]] BSScrapArray<NiAVObject*>& a_nodesToAnimate) const { return false; }                                                                                                // 06
		virtual bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) = 0;                                                                                                                                 // 07
		virtual bool InitializeAnimationGraphVariables([[maybe_unused]] const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph) const { return true; }                                                                               // 08
		virtual bool SetupAnimEventSinks([[maybe_unused]] const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph) { return true; }                                                                                                   // 09
		virtual void DoFailedToLoadGraph() const { return; }                                                                                                                                                                         // 0A
		virtual bool CreateAnimationChannels([[maybe_unused]] BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>& a_channels) { return false; }                                                                                  // 0B
		virtual void PostCreateAnimationGraphManager([[maybe_unused]] BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) { return; }                                                                                          // 0C
		virtual void PostChangeAnimationManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_newAnimGraphMgr, [[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_oldAnimGraphMgr) { return; }  // 0D
		virtual bool ShouldUpdateAnimation() { return true; }                                                                                                                                                                        // 0E
		virtual std::uint32_t GetGraphVariableCacheSize() const { return 0; }                                                                                                                                                        // 0F
		virtual bool GetGraphVariableImpl([[maybe_unused]] std::uint32_t a_graphVarID, [[maybe_unused]] float& a_out) const { return false; }                                                                                        // 10
		virtual bool GetGraphVariableImpl([[maybe_unused]] std::uint32_t a_graphVarID, [[maybe_unused]] bool& a_out) const { return false; }                                                                                         // 11
		virtual bool GetGraphVariableImpl([[maybe_unused]] std::uint32_t a_graphVarID, [[maybe_unused]] std::int32_t& a_out) const { return false; }                                                                                 // 12
		virtual bool GetGraphVariableImpl([[maybe_unused]] const BSFixedString& a_variable, [[maybe_unused]] float& a_out) const { return false; }                                                                                   // 13
		virtual bool GetGraphVariableImpl([[maybe_unused]] const BSFixedString& a_variable, [[maybe_unused]] std::int32_t& a_out) const { return false; }                                                                            // 14
		virtual bool GetGraphVariableImpl([[maybe_unused]] const BSFixedString& a_variable, [[maybe_unused]] bool& a_out) const { return false; }                                                                                    // 15
		virtual void PreUpdateAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const { return; }                                                                               // 16
		virtual void PostUpdateAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const { return; }                                                                              // 17
		virtual void PreLoadAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) { return; }                                                                                       // 18
		virtual void PostLoadAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) { return; }                                                                                      // 19

		bool SetGraphVariableBool(const BSFixedString& asVariableName, bool newVal)
		{
			using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableBool);
			REL::Relocation<func_t> func{ REL::ID(1437197) };
			return func(this, asVariableName, newVal);
		}
		bool SetGraphVariableInt(const BSFixedString& asVariableName, int newVal)
		{
			using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableInt);
			REL::Relocation<func_t> func{ REL::ID(732926) };
			return func(this, asVariableName, newVal);
		}
		bool SetGraphVariableFloat(const BSFixedString& asVariableName, float newVal)
		{
			using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableFloat);
			REL::Relocation<func_t> func{ REL::ID(27400) };
			return func(this, asVariableName, newVal);
		}
		bool SetGraphVariableNiPoint3(const BSFixedString& asVariableName, NiPoint3 newVal)
		{
			using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableNiPoint3);
			REL::Relocation<func_t> func{ REL::ID(905324) };
			return func(this, asVariableName, newVal);
		}
		bool SetGraphVariableNiQuaternion(const BSFixedString& asVariableName, NiQuaternion newVal)
		{
			using func_t = decltype(&IAnimationGraphManagerHolder::SetGraphVariableNiQuaternion);
			REL::Relocation<func_t> func{ REL::ID(1343874) };
			return func(this, asVariableName, newVal);
		}
	};
	static_assert(sizeof(IAnimationGraphManagerHolder) == 0x8);

	
}
