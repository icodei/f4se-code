#pragma once

#include "RE/Bethesda/BSResource/BSResourceEnums.h"
#include "RE/Bethesda/BSResource/BSResourceStream.h"
#include "RE/Bethesda/BSResource/BSResourceStreamBase.h"
#include "RE/Bethesda/BSResource/LooseFileStreamBase.h"
#include "RE/Bethesda/BSSystemFile.h"

namespace RE
{
	namespace BSResource
	{
		class Location
		{
		public:
			static constexpr auto RTTI{ RTTI::BSResource__Location };
			static constexpr auto VTABLE{ VTABLE::BSResource__Location };

			//members
			bool bMounted;
		};

		class EntryBase
		{
		public:
			//members
			BSResource::ID NameID;
			BSTAtomicValue<unsigned int volatile> Ctrl;
			BSTSmartPointer<BSResource::Stream> pStream;
		};

		class IEntryDB
		{
		public:
			static constexpr auto RTTI{ RTTI::BSResource__IEntryDB };
			static constexpr auto VTABLE{ VTABLE::BSResource__IEntryDB };

			//members
		};

		[[nodiscard]] ErrorCode GetOrCreateStream(const char* a_fileName, BSTSmartPointer<Stream>& a_result, bool a_writable = false, Location* a_optionalStart = nullptr);
	}

}
