#pragma once
#include "RE/Havok/Common/Base/Container/String/hkString.h"

namespace RE
{
	class hkTrackerStringPtrLayoutHandler;

	/// This class is used to store a char* c-string.
	/// It automatically handles allocations and deallocation of
	/// stored c-string. The string memory may be externally or internally
	/// allocated, the lowest bit of the pointer being used as a
	/// should-deallocate flag. This simplifies destruction of objects
	/// which may be allocated in a packfile for instance.
	class hkStringPtr
	{
	public:
		friend class hkTrackerStringPtrLayoutHandler;

		enum StringFlags
		{
			/// If we own it, we free it.
			OWNED_FLAG = 0x1,
		};

	private:
		/// m_stringAndFlag&~1 is the real pointer, m_stringAndFlag&1 is the deallocate flag.
		const char* m_stringAndFlag;
	};
}
