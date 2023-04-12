#pragma once
#include "RE/Havok/Common/Base/System/Io/OArchive/hkOArchive.h"

namespace RE
{
	class hkDisplaySerializeOStream : public hkOArchive
	{
	public:
		static constexpr auto RTTI{ RTTI::hkDisplaySerializeOStream };
		static constexpr auto VTABLE{ VTABLE::hkDisplaySerializeOStream };
	};
}
