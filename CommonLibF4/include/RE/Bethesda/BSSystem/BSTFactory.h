#pragma once
#include "RE/Bethesda/BSCore/BSTStaticHashMap.h"
#include "RE/Bethesda/BSCore/BSTSingleton.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"

namespace RE
{
	template <class>
	struct IBSTCreator;

	template <class Key, class T, std::uint32_t SIZE, template <class> class Singleton>
	class BSTFactoryManager : public Singleton<BSTFactoryManager<Key, T, SIZE, Singleton>>
	{
	public:
		// members
		BSTStaticHashMap<Key, const T*, SIZE> factories;  // 00
	};
}
