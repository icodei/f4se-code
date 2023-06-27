#include "HookInfo.h"

#include <detours.h>

void HookInfo::ClearHookInfo() {
	HookInfo& Info = HookInfo::getInstance();

	Info.RegisterShaderOrig = NULL;
	Info.UnregisterShaderOrig = NULL;
	Info.PCUpdateMainThreadOrig = NULL;

	if (!Info.hookedList.empty()) {
		for (const std::pair<const char*, bool>& n : Info.hookedList) {
			Info.hookedList[n.first] = false;
		}
	}
}

HookInfo& HookInfo::getInstance() {
	static HookInfo instance;
	return instance;
}

void HookInfo::HookDetours() {
	HookInfo& Info = HookInfo::getInstance();

	REL::Relocation<uintptr_t> RegisterShaderLoader{ REL::ID(1569773) };
	Info.RegisterShaderOrig = RegisterShaderLoader.address();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Info.RegisterShaderOrig, RegisterShaderHandler::HookedRegister);
	DetourTransactionCommit();

	REL::Relocation<uintptr_t> UnregisterShaderLoader{ REL::ID(425866) };
	Info.UnregisterShaderOrig = UnregisterShaderLoader.address();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Info.UnregisterShaderOrig, UnregisterShaderHandler::HookedUnregister);
	DetourTransactionCommit();
}
