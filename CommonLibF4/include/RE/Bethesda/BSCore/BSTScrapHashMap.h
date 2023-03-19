#pragma once

#ifndef F4SE_TEST_SUITE
#	include "RE/Bethesda/BSCore/BSTScatterTable.h"
#	include "RE/Bethesda/BSCore/BSTTuple.h"
#	include "RE/Bethesda/BSCore/MemoryManager.h"
#	include "RE/Bethesda/CRC.h"
#endif

namespace RE
{
	template <
		class Key,
		class T,
		class Hash = BSCRC32<Key>,
		class KeyEq = std::equal_to<Key>>
	using BSTScrapHashMap =
		BSTScatterTable<
			Hash,
			KeyEq,
			BSTScatterTableTraits<Key, T>,
			BSTScatterTableScrapAllocator>;
}
