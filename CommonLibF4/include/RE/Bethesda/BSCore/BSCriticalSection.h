#pragma once

namespace RE
{
	class BSCriticalSection
	{
	public:
		//members
		std::byte CriticalSection[24];
		unsigned int ulThreadOwner;
		unsigned int ulPrevOwner;
		unsigned int uiLockCount;
	};

}
