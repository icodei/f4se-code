#pragma once
#include "RE/Havok/Common/Base/Container/String/hkStringPtr.h"
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"

namespace RE
{
	/// Constant string data associated with a behavior project.
	class hkbProjectStringData : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbProjectStringData };
		static constexpr auto VTABLE{ VTABLE::hkbProjectStringData };

		hkbProjectStringData() {}

		/// A list of referenced animation filenames.
		/// This is not necessarily equivalent to the files that were exported.
		/// The list of exported files is dependent on several settings in HAT
		/// such as "Only Export Referenced Animations" and "Bundle Referenced Animations"
		hkArray<hkStringPtr> m_animationFilenames;

		/// A list of referenced behavior filenames.
		hkArray<hkStringPtr> m_behaviorFilenames;

		/// A list of referenced character filenames.
		hkArray<hkStringPtr> m_characterFilenames;

		/// The names of the events in the project.  These will not be present if your
		/// project has events defined per-behavior.
		hkArray<hkStringPtr> m_eventNames;

		/// The path to the folder containing animations.  This can be either absolute or relative to the project folder.
		hkStringPtr m_animationPath;

		/// The path to the folder containing behaviors.  This can be either absolute or relative to the project folder.
		hkStringPtr m_behaviorPath;

		/// The path to the folder containing characters.  This can be either absolute or relative to the project folder.
		hkStringPtr m_characterPath;

		/// The path to the folder containing scripts.  This can be either absolute or relative to the project folder.
		hkStringPtr m_scriptsPath;

		/// The full path to the source HKP file.
		hkStringPtr m_fullPathToSource;

		/// The path from which this project data was loaded from.  This is not saved.  It is set by the hkbProjectAssetManager and used
		/// when loading assets.
		hkStringPtr m_rootPath;  //+nosave
	};
}
