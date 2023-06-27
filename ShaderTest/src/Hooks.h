#pragma once
#include "Global.h"

class MenuOpenCloseEventSink : public BSTEventSink<MenuOpenCloseEvent> {
public:
	virtual ~MenuOpenCloseEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(MenuOpenCloseEventSink);
};

class TESLoadGameEventSink : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESLoadGameEventSink);
};

/*;========================================================================================================================================================;*/

class PlayerUpdateHandler {
public:
	~PlayerUpdateHandler() {}

	void HookedUpdate();

	F4_HEAP_REDEFINE_NEW(PlayerUpdateHandler);
};

/*;========================================================================================================================================================;*/

class RegisterShaderHandler {
public:
	~RegisterShaderHandler() {}

	static void HookedRegister(const char* a_name, BSReloadShaderI* a_shader);

	using FnRegister = decltype(&HookedRegister);

	F4_HEAP_REDEFINE_NEW(RegisterShaderHandler);
};

class UnregisterShaderHandler {
public:
	~UnregisterShaderHandler() {}

	static void HookedUnregister(const char* a_name);

	using FnUnregister = decltype(&HookedUnregister);

	F4_HEAP_REDEFINE_NEW(UnregisterShaderHandler);
};

/*;========================================================================================================================================================;*/

void initHooks();
void initSpecialHooks();
