#pragma once

#include "RE/Bethesda/BSResource/BSResourceEnums.h"
#include "RE/Bethesda/BSResource/LooseFileStreamBase.h"
#include "RE/Bethesda/BSResource/StreamBase.h"
#include "RE/Bethesda/BSSystemFile.h"

#include "RE/Bethesda/BSResource/Stream.h"

namespace RE
{
	namespace BSResource
	{
		class Location
		{
		public:
			static constexpr auto RTTI{ RTTI::BSResource__Location };
			static constexpr auto VTABLE{ VTABLE::BSResource__Location };

			struct $EEB0A6E53216D5EA78AC2B6AB5AC6EA2
			{
				std::byte gap0[4];
				bool bMounted;
			};

			union $286B7AA9BD27ED50F4CD39F5142F8B9C
			{
				void* __vftable /*VFT*/;
				$EEB0A6E53216D5EA78AC2B6AB5AC6EA2 __s1;
			};
			//members
			$286B7AA9BD27ED50F4CD39F5142F8B9C ___u0;
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
