#pragma once
#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BSResource/BSResourceID.h"
#include "RE/Bethesda/BSResource/BSResourceStream.h"

namespace RE
{
	namespace BSResource
	{
		class EntryBase
		{
		public:
			//members
			ID NameID;
			BSTAtomicValue<unsigned int volatile> Ctrl;
			BSTSmartPointer<Stream> pStream;
		};

		template<class T>
		class Entry : EntryBase
		{

		};
	}
}
