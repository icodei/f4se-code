#pragma once
#include "RE/Havok/Behavior/Behavior/Variables/hkbVariableValue.h"
#include "RE/Havok/Common/Base/Container/String/hkStringPtr.h"
#include "RE/Havok/Common/Base/Reflection/hkClass.h"
#include "RE/Havok/Common/Base/Types/hkBaseDefs.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"

namespace RE
{
	class hkbBehaviorGraph;
	class hkbBindable;
	class hkbContext;
	struct hkbSyncVariableSetup;

	/// A set of bindings from variables to object properties.
	class hkbVariableBindingSet : public hkReferencedObject
	{
	public:
		//+version(2)
		//+vtable(1)

		/// Create an empty set of variable bindings.
		hkbVariableBindingSet();

		virtual ~hkbVariableBindingSet();

		/// Copy variable values into the bound objects.
		///
		/// If reverse is true, the values are copied into the variables from the bound objects,
		void copyVariablesToMembers(hkbSyncVariableSetup& syncVariableSetup,
			bool reverse,
			hkbBindable* bindable,
			hkbBehaviorGraph* rootBehavior);

		/// Copies the variable bound to the m_enable property.  You must check that there is one first
		/// by calling getIndexOfBindingToEnable() and checking that it is not -1.
		void copyVariableToEnable(hkbSyncVariableSetup& syncVariableSetup,
			hkbBindable* bindable,
			hkbBehaviorGraph* rootBehavior);

		/// A binding between a variable and an object member.
		struct __declspec(novtable) Binding
		{
			//+version(1)

			friend class hkbVariableBindingSet;

		public:
			/// Construct with defaults.
			Binding();

			/// Which data we are binding to.
			enum BindingType
			{
				/// Binding to a variable.
				BINDING_TYPE_VARIABLE,

				/// Binding to a character property.
				BINDING_TYPE_CHARACTER_PROPERTY,
			};

			/// Create a new binding.
			Binding(const char* memberPath, int variableIndex, BindingType bindingType, hkInt8 bitIndex);

			/// The path to the member that is being bound.
			///
			/// Memory for this member is managed by hkbVariableBindingSet,
			/// so don't mess with it.
			/// See hkbVariableBindingSet::addBinding() for the path format.
			hkStringPtr m_memberPath;

		private:
			// The class of the member, if any.
			const hkClass* m_memberClass;  //+nosave

			// The offset of the member in the root object.
			// One is added so that zero represents an invalid offset.
			hkInt32 m_offsetInObjectPlusOne;  //+nosave

			// The offset of the data in an array, if any.
			// One is added so that zero represents an invalid offset.
			hkInt32 m_offsetInArrayPlusOne;  //+nosave

			// The index of the variable in the root behavior.  This is stored only to support variables syncing on SPU.
			hkInt32 m_rootVariableIndex;  //+nosave

		public:
			/// The index of the variable that is bound to an object member.
			hkInt32 m_variableIndex;

			/// The index of the bit to which the variable is bound.
			/// A value of -1 indicates that we are not binding to an individual bit.
			hkInt8 m_bitIndex;  //+default(-1)

			/// Which data we are binding to.
			hkEnum<BindingType, hkInt8> m_bindingType;

		private:
			// The type of the member data.
			hkEnum<hkClassMember::Type, hkUint8> m_memberType;  //+nosave

			// The type of the variable. This is stored only to support variables syncing on SPU.
			hkInt8 m_variableType;  //+nosave

			enum InternalBindingFlags
			{
				//+defineflags(true)

				FLAG_NONE = 0,

				// values are copied from the property to bound variables
				FLAG_OUTPUT = 1,
			};

			// whether the property is output
			hkFlags<InternalBindingFlags, hkInt8> m_flags;  //+nosave

		public:
			friend class hkbVariableBindingSetUtils;
		};

		/// Add a binding to the set.
		///
		/// The memberPath is made up of member names, separated by '/'.
		/// Integers after colons in the path are array indices.
		/// For example, "children:2/blendWeight" would seek an array
		/// member named "children", access the second member, and then
		/// look for a member named "blendWeight" in that object.
		void addBinding(const char* memberPath, int variableIndex, Binding::BindingType bindingType = Binding::BINDING_TYPE_VARIABLE, int bitIndex = -1);

		/// Remove a binding from the set, by index.
		void removeBinding(int index);

		/// Remove a binding from the set, by values.
		void removeBinding(const char* memberPath, int variableIndex, Binding::BindingType bindingType = Binding::BINDING_TYPE_VARIABLE, int bitIndex = -1);

		/// Remove all bindings from the set.
		void removeAllBindings();

		/// Remove all bindings of a particular type (VARIABLE or CHARACTER_PROPERTY).
		void removeBindingsByType(Binding::BindingType bindingType);

		/// Returns the number of bindings in the set.
		int numBindings();

		/// Get a binding from the set by index.
		const Binding& getBinding(int index);

		/// Find a binding by searching them all and comparing
		/// the member path.  Returns HK_NULL if no matching binding
		/// is found.  This is very expensive so try to avoid using it.
		const Binding* findBindingByMemberPath(const char* memberPath) const;

		/// Get the index of the binding that is bound to the "enable" member.
		int getIndexOfBindingToEnable();

		/// Whether there is any binding to an output property.
		hkBool32 hasOutputBinding();

		/// Computes all of the offsets of members in memory so we don't have to look them up each time.
		/// Early-outs if initialization has already occurred with the provided bindable.
		void initMemberOffsets(hkbBindable* bindable);

	private:
		// Compute the member data pointer for a binding.
		void initMemberOffsetsInternal(Binding& binding, hkbBindable* bindable);

		// The list of bindings.
		hkArray<struct Binding> m_bindings;

		// If there is a binding to the member hkbModifier::m_enable then
		// we store its index here.
		hkInt32 m_indexOfBindingToEnable;  //+default(-1)

		// Whether there is any binding to an output property.
		hkBool m_hasOutputBinding;  //+nosave

		// Indicates we have initialized our offsets
		hkBool m_initializedOffsets;  //+nosave

	public:
	};
}
