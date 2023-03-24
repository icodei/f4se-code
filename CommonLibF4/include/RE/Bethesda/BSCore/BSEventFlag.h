#pragma once

namespace RE
{
	class BSEventFlag
	{
	public:
		//members
		void* hEvent;
	};
	static_assert(sizeof(BSEventFlag) == 0x8);
}
