#pragma once
#include "RE/Havok/Behavior/Behavior/Event/hkbEvent.h"
#include "RE/Havok/Behavior/Behavior/Node/hkbBindable.h"
#include "RE/Havok/Behavior/Behavior/Node/hkbNodeInfo.h"
#include "RE/Havok/Common/Base/Container/PointerMap/hkPointerMap.h"

namespace RE
{
	/// An enumeration of some of the Behavior node types.
	/// Some deprecated nodes have type HKB_NODE_TYPE_OTHER_GENERATOR or HKB_NODE_TYPE_OTHER_MODIFIER.
	enum hkbNodeType
	{
		HKB_NODE_TYPE_INVALID = 0,

		// Generators - must be contiguous and include Transition Effects, which must also be contiguous.
		HKB_NODE_TYPE_FIRST_GENERATOR,
		HKB_NODE_TYPE_BEHAVIOR_GRAPH = HKB_NODE_TYPE_FIRST_GENERATOR,
		HKB_NODE_TYPE_BEHAVIOR_REFERENCE_GENERATOR,
		HKB_NODE_TYPE_BLENDER_GENERATOR,
		HKB_NODE_TYPE_CLIP_GENERATOR,
		HKB_NODE_TYPE_MANUAL_SELECTOR_GENERATOR,
		HKB_NODE_TYPE_MODIFIER_GENERATOR,
		HKB_NODE_TYPE_REFERENCE_POSE_GENERATOR,
		HKB_NODE_TYPE_STATE_MACHINE,
		HKB_NODE_TYPE_SCRIPT_GENERATOR,
		HKB_NODE_TYPE_LAYER_GENERATOR,

		// You can add your own custom generator types here if you implement them on SPU.
		// You must also update hkbSpuBehaviorUtils::s_generatorSize.
		// HKB_NODE_TYPE_USER_SPU_GENERATOR_0,

		HKB_NODE_TYPE_END_OF_SPU_GENERATORS,

		// the rest of the generators don't run on SPU

		HKB_NODE_TYPE_DOCKING_GENERATOR = HKB_NODE_TYPE_END_OF_SPU_GENERATORS,
		HKB_NODE_TYPE_PARAMETRIC_MOTION_GENERATOR,
		HKB_NODE_TYPE_PIN_BONE_GENERATOR,
		HKB_NODE_TYPE_OTHER_GENERATOR,

		// This is where you can define your custom generator types if they don't run on SPU.
		// HKB_NODE_TYPE_USER_GENERATOR_0
		HKB_NODE_TYPE_BS_GAMEBRYO_SEQUENCE_GENERATOR,
		HKB_NODE_TYPE_BS_CYCLIC_TRANSITION_GENERATOR,
		HKB_NODE_TYPE_BS_BONE_SWITCH_GENERATOR,
		HKB_NODE_TYPE_BS_OFFSET_ANIMATION_GENERATOR,
		HKB_NODE_TYPE_BS_SYNCHRONIZED_CLIP_GENERATOR,
		HKB_NODE_TYPE_BS_ISTATE_TAGGING_GENERATOR,
		HKB_NODE_TYPE_BS_DYNAMIC_ANIMATION_TAGGING_GENERATOR,
		HKB_NODE_TYPE_BS_BEHAVIOR_GRAPH_SWAP_GENERATOR,
		HKB_NODE_TYPE_BS_RETARGET_BODY_BLEND_GENERATOR,

		// Transition Effects (they are also generators) - Must be contiguous.
		HKB_NODE_TYPE_FIRST_TRANSITION_EFFECT = 48,
		HKB_NODE_TYPE_BLENDING_TRANSITION_EFFECT = HKB_NODE_TYPE_FIRST_TRANSITION_EFFECT,
		HKB_NODE_TYPE_GENERATOR_TRANSITION_EFFECT,

