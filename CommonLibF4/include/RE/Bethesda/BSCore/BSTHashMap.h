#pragma once

#include "RE/Bethesda/BSCore/BSTScatterTable.h"
#include "RE/Bethesda/BSCore/BSTTuple.h"
#include "RE/Bethesda/BSCore/MemoryManager.h"
#include "RE/Bethesda/CRC.h"

namespace RE
{
	template <
		class Key,
		class T,
		class Hash = BSCRC32<Key>,
		class KeyEq = std::equal_to<Key>>
	using BSTHashMap =
		BSTScatterTable<
			Hash,
			KeyEq,
			BSTScatterTableTraits<Key, T>,
			BSTScatterTableHeapAllocator>;
}
