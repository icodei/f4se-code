#pragma once

namespace RE
{
	/// An attribute for describing the role of a property of a behavior node.  You
	/// can also specify additional flags that influence how HAT presents the UI for the property.
	struct hkbRoleAttribute
	{
		//+defineattribute(true)
	public:
		enum Role
		{

			/// The property has no particular role.
			ROLE_DEFAULT,

			/// The property is a char* which stores a file name. HAT will open up a file picker dialog box
			/// when setting this property,
			ROLE_FILE_NAME,

			/// The property is a bone index (hkInt16) or contains bone indices (hkbBoneIndexArray, hkbBoneWeightArray).
			/// hkbBoneIndexArrays, hkbBoneWeightArrays, and individual bones can be given a group name using hk.Ui(group="groupName").
			/// HAT will use the Select Bones Dialog for groups of related bones.
			ROLE_BONE_INDEX,

			/// The property is an event ID (hkInt32). HAT will allow you to choose the event by name.
			ROLE_EVENT_ID,

			/// The property is a behavior variable index (hkInt32). HAT will allow you to choose a variable by name.
			ROLE_VARIABLE_INDEX,

			/// The property is a behavior attribute index (hkInt32). HAT will allow you to choose an attribute by name.
			ROLE_ATTRIBUTE_INDEX,

			/// The property is a time in seconds (hkReal) (currently unused).
			ROLE_TIME,

			/// The property is a script
			ROLE_SCRIPT,

			/// The property is a local frame
			ROLE_LOCAL_FRAME,

			/// The property is a bone attachment
			ROLE_BONE_ATTACHMENT,

		};

		enum RoleFlags
		{
			//+defineflags(true)

			/// No flags are set.
			FLAG_NONE = 0,

			/// The property refers to the ragdoll skeleton. Without this flag HAT defaults to the animation skeleton.
			/// Use this in conjunction with ROLE_BONE_INDEX, hkbBoneIndexArrays, or hkbBoneWeightArrays.
			FLAG_RAGDOLL = 1,

			/// The property should be normalized (apply this to hkVector4) (currently unused).
			FLAG_NORMALIZED = 1 << 1,

			/// HAT will not allow the property to be bound to a variable.
			FLAG_NOT_VARIABLE = 1 << 2,

			/// HAT will not show the property in the UI.
			FLAG_HIDDEN = 1 << 3,

			/// By default, all node properties are considered inputs, which means that behavior variable values
			/// are copied to them. If you want the property to serve as an output, you must use this flag.
			/// Note: a property cannot be both an input and an output.
			FLAG_OUTPUT = 1 << 4,

			/// HAT will not allow the property to be bound to a character property.
			FLAG_NOT_CHARACTER_PROPERTY = 1 << 5,

			/// HAT will interpret the property as contributing to a bone chain (no siblings allowed). Use this in
			/// conjunction with ROLE_BONE_INDEX or hkbBoneIndexArrays.
			FLAG_CHAIN = 1 << 6,

		};
	};
}