		// You can add your own custom transition effect types here if you implement them on SPU.
		// You must also update hkbSpuBehaviorUtils::s_transitionEffectSize.
		// HKB_NODE_TYPE_USER_SPU_TRANSITION_EFFECT_0,

		HKB_NODE_TYPE_END_OF_SPU_TRANSITION_EFFECTS,

		// The rest of the transition effects don't run on SPU.

		HKB_NODE_TYPE_MANUAL_SELECTOR_TRANSITION_EFFECT = HKB_NODE_TYPE_END_OF_SPU_TRANSITION_EFFECTS,

		// This is where you can define your custom transition effect types if they don't run on SPU.
		// HKB_NODE_TYPE_USER_TRANSITION_EFFECT_0

		// Modifiers - Must be contiguous.
		HKB_NODE_TYPE_FIRST_MODIFIER = 64,
		HKB_NODE_TYPE_ATTACHMENT_MODIFIER = HKB_NODE_TYPE_FIRST_MODIFIER,
		HKB_NODE_TYPE_ATTRIBUTE_MODIFIER,
		HKB_NODE_TYPE_CHARACTER_CONTROLLER_MODIFIER,
		HKB_NODE_TYPE_COMBINE_TRANSFORMS_MODIFIER,
		HKB_NODE_TYPE_COMPUTE_DIRECTION_MODIFIER,
		HKB_NODE_TYPE_COMPUTE_ROTATION_FROM_AXIS_ANGLE_MODIFIER,
		HKB_NODE_TYPE_COMPUTE_ROTATION_TO_TARGET_MODIFIER,
		HKB_NODE_TYPE_DAMPING_MODIFIER,
		HKB_NODE_TYPE_DELAYED_MODIFIER,
		HKB_NODE_TYPE_EVALUATE_EXPRESSION_MODIFIER,
		HKB_NODE_TYPE_EVENTS_FROM_RANGE_MODIFIER,
		HKB_NODE_TYPE_EVENT_DRIVEN_MODIFIER,
		HKB_NODE_TYPE_FOOT_IK_CONTROLS_MODIFIER,
		HKB_NODE_TYPE_GET_WORLD_FROM_MODEL_MODIFIER,
		HKB_NODE_TYPE_HAND_IK_CONTROLS_MODIFIER,
		HKB_NODE_TYPE_KEYFRAME_BONES_MODIFIER,
		HKB_NODE_TYPE_LOOK_AT_MODIFIER,
		HKB_NODE_TYPE_MIRROR_MODIFIER,
		HKB_NODE_TYPE_MODIFIER_LIST,
		HKB_NODE_TYPE_MOVE_BONE_ATTACHMENT_MODIFIER,
		HKB_NODE_TYPE_MOVE_CHARACTER_MODIFIER,
		HKB_NODE_TYPE_POWERED_RAGDOLL_CONTROLS_MODIFIER,
		HKB_NODE_TYPE_RIGID_BODY_RAGDOLL_CONTROLS_MODIFIER,
		HKB_NODE_TYPE_ROTATE_CHARACTER_MODIFIER,
		HKB_NODE_TYPE_SET_WORLD_FROM_MODEL_MODIFIER,
		HKB_NODE_TYPE_TIMER_MODIFIER,
		HKB_NODE_TYPE_TRANSFORM_VECTOR_MODIFIER,
		HKB_NODE_TYPE_TWIST_MODIFIER,

		// You can add your own custom modifier types here if you implement them on SPU.
		// You must also update hkbSpuBehaviorUtils::s_modifierSize.
		// HKB_NODE_TYPE_USER_SPU_MODIFIER_0,

		HKB_NODE_TYPE_END_OF_SPU_MODIFIERS,

		// the rest of the modifiers don't run on SPU

