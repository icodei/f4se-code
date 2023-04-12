#pragma once

namespace RE
{
	class hkbCharacter;

	/// The targets to an attachment.  The attachee can be either a character or a
	/// rigid body.  If you specify both, the rigid body should belong to the character,
	/// which will override hkbAttachmentSetup::m_attacheeBone.
	struct hkbAttachmentTargets
	{
	};
}
