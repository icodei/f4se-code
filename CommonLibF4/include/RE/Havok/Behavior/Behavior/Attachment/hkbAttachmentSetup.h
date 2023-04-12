#pragma once

namespace RE
{
	/// The template for an attachment scenario.  These are referenced objects
	/// so that you can choose how to manage the memory for them.
	class hkbAttachmentSetup : public hkReferencedObject
	{
	public:
		/// Set to default values.
		hkbAttachmentSetup();

		/// Copy constructor
		hkbAttachmentSetup(const hkbAttachmentSetup& setup);

		/// How the attachment will be implemented.
		enum AttachmentType
		{
			/// Keyframe the attached rigid body.
			ATTACHMENT_TYPE_KEYFRAME_RIGID_BODY,

			/// Use a ball and socket constraint.
			ATTACHMENT_TYPE_BALL_SOCKET_CONSTRAINT,

			/// Use a ragdoll constraint.
			ATTACHMENT_TYPE_RAGDOLL_CONSTRAINT,

			/// Set the world-from-model transform of the attachee.
			ATTACHMENT_TYPE_SET_WORLD_FROM_MODEL,

			/// No attachment will be done.
			ATTACHMENT_TYPE_NONE,
		};

	public:
	};
}