		HKB_NODE_TYPE_DETECT_CLOSE_TO_GROUND_MODIFIER = HKB_NODE_TYPE_END_OF_SPU_MODIFIERS,
		HKB_NODE_TYPE_EVALUATE_HANDLE_MODIFIER,
		HKB_NODE_TYPE_GET_HANDLE_ON_BONE_MODIFIER,
		HKB_NODE_TYPE_GET_UP_MODIFIER,
		HKB_NODE_TYPE_JIGGLER_MODIFIER,
		HKB_NODE_TYPE_SENSE_HANDLE_MODIFIER,
		HKB_NODE_TYPE_SEQUENCE,
		HKB_NODE_TYPE_AI_STEERING_MODIFIER,
		HKB_NODE_TYPE_AI_CONTROL_MODIFIER,
		HKB_NODE_TYPE_ROCKETBOX_CHARACTER_CONTROLLER_MODIFIER,
		HKB_NODE_TYPE_LEAN_ROCKETBOX_CHARACTER_CONTROLLER_MODIFIER,
		HKB_NODE_TYPE_OTHER_MODIFIER,

		// This is where you can define your custom modifier types if they don't run on SPU.
		// HKB_NODE_TYPE_USER_MODIFIER_0
		HKB_NODE_TYPE_BS_COMPUTE_ADD_BONE_ANIM,
		HKB_NODE_TYPE_BS_DECOMPOSE_VECTOR,
		HKB_NODE_TYPE_BS_DIRECT_AT,
		HKB_NODE_TYPE_BS_DIST_TRIGGER,
		HKB_NODE_TYPE_BS_EVENT_EVERY_N_EVENTS,
		HKB_NODE_TYPE_BS_EVENT_ON_DEACTIVATE,
		HKB_NODE_TYPE_BS_EVENT_ON_FALSE_TO_TRUE,
		HKB_NODE_TYPE_BS_GET_TIME_STEP,
		HKB_NODE_TYPE_BS_INTERP_VALUE,
		HKB_NODE_TYPE_BS_IS_ACTIVE,
		HKB_NODE_TYPE_BS_ISTATE_MANAGER,
		HKB_NODE_TYPE_BS_LIMB_IK,
		HKB_NODE_TYPE_BS_LOOK_AT,
		HKB_NODE_TYPE_BS_MODIFY_ONCE,
		HKB_NODE_TYPE_BS_PASS_BY_TARGET_TRIGGER,
		HKB_NODE_TYPE_BS_RAGDOLL_CONTACT_LISTENER,
		HKB_NODE_TYPE_BS_REVERSE_SPINE_TWIST,
		HKB_NODE_TYPE_BS_ROOT_TWIST,
		HKB_NODE_TYPE_BS_SPEED_SAMPLER,
		HKB_NODE_TYPE_BS_TIMER,
		HKB_NODE_TYPE_BS_TWEENER,
		HKB_NODE_TYPE_BS_ASSIGN_VARIABLE,
		HKB_NODE_TYPE_BS_ALIGN_BONE,
		HKB_NODE_TYPE_BS_LIMB_CYCLE,
		HKB_NODE_TYPE_BS_LOOKAT_CAPTURE_POSE,
		HKB_NODE_TYPE_BS_DIRECTAT_CAPTURE_POSE,
		HKB_NODE_TYPE_BS_RANDOM_ALARM,
	};

	class hkbNode : public hkbBindable
	{
	public:

		static constexpr auto RTTI{ RTTI::hkbNode };
		static constexpr auto VTABLE{ VTABLE::hkbNode };

			/// Construct a node with no name.
		hkbNode(hkbNodeType nodeType);

	protected:
		hkbNode(const hkbNode& node);

	public:
		/// Performs initialization.
		///
		/// This method must be called before any calls to update(), or handleEvent(),
		/// hkbGenerator::generate(), or hkbModifier::modify().
		/// Typically, a call to activate() is followed by several calls to update(), handleEvent(),
		/// hkbGenerator::generate(), or hkbModifier::modify(), and then a call to deactivate().
		///
		/// Do not call this method directly.  Use hkbBehaviorGraph::activate().
		/// The base class implementation does nothing.
		virtual void activate([[maybe_unused]] const hkbContext& context) {}

