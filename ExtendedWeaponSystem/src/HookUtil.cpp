#include "HookUtil.h"

namespace HookUtil {
	uintptr_t SafeWrite64(uintptr_t addr, uintptr_t data) {
		return SafeWrite_Impl(addr, data);
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
