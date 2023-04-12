#pragma once

namespace RE
{
	template <class TYPE, TYPE N, class DISCRIMINANT>
	struct hkHandle
	{
	public:
		~hkHandle() noexcept {}  // intentional

		// members
		TYPE m_value;  // 0
	};
}
