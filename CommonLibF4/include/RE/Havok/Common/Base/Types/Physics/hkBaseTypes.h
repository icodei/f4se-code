#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4.h"

namespace RE
{
	class hkBool
	{
	public:
		~hkBool() noexcept {}  // intentional

		bool b;
	};

	template <class T>
	class hkDebugOnlyMember
	{
	public:
		T member;
	};

	template <class E, class U>
	using hkEnum = stl::enumeration<E, U>;

	template <class E, class U>
	using hkFlags = stl::enumeration<E, U>;

	template <class T>
	class hkPadSpu
	{
	public:
		~hkPadSpu() noexcept {}  // NOLINT(modernize-use-equals-default)

		// members
		T storage;
	};

	enum class hkResultEnum
	{
		kSuccess,
		kFailure
	};

	struct hkResult
	{
	public:
		~hkResult() noexcept {}  // NOLINT(modernize-use-equals-default)

		// members
		hkResultEnum e;  // 0
	};
	static_assert(sizeof(hkResult) == 0x4);
}
