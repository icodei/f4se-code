#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"

namespace RE
{
	template <class Key>
	class BSTSetTraits
	{
	public:
		using key_type = Key;
		using mapped_type = void;
		using value_type = key_type;

		[[nodiscard]] static const key_type& unwrap_key(const value_type& a_value) noexcept { return a_value; }
	};

	template <
		class Key,
		class Hash = BSCRC32<Key>,
		class KeyEq = std::equal_to<Key>>
	using BSTSet =
		BSTScatterTable<
			Hash,
			KeyEq,
			BSTSetTraits<Key>,
			BSTScatterTableHeapAllocator>;
}
