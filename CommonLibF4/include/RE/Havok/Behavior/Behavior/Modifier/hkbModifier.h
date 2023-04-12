#pragma once
#include "RE/Havok/Behavior/Behavior/Node/hkbNode.h"
#include "RE/Havok/Behavior/Behavior/Generator/hkbGeneratorPartitionInfo.h"

namespace RE
{
	class hkbContext;
	class hkbGeneratorOutput;
	class hkbGeneratorSyncInfo;

		/// An interface to an object that modifies a pose.
	class hkbModifier : public hkbNode
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbModifier };
		static constexpr auto VTABLE{ VTABLE::hkbModifier };

		hkbModifier(hkbNodeType nodeType) :
			hkbNode(nodeType), m_enable(true) {}

	protected:
		hkbModifier(const hkbModifier& mod) :
			hkbNode(mod), m_enable(mod.m_enable) {}

	public:
		/// Modify an output pose and reference frame.  Must be called between calls to activate() and deactivate().
		virtual void modify([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkbGeneratorOutput& inOut) {}

		/// Modify an output pose and reference frame, including a time offset.  Must be called between calls to activate() and deactivate().
		/// Only implement this function if predictive modify actually makes sense.  Also prediction should be stateless, so ensure that predictive
		/// modify does not change the state of the modifier.
		virtual void predictiveModify([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkbGeneratorOutput& inOut, [[maybe_unused]] hkReal timeOffset) {}

		/// Modify the sync info as it passes through this modifier.
		virtual void modifySyncInfo([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkbGeneratorSyncInfo& syncInfo) {}

		/// Modify the sync info as it passes through this modifier.
		virtual void modifyPartitionInfo([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkbGeneratorPartitionInfo& partitionInfo) {}

		///////////////
		// properties
		///////////////

		/// If this is true the modifier will be active.
		hkBool m_enable;  //+default(true)
						  //+hk.Description("If this is true the modifier will be active.")

	private:
		// make the layout test succeed
		hkBool m_padModifier[3];  //+nosave
	};
}
