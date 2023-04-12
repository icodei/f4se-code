#pragma once
#include "RE/Havok/Behavior/Behavior/Generator/hkbGenerator.h"

namespace RE
{
	class hkbContext;
	class hkbGeneratorOutput;
	class hkbEventQueue;
	class hkbStateMachine;

	/// A transition effect between two generators, for example, to blend them.
	///
	/// An hkbTransitionEffect represents a transition over time between one generator and another.
	/// They are used by hkbStateMachines to generate poses when the state machine
	/// transitions between states.
	class hkbTransitionEffect : public hkbGenerator
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbTransitionEffect };
		static constexpr auto VTABLE{ VTABLE::hkbTransitionEffect };

		hkbTransitionEffect(hkbNodeType nodeType);

	protected:
		hkbTransitionEffect(const hkbTransitionEffect& te);

	public:
		/// Sets the generator that is being transitioned from.
		void setFromGenerator(hkbGenerator* fromGen) { m_fromGenerator = fromGen; }

		/// Sets the generator that is being transitioned to.
		void setToGenerator(hkbGenerator* toGen) { m_toGenerator = toGen; }

		/// Gets the generator that is being transitioned from.
		const hkbGenerator* getFromGenerator() const { return m_fromGenerator; }

		/// Gets the generator that is being transitioned to.
		const hkbGenerator* getToGenerator() const { return m_toGenerator; }

		////////////////////////////////////////
		// hkbBindable virtual methods, overridden to facilitate execution in different behavior graphs
		////////////////////////////////////////

		virtual hkBool32 copyVariablesToMembers(hkbSyncVariableSetup& syncVariableSetup, hkbBehaviorGraph& rootBehavior, bool reverse) HK_OVERRIDE;

		virtual void copyVariableToEnable(hkbSyncVariableSetup& syncVariableSetup, hkbBehaviorGraph& rootBehavior) HK_OVERRIDE;

		////////////////////////////////////////
		// hkbTransitionEffect virtual methods
		////////////////////////////////////////

		/// Indicates whether the transition has completed or not.
		virtual bool isDone() = 0;

		/// Indicates how long the transition effect plans to blend out the from-generator.
		///
		/// This is used by the state machine to start transitions just enough in advance of
		/// the end of the from-generator so that it plays until the end during the blend.
		virtual hkReal getFromGeneratorBlendOutTime() = 0;

		/// Indicates how long the transition effect plans to blend in the to-generator.
		///
		/// This is used by applySelfTransitionMode() to decide how long to blend during a self-transition
		/// involving the to-generator.
		virtual hkReal getToGeneratorBlendInTime() = 0;

		/// Called by the state machine when creating the TE.
		/// By default, this information is not stored.
		virtual void setParentStateMachine([[maybe_unused]] const hkbContext& context, [[maybe_unused]] const hkbStateMachine& parentStateMachine) {}

		/// These modes determine the behavior when the to-generator is already active when the transition begins.
		enum SelfTransitionMode
		{
			/// If the to-generator is cyclic, it will be continued without interruption.  Otherwise, it will be
			/// blended with itself using the echo feature.
			SELF_TRANSITION_MODE_CONTINUE_IF_CYCLIC_BLEND_IF_ACYCLIC = 0,

			/// Continue the to-generator without interruption.
			SELF_TRANSITION_MODE_CONTINUE,

			/// Reset the to-generator to the beginning.
			SELF_TRANSITION_MODE_RESET,

			/// Reset the to-generator to the beginning using the echo feature to blend.
			SELF_TRANSITION_MODE_BLEND,
		};

		enum EventMode
		{
			/// Apply the event mode from m_defaultEventMode.
			EVENT_MODE_DEFAULT,

			/// Don't ignore the events of either the from-generator or the to-generator.
			EVENT_MODE_PROCESS_ALL,

			/// Ignore all events sent by or to the from-generator.
			EVENT_MODE_IGNORE_FROM_GENERATOR,

			/// Ignore all events sent by or to the to-generator.
			EVENT_MODE_IGNORE_TO_GENERATOR,
		};

		/// What to do if the to-generator is already active when the transition activates it.
		hkEnum<SelfTransitionMode, hkInt8> m_selfTransitionMode;  //+default(hkbTransitionEffect::SELF_TRANSITION_MODE_CONTINUE_IF_CYCLIC_BLEND_IF_ACYCLIC)
																  //+hk.Description("What to do if the to-generator is already active when the transition activates it.")

		/// How to process the events of the from- and to-generators.
		hkEnum<EventMode, hkInt8> m_eventMode;  //+default(hkbTransitionEffect::EVENT_MODE_DEFAULT)
												//+hk.Description("How to process the events of the from-generator and to-generator.")

	protected:
		// The effective self transition mode depends on the toGenerator (see SELF_TRANSITION_MODE_CONTINUE_IF_CYCLIC_BLEND_IF_ACYCLIC).
		// This function returns either SELF_TRANSITION_MODE_RESET, SELF_TRANSITION_MODE_BLEND, or SELF_TRANSITION_MODE_CONTINUE taking into account
		// the TE mode and the toGenerator's cyclic status.
		SelfTransitionMode computeSelfTransitionMode(const hkbContext& context, hkbGenerator* toGenerator);

		// Apply the selfTransitionMode computed in computeSelfTransitionMode.
		// This should be called only once after the toGenerator has been (re)activated.
		void applySelfTransitionMode(const hkbContext& context, hkbGenerator* toGenerator, SelfTransitionMode selfTransitionMode);

		// return the event mode, applying the default if appropriate
		int getEventMode();

		// The default event mode to use when the event mode of a transition effect is EVENT_MODE_USE_DEFAULT.
		// You should not set this to EVENT_MODE_USE_DEFAULT.
		// Subclasses should set this to hkbProjectData::m_defaultEventMode inside activate().
		hkEnum<hkbTransitionEffect::EventMode, hkInt8> m_defaultEventMode;  //+nosave

		// For internal use only.
		// Overriding binding information; used when this TE is executed in the context of a global transition into a different behavior graph.
		hkRefPtr<hkReferencedObject> m_patchedBindingInfo;  //+nosave

		// The generator that is being transformed from (not reference counted)
		hkbGenerator* m_fromGenerator;  //+nosave

		// The generator that is being transitioned to (not reference counted)
		hkbGenerator* m_toGenerator;  //+nosave

	public:
		// Function for internal use.
		// This function prepares m_patchedBindingInfo to redirect copyVariablesToMembers functions to the proper variables.
		// This is necessary for effects used by global transitions since they are authored in the context of one
		// behavior graph but are executed in another.
		virtual void computePatchedBindings(const hkbContext& context, const hkbBehaviorGraph& referenceBehavior);

		// Function for internal use.
		// Returns if computePatchedBindings has been called
		bool isBorrowedTransitionEffect() { return m_patchedBindingInfo != HK_NULL; }
	};
}
