#include "Util.h"

char tempbuf[8192] = { 0 };
char* _MESSAGE(const char* fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vsnprintf(tempbuf, sizeof(tempbuf), fmt, args);
	va_end(args);
	spdlog::log(spdlog::level::info, tempbuf);

	return tempbuf;
}

void Dump(void* mem, unsigned int size) {
	char* p = static_cast<char*>(mem);
	unsigned char* up = (unsigned char*)p;
	std::stringstream stream;
	int row = 0;
	for (unsigned int i = 0; i < size; i++) {
		stream << std::setfill('0') << std::setw(2) << std::hex << (int)up[i] << " ";
		if (i % 8 == 7) {
			stream << "\t0x"
				   << std::setw(2) << std::hex << (int)up[i]
				   << std::setw(2) << (int)up[i - 1]
				   << std::setw(2) << (int)up[i - 2]
				   << std::setw(2) << (int)up[i - 3]
				   << std::setw(2) << (int)up[i - 4]
				   << std::setw(2) << (int)up[i - 5]
				   << std::setw(2) << (int)up[i - 6]
				   << std::setw(2) << (int)up[i - 7] << std::setfill('0');
			stream << "\t0x" << std::setw(2) << std::hex << row * 8 << std::setfill('0');
			_MESSAGE("%s", stream.str().c_str());
			stream.str(std::string());
			row++;
		}
	}
}

BSTEventSource<void*>* GetGlobalEventSource(BSTGlobalEvent_OLD* globalEvents, const char* globalName) {
	auto sources = (globalEvents->eventSources);
	for (auto elem = sources.begin(); elem != sources.end(); ++elem) {
		const char* name = GetObjectClassName(elem) + 15;
		if (globalName == name) {
			return (BSTEventSource<void*>*)&((elem));
		}
	}
	return nullptr;
}

const char* GetObjectClassNameImpl(const char* result, void* objBase) {
	using namespace RTTI;
	void** obj = (void**)objBase;
	CompleteObjectLocator** vtbl = (CompleteObjectLocator**)obj[0];
	CompleteObjectLocator* rtti = vtbl[-1];
	RVA<TypeDescriptor> typeDesc = rtti->typeDescriptor;

	// starts with ,?
	const char* _name = typeDesc->mangled_name();
	if ((_name[0] == '.') && (_name[1] == '?')) {
		// is at most 100 chars long
		for (uint32_t i = 0; i < 100; i++) {
			if (_name[i] == 0) {
				// remove the .?AV
				return _name + 4;
				break;
			}
		}
	}
	return result;
}

const char* GetObjectClassName(void* objBase) {
	const char* result = "<no rtti>";
	__try {
		result = GetObjectClassNameImpl(result, objBase);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		// return the default
	}

	return result;
}

//Functions to write a simple line of text to logs

//Write info to log
void logInfo(string text) {
	logger::info(FMT_STRING("{:s}"), text);
}

void logWarn(string text) {
	logger::warn(FMT_STRING("{:s}"), text);
}

//Write error to log. Error is unexpected result but not a crash
void logError(string text) {
	logger::error(FMT_STRING("{:s}"), text);
}

//Write critical to log. Critical is something that will crash
void logCritical(string text) {
	logger::critical(FMT_STRING("{:s}"), text);
}
