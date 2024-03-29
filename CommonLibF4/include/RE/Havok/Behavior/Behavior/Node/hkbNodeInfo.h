#pragma once

namespace RE
{
	class hkbNode;
	class hkbBehaviorGraph;

		/// Stores returned info about a child of a node.
	struct hkbNodeChildInfo
	{

		hkbNodeChildInfo() :
			m_node(HK_NULL),
			m_nodeClone(HK_NULL),
			m_ignoreEvents(false),
			m_reset(false),
			m_syncToParent(false),
			m_stopped(false)
		{
		}

		/// The child node template.
		hkbNode* m_node;

		/// The child node clone.
		hkbNode* m_nodeClone;

		/// If true, events will not be sent to the nodes and events generated by the node will
		/// not be forwarded.
		hkBool m_ignoreEvents;

		/// Whether to reset the node asap (deactivate and then activate).
		hkBool m_reset;

		/// Whether or not to synchronize this node with the parent.
		hkBool m_syncToParent;

		/// Whether or not the parent wants this child to be moved forward in time.
		hkBool m_stopped;
	};

	/// Information about a node in a behavior graph.
	struct hkbNodeInfo
	{
		enum Flags
		{
			FLAG_NONE = 0,

			/// If true, events will not be sent to the nodes and events generated by the node will not be forwarded.
			FLAG_IGNORE_EVENTS = 1,

			/// Whether the node is a generator or a modifier.
			FLAG_IS_GENERATOR = 1 << 1,

			/// Whether or not to sync this node to the parent.
			FLAG_SYNC_TO_PARENT = 1 << 2,

			/// True if ALL parents want this node to not progress in time.
			FLAG_STOPPED = 1 << 3,

			/// Whether activate() has been called on the node or not.
			FLAG_HAS_ACTIVATE_BEEN_CALLED = 1 << 4,

			/// This is used during traversals to avoid traversing the same node twice.
			/// It must be reset to false after any traversal that changes it to true.
			FLAG_TOUCHED = 1 << 5,

			/// Modifiers are activated preemptively and then this flag is used to keep track of
			/// when changes to m_enable have been noticed.
			FLAG_IS_MODIFIER_ENABLED = 1 << 6,
		};

		/// The node template (pre-clone).
		hkbNode*  m_nodeTemplate;

		/// The clone of m_nodeTemplate for this node.
		hkbNode*  m_nodeClone;

		/// The behavior that this node is inside.
		hkbBehaviorGraph*  m_behavior;
		
		/// The rootwardmost parent of the node.
		hkbNode*  m_rootwardmostParentClone;
		
		/// This parent is used for computing the timestep of this node based on synchronization or speed.
		hkbNode*  m_parentClone;
		
		/// The currently active children.
		hkArray<hkbNodeChildInfo> m_activeChildren;
		
		/// The index of this node in the master list of active nodes (hkbBehaviorGraph::m_activeNodes).
		hkInt16 m_index;
		
		/// The number of parents of the node.
		hkUint8 m_numParents;
		
		/// This is used during generate() to count down the number of remaining parents so we know
		/// when this node's output is no longer needed.
		hkUint8 m_countParents;
		
		hkFlags<hkbNodeInfo::Flags, hkInt8> m_flags;
	};
}
