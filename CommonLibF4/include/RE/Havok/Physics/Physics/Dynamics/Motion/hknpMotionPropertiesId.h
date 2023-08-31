#pragma once

namespace RE
{
	class hknpMotionPropertiesId
	{
	public:
		enum Preset
		{
			STATIC = 0,  ///< No velocity allowed
			DYNAMIC,     ///< For regular dynamic bodies, undamped and gravity factor = 1
			KEYFRAMED,   ///< like DYNAMIC, but gravity factor = 0
			FROZEN,      ///< like KEYFRAMED, but lots of damping
			DEBRIS,      ///< like DYNAMIC, but aggressive deactivation

			NUM_PRESETS
		};
	};
}