		/// Advance time and generate events.
		///
		/// Can only be called between calls to activate() and deactivate().
		///
		/// Do not call this method directly.  Use hkbBehaviorGraph::update().
		/// The base class implementation does nothing.
		virtual void update([[maybe_unused]] const hkbContext& context, [[maybe_unused]] hkReal timestep) {}

		/// Handle events that are raised.
		///
		/// Can only be called between calls to activate() and deactivate().
		///
		/// Do not call this method directly.  Use hkbBehaviorGraph::handleEvent().
		/// The base class implementation does nothing.
		virtual void handleEvent([[maybe_unused]] const hkbContext& context, [[maybe_unused]] const hkbEvent e) {}

		/// Clean up.
		///
		/// Do not call this method directly.  Use hkbBehaviorGraph::deactivate().
		virtual void deactivate([[maybe_unused]] const hkbContext& context) {}

		/// Flags used when calling GenNumChildren() or GetChildren().
		enum GetChildrenFlagBits
		{
			/// If true, only return the active children (otherwise, all children).
			FLAG_ACTIVE_ONLY = (1 << 0),

			/// If true, only return generators (else also return modifiers).
			FLAG_GENERATORS_ONLY = (1 << 2),

			/// If true, the behavior graphs pointed to by hkbBehaviorReferenceGenerators
			/// will be ignored (along with all of their descendants).
			FLAG_IGNORE_REFERENCED_BEHAVIORS = (1 << 3),
		};

		/// An integer type for storing combinations of GetChildrenFlagsBits.
		typedef int GetChildrenFlags;

		/// Stores returned info about the children of a node.
		struct ChildrenInfo
		{

			/// An array of child info (must be allocated by the caller).
			hkArray<hkbNodeChildInfo>& m_childInfos;
		};

	protected:
		// Used for harvesting variables from hkbBindables.
		class BoundVariablesCollector : public hkbBindableCollector
		{
		public:
			virtual void collectBindable(hkbBindable* bindable) HK_OVERRIDE;

			// Collected variable IDs are put into this map.
			hkPointerMap<int, bool>* m_variablesMap;
		};

	public:
		/// You can use this for whatever you want.
		hkUlong m_userData;	//+hkb.RoleAttribute("ROLE_DEFAULT","FLAG_HIDDEN")

		// The name of the node.
		hkStringPtr m_name;	//+hkb.RoleAttribute("ROLE_DEFAULT","FLAG_HIDDEN")
		
		// An ID that is unique among all nodes in a behavior graph including all
		// nested graphs.
		hkUint16 m_id;	//+nosave
		
		enum CloneState
		{
			/// This node is neither a clone nor a template.  This is the initial m_cloneState.  It indicates
			/// that the node has not been cloned.  If you are not using cloning the nodes will have this state.
			/// If you are using cloning, all nodes should have their state changed from this at some point as they
			/// get cloned.
			CLONE_STATE_DEFAULT,

			/// This node is a template that should not be used directly.
			CLONE_STATE_TEMPLATE,

			/// This node is a clone that can be used.
			CLONE_STATE_CLONE,
		};

			/// This is used in some templates that work differently if the node is a template vs clone.
		enum TemplateOrClone
		{
			NODE_IS_TEMPLATE,
			NODE_IS_CLONE,
		};

	protected:
		// whether this is a clone, template, or sharable node
		hkEnum<hkbNode::CloneState, hkInt8> m_cloneState;  //+nosave
		
		// the type of this node
		hkEnum<hkbNodeType, hkUint8> m_type;	//+nosave
		
		// this is HK_NULL iff the node is active
		hkbNodeInfo* m_nodeInfo;	//+nosave
	};
}
