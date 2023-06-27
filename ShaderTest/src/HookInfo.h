#pragma once
#include "Global.h"

#include "Hooks.h"

struct HookInfo {
private:
	HookInfo() {}
	~HookInfo() { ClearHookInfo(); }

public:
	HookInfo(HookInfo const&) = delete;
	void operator=(HookInfo const&) = delete;

	//static functions
	static void ClearHookInfo();
	static HookInfo& getInstance();

	//static hook functions
	static void HookDetours();

	//members
	uintptr_t RegisterShaderOrig;
	uintptr_t UnregisterShaderOrig;
	uintptr_t PCUpdateMainThreadOrig;

	std::unordered_map<const char*, bool> hookedList;
};
