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

		template <class T_Type, class T_EntryDBTraitsCArgs>
		class Entry : public EntryBase
		{
		public:
			using U_Type = T_Type;
			using U_EntryDBTraitsCArgs = T_EntryDBTraitsCArgs;

			// members
			Entry<T_Type, T_EntryDBTraitsCArgs>* next;  // 00
			T_Type data;                                // ??
			std::uint32_t flags;                        // ??
		};
	}
}
