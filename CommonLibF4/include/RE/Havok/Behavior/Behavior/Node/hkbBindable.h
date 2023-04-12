#pragma once
#include "RE/Havok/Behavior/Behavior/Variables/hkbVariableBindingSet.h"
#include "RE/Havok/Common/Base/Types/hkBaseDefs.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"
#include "RE/Havok/Common/Base/Types/hkRefPtr.h"

namespace RE
{
	class hkbBindable;
	class hkbBehaviorGraph;
	struct hkbSyncVariableSetup;

	/// An abstract class for collecting hkbBindables.
	class __declspec(novtable) hkbBindableCollector
	{
	public:

		static constexpr auto RTTI{ RTTI::hkbBindableCollector };
		static constexpr auto VTABLE{ VTABLE::hkbBindableCollector };

		/// Called on each hkbBindable when you pass this collector into hkbBindable::collectBindables().
		virtual void collectBindable(hkbBindable* bindable) = 0;

		virtual ~hkbBindableCollector() {}
	};

	/// An object that can be bound to behavior variables.
	class hkbBindable : public hkReferencedObject
	{
	public:
		
		static constexpr auto RTTI{ RTTI::hkbBindable };
		static constexpr auto VTABLE{ VTABLE::hkbBindable };

		hkbBindable();
		~hkbBindable();

		/// Collect this bindable and all of its child bindables.
		/// Override this if your object points to hkbBindables that it owns,
		/// in which case it should recur on all of the children.
		virtual void collectBindables(hkbBindableCollector& collector);

		/// Copy variables to properties, or vice-versa.
		/// Returns whether or not there are any output bindings.
		virtual hkBool32 copyVariablesToMembers(hkbSyncVariableSetup& syncVariableSetup, hkbBehaviorGraph& rootBehavior, bool reverse);

		/// Copies the variable that is bound to the m_enable member, if there is one.
		virtual void copyVariableToEnable(hkbSyncVariableSetup& syncVariableSetup, hkbBehaviorGraph& rootBehavior);

		/// Set the bindings from variables to this node.
		void setVariableBindings(hkbVariableBindingSet* bindings);

		/// Get the bindings from variables to this node.
		hkbVariableBindingSet* getVariableBindings() const;

		/// Whether there are any bindings to this node.
		bool hasBindings() const;

		/// Whether an m_enable member of this bindable has changed since the last call to clearHasEnableChanged().
		bool hasEnableChanged() const;

		/// Inform this bindable that m_enable has changed.
		void orHasEnableChanged(bool b);

		/// Set m_hasEnableChanged to false indicating that the bindable is up to date.
		void clearHasEnableChanged();

	private:
		// Builds the cache of nested bindables.
		void cacheBindables();

		// the variable bindings
		hkRefPtr<hkbVariableBindingSet> m_variableBindingSet;

		// Used by cacheBindables() to process all hkbBindables.
		class __declspec(novtable) CacheBindablesCollector : public hkbBindableCollector
		{
		public:
			virtual void collectBindable(hkbBindable* bindable) HK_OVERRIDE;

			hkbBindable* m_rootBindable;
		};

		// A cache of all of the nested bindables that have bindings.
		// Note that this bindable is excluded from its own cache because
		// the common case is no nested bindables, and so we won't waste the
		// array memory and extra cache miss in accessing it.
		hkArray<hkbBindable*> m_cachedBindables;  //+nosave

		// Whether the bindables have been cached yet.
		hkBool m_areBindablesCached;  //+nosave

		// Whether a binding to an m_enable member has changed recently.
		hkBool m_hasEnableChanged;  //+nosave

	public:
		
		friend class hkbTransitionEffect;
	};
}
