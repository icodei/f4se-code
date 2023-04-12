#pragma once
#include "RE/Havok/Behavior/Behavior/Node/hkbNode.h"
#include "RE/Havok/Behavior/Behavior/Generator/hkbGeneratorSyncInfo.h"
#include "RE/Havok/Behavior/Behavior/Generator/hkbGeneratorPartitionInfo.h"
#include "RE/Havok/Animation/Animation/Rig/hkaSkeleton.h"

namespace RE
{
	class hkbGeneratorOutput;
	class hkaMirroredSkeleton;

	/// A base class for the principal node types that make up a behavior graph.
	///
	/// An hkbGenerator generates animation poses over time, along with other track data.
	class hkbGenerator : public hkbNode
	{
	public:

		static constexpr auto RTTI{ RTTI::hkbGenerator };
		static constexpr auto VTABLE{ VTABLE::hkbGenerator };

		hkbGenerator(hkbNodeType nodeType) :
			hkbNode(nodeType), m_syncInfo(HK_NULL) {}
		~hkbGenerator();

		/// Generate an output pose and reference frame.
		///
		/// Must be called between calls to activate() and deactivate().
		/// Do not call this method directly.  Use hkbBehaviorGraph::generate().
		virtual void generate(const hkbContext& context,
			const hkbGeneratorOutput** activeChildrenOutput,
			hkbGeneratorOutput& output,
			hkReal timeOffset = 0.0f) const = 0;

		/// Whether or not the generator can handle the situation where one of the
		/// activeChildrenOutputs passed to generate() is the same address as the output argument.
		///
		/// Nodes that can recycle their output can be handled more efficiently.  See the implementation
		/// of hkbModifierGenerator for an example.
		virtual bool canRecycleOutput() const;

		/// Computes the synchronization info for the generator based on the previously
		/// computed synchronization info of the children.
		virtual void updateSync([[maybe_unused]] const hkbContext& context);

		/// Set the time of the generator.
		///
		/// Do not call this method directly.  It is called by hkbBehaviorGraph::setActiveGeneratorLocalTime().
		virtual void setLocalTime([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkReal seconds);

		/// Start an echo for self-transition.  This is for internal use.
		virtual void startEcho([[maybe_unused]] hkReal echoDuration) {}

		/// Called in root-first order on all of the active generators before update() is called on any node.
		virtual void preUpdate([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkReal timestep) {}

		/// Computes the partition info for this generator. Use the default implementation for generators that are leafs
		/// or with generators that have all the children that are generators.
		virtual void computePartitionInfo([[maybe_unused]] const hkArray<hkbNodeChildInfo>& activeChildren, [[maybe_unused]] const hkbContext& context);

		/// Returns m_syncInfo and creates it if necessary.
		hkbGeneratorSyncInfo& accessSyncInfo();

		/// Returns m_syncInfo.
		const hkbGeneratorSyncInfo& getSyncInfo() const;

		/// Delete m_syncInfo.
		void discardSyncInfo();

		/// Returns beginning of the m_partitionIndices array.
		hkbGeneratorPartitionInfo& accessPartitionInfo();

		/// Returns beginning of the m_partitionIndices array.
		const hkbGeneratorPartitionInfo& getPartitionInfo() const;

		hkbGeneratorPartitionInfo m_partitionInfo;  //+nosave

		hkbGeneratorSyncInfo* m_syncInfo;  //+nosave

		// make the layout test succeed
		hkInt8 m_pad[4];  //+nosave
	};
}
