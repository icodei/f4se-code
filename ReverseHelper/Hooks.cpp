#include "Global.h"


RelocAddr<uintptr_t> MenuOpenCloseEvent_ReceiveEvent_Target(0x2D49200 + 0x08);
_MenuOpenCloseEvent_ReceiveEvent MenuOpenCloseEvent_ReceiveEvent_Original;


BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName) {
	for (int i = 0; i < globalEvents->eventSources.count; i++) {
		const char* name = GetObjectClassName(globalEvents->eventSources[i]) + 15;    // ?$EventSource@V
		if (strstr(name, dispatcherName) == name) {
			return &globalEvents->eventSources[i]->eventDispatcher;
		}
	}
	return nullptr;
}

EventResult TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent* evn, void* dispatcher) {
	RegisterAfterLoadEvents();
	if (!oncePerSession) {
		if (!RegisterAfterLoadEvents()) {
			logIfNeeded("unable to register for events on game load");
		}
		oncePerSession = true;
	}
	return kEvent_Continue;
}

EventResult MenuOpenCloseEvent_ReceiveEvent_Hook(void* arg1, MenuOpenCloseEvent* evn, void* dispatcher) {
	static BSFixedString LoadingMenu("LoadingMenu");
	if (evn->menuName == LoadingMenu && evn->isOpen) {

		static auto pLoadGameHandler = new TESLoadGameHandler();
		GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);
	}
	return MenuOpenCloseEvent_ReceiveEvent_Original(arg1, evn, dispatcher);
}

bool Install() { //Called at GameLoaded
	bool toReturn = true;
	log("Hooks Install");

	MenuOpenCloseEvent_ReceiveEvent_Original = *(_MenuOpenCloseEvent_ReceiveEvent*)(MenuOpenCloseEvent_ReceiveEvent_Target.GetUIntPtr());
	SafeWrite64(MenuOpenCloseEvent_ReceiveEvent_Target.GetUIntPtr(), (uintptr_t)MenuOpenCloseEvent_ReceiveEvent_Hook);

	return toReturn;
}

bool RegisterAfterLoadEvents() { //Called at LoadingMenu


	return true;
}