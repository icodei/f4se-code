#include "Hooks.h"


BSEventNotifyControl MenuOpenCloseEventSink::ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) {
	const BSFixedString LoadingMenu("LoadingMenu");

	if (a_event.menuName == LoadingMenu && a_event.opening) {
		logInfo("Loading...");
	}
	if (a_event.menuName == LoadingMenu && !a_event.opening) {
		logInfo("Loading Complete");
	}
	return BSEventNotifyControl::kContinue;
}

#pragma region TESLoadGameEventSink
BSEventNotifyControl TESLoadGameEventSink::ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) {
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region TryHooks

void TryHookMenuOpenCloseEvent() {
	if (hookedList.at("MenuOpenCloseEvent") == true) {
		return;
	}
	BSTEventSource<MenuOpenCloseEvent>* eventSource = UI::GetSingleton()->GetEventSource<MenuOpenCloseEvent>();
	if (eventSource) {
		MenuOpenCloseEventSink* OnMenuOpenCloseEventSink = new MenuOpenCloseEventSink();
		eventSource->RegisterSink(OnMenuOpenCloseEventSink);
		hookedList.at("MenuOpenCloseEvent") = true;
	}
}

void TryHookTESLoadGameEvent() {
	if (hookedList.at("TESLoadGameEvent") == true) {
		return;
	}
	BSTEventSource<TESLoadGameEvent>* eventSource = TESLoadGameEvent::GetEventSource();
	if (eventSource) {
		TESLoadGameEventSink* OnTESLoadGameEvent = new TESLoadGameEventSink();
		eventSource->RegisterSink(OnTESLoadGameEvent);
		hookedList.at("TESLoadGameEvent") = true;
	}
}

void TryHooks() {
	logInfo("Trying for hooks...");
	TryHookMenuOpenCloseEvent();
	TryHookTESLoadGameEvent();
}

//Used to hook certain things that CTD if hooked at the wrong time
void TrySpecialHooks() {
	logInfo("Trying for special hooks...");
}
#pragma endregion

#pragma region Init
void initHooks() {
	if (hookedList.empty()) {
		hookedList = {
			{ "MenuOpenCloseEvent", false },
			{ "TESLoadGameEvent", false },
		};
	}
	TryHooks();
	logInfo(";=============================== Hooks Install Complete ===============================;");
	print_map(std::as_const(hookedList));
	logInfo(";======================================================================================;");
}

//Mostly for global events
void initSpecialHooks() {
	TrySpecialHooks();
	logInfo(";=========================== Special Hooks Install Complete ===========================;");
	print_map(std::as_const(hookedList));
	logInfo(";======================================================================================;");
}
#pragma endregion
