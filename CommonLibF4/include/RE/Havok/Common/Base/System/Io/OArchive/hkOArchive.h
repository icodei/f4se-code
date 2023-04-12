#pragma once
#include "RE/Havok/Common/Base/Types/hkRefPtr.h"

namespace RE
{
	class hkOArchive : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkOArchive };
		static constexpr auto VTABLE{ VTABLE::hkOArchive };

		virtual ~hkOArchive();

	protected:
		//member
		hkRefPtr<hkStreamWriter> m_writer;
		hkBool m_byteSwap;
	};

	typedef hkOArchive hkOfArchive;
}
