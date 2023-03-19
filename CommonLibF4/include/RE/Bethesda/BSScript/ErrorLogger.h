#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/ICachedErrorMessage.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTObjectArena.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/Bethesda/BSCore/BSTTuple.h"
#include "RE/Bethesda/BSCore/MemoryManager.h"

namespace RE
{
	namespace BSScript
	{
		class ICachedErrorMessage;

		struct LogEvent;

		class __declspec(novtable) ErrorLogger :
			public BSTEventSource<LogEvent>  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ErrorLogger };
			static constexpr auto VTABLE{ VTABLE::BSScript__ErrorLogger };

			enum class Severity
			{
				kInfo,
				kWarning,
				kError,
				kFatal
			};

			struct PerThreadErrorCounts
			{
			public:
				// members
				std::uint32_t fatalCount;    // 0
				std::uint32_t errorCount;    // 4
				std::uint32_t warningCount;  // 8
			};
			static_assert(sizeof(PerThreadErrorCounts) == 0xC);

			virtual ~ErrorLogger();  // 00

			// add
			virtual void PostErrorImpl(const ICachedErrorMessage* a_errMsg, Severity a_severity) = 0;  // 01
			virtual void ResetImpl() { return; }                                                       // 02

			// members
			const BSFixedString logName;                                                // 60
			BSSpinLock dataLock;                                                        // 68
			BSTHashMap<std::uint32_t, ErrorLogger::PerThreadErrorCounts> threadErrors;  // 70
		};
		static_assert(sizeof(ErrorLogger) == 0xA0);
	}
}
