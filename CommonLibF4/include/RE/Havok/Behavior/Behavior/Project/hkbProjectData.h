#pragma once
#include "RE/Havok/Behavior/Behavior/TransitionEffect/hkbTransitionEffect.h"
#include "RE/Havok/Behavior/Behavior/Project/hkbProjectStringData.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Types/hkRefPtr.h"

namespace RE
{
	/// Constant data associated with a behavior project.
	class hkbProjectData : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbProjectData };
		static constexpr auto VTABLE{ VTABLE::hkbProjectData };

		hkbProjectData();

		/// Get the string data for the project.
		const hkbProjectStringData* getStringData() const { return m_stringData; }

		/// Set the string data and update the reference counts on the old and new string data.
		void setStringData(hkbProjectStringData* stringData);

	public:
		/// The world up vector.
		hkVector4f m_worldUpWS;

		/// String data such as names and filenames associated with the project.
		hkRefPtr<hkbProjectStringData> m_stringData;

		/// This is used to initialize hkbTransitionEffect::m_defaultEventMode.
		hkEnum<hkbTransitionEffect::EventMode, hkInt8> m_defaultEventMode;
	};
}
