#pragma once
//#include "RE/Bethesda/BSResource/BSResourceArchive2.h"
//#include "RE/Bethesda/BSResource/BSResourceDirectory.h"
//#include "RE/Bethesda/BSResource/BSResourceEntry.h"
//#include "RE/Bethesda/BSResource/BSResourceEntryDB.h"
//#include "RE/Bethesda/BSResource/BSResourceEntryQueue.h"
#include "RE/Bethesda/BSResource/BSResourceEnums.h"
//#include "RE/Bethesda/BSResource/BSResourceID.h"
#include "RE/Bethesda/BSResource/BSResourceLocation.h"
#include "RE/Bethesda/BSResource/BSResourceStream.h"
//#include "RE/Bethesda/BSResource/BSResourceStreamBase.h"
//#include "RE/Bethesda/BSResource/BSResourceStreamer.h"
//#include "RE/Bethesda/BSResource/BSResourceUtil.h"
//#include "RE/Bethesda/BSResource/LooseFileStreamBase.h"
//#include "RE/Bethesda/BSSystem/BSSystemFile.h"

namespace RE
{
	namespace BSResource
	{
		[[nodiscard]] ErrorCode GetOrCreateStream(const char* a_fileName, BSTSmartPointer<Stream>& a_result, bool a_writable = false, Location* a_optionalStart = nullptr);
	}

}
