#pragma once

namespace RE
{
	class hkbCharacter;
	class hkbAttachmentSetup;
	class hkCriticalSection;
	struct hkbAttachmentInstance;
	struct hkbAttachmentTargets;
	struct hkbSceneCharacters;

	/// A manager for attachments.  The attachment manager implements various methods of attachment.
	/// It maintains a topologically sorted list of attachments, and updates the attachments in
	/// "attacher before attachee" order.
	class hkbAttachmentManager
	{
	public:
	private:
	private:
	};
}
