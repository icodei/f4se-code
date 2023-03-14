#pragma once

#include "RE/NetImmerse/NiMain/NiTDefaultAllocator.h"
#include "RE/NetImmerse/NiMain/NiTPointerListBase.h"

namespace RE
{
	template <class T>
	class NiTList :
		public NiTPointerListBase<NiTDefaultAllocator<T>, T>  // 00
	{
	public:
	};
}
