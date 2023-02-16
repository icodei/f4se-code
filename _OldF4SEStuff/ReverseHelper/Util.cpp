#include "Global.h"

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

const std::string prefixLog() {
	std::stringstream buffer;
	buffer << "[" << currentDateTime() << "] [EWS] ";
	return(buffer.str());
}

//Write message log only if logEnabled == True
void logIfNeeded(std::string text) {
	if (logEnabled) {
		_MESSAGE("%s %s", prefixLog().c_str(), text.c_str());
	}
}

//Write message log always
void log(std::string text) {
	_MESSAGE("%s %s", prefixLog().c_str(), text.c_str());
}

void DumpClassX(void* theClassPtr, UInt64 nIntsToDump)
{
	UInt64* basePtr = (UInt64*)theClassPtr;

	_MESSAGE("DumpClassX");

	gLog.Indent();

	if (!theClassPtr) return;
	for (UInt64 ix = 0; ix < nIntsToDump; ix++) {
		UInt64* curPtr = basePtr + ix;
		const char* curPtrName = NULL;
		UInt64 otherPtr = 0;
		float otherFloat1 = 0.0;
		float otherFloat2 = 0.0;
		const char* otherPtrName = NULL;
		if (curPtr) {
			curPtrName = GetObjectClassName((void*)curPtr);

			__try
			{
				otherPtr = *curPtr;
				UInt32 lowerFloat = otherPtr & 0xFFFFFFFF;
				UInt32 upperFloat = (otherPtr >> 32) & 0xFFFFFFFF;
				otherFloat1 = *(float*)&lowerFloat;
				otherFloat2 = *(float*)&upperFloat;
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				//
			}

			if (otherPtr) {
				otherPtrName = GetObjectClassName((void*)otherPtr);
			}
		}

		_MESSAGE("%3d +%03X ptr: 0x%016I64X: %32s *ptr: 0x%016I64x | %f, %f: %32s", ix, ix * 8, curPtr - RelocationManager::s_baseAddr, curPtrName, otherPtr, otherFloat2, otherFloat1, otherPtrName);
	}

	gLog.Outdent();
}
