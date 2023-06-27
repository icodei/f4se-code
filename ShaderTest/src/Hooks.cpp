#include "Hooks.h"

#include "Global.h"
#include "HookInfo.h"
#include "HookUtil.h"
#include "ShaderInfo.h"
#include "Util.h"

#pragma region EventSink

#pragma region MenuOpenCloseEventSink
BSEventNotifyControl MenuOpenCloseEventSink::ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) {
	const BSFixedString LoadingMenu("LoadingMenu");
	if (a_event.menuName == LoadingMenu && a_event.opening) {
		logInfo("Loading...");
		gameLoading = true;
	}
	if (a_event.menuName == LoadingMenu && !a_event.opening) {
		logInfo("Loading Complete");
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion MenuOpenCloseEventSink

#pragma region TESLoadGameEventSink
BSEventNotifyControl TESLoadGameEventSink::ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) {
	logInfo("Game Loaded");
	return BSEventNotifyControl::kContinue;
}
#pragma endregion TESLoadGameEventSink

#pragma endregion EventSink

/*;========================================================================================================================================================;*/

#pragma region Handlers

#pragma region PlayerUpdateHandler
void PlayerUpdateHandler::HookedUpdate() {
	HookInfo& Info = HookInfo::getInstance();

	typedef void (*FnUpdate)();
	FnUpdate fn = (FnUpdate)Info.PCUpdateMainThreadOrig;
	if (fn) {
		(*fn)();
	}
}
#pragma endregion PlayerUpdateHandler

void RegisterShaderHandler::HookedRegister(const char* a_name, BSReloadShaderI* a_shader) {
	HookInfo& Info = HookInfo::getInstance();
	ShaderInfo::FillShaderInfo(a_name, a_shader, true);

	//BSFixedString name(a_name);
	//auto shadermap = BSShaderManager::GetShaderLoaderMap();
	//if (&shadermap) {
	//	shadermap.insert(BSTTuple<BSFixedString, BSReloadShaderI*>(name, a_shader));
	//} else {
	//	ShaderInfo::FillShaderInfo(a_name, (BSShader*)a_shader, true);
	//}

	FnRegister fn = (FnRegister)Info.RegisterShaderOrig;
	if (fn) {
		(*fn)(a_name, a_shader);
	}
	return;
}

void UnregisterShaderHandler::HookedUnregister(const char* a_name) {
	HookInfo& Info = HookInfo::getInstance();
	ShaderInfo::EraseShaderInfo(a_name);

	//BSFixedString name(a_name);
	//auto shadermap = BSShaderManager::GetShaderLoaderMap();
	//if (&shadermap) {
	//	if (shadermap.contains(name)) {
	//		shadermap.erase(name);
	//	}
	//} else {
	//	ShaderInfo::EraseShaderInfo(a_name);
	//}

	FnUnregister fn = (FnUnregister)Info.UnregisterShaderOrig;
	if (fn) {
		(*fn)(a_name);
	}
	return;
}

#pragma endregion Handlers

#pragma region TryHooks

void TryHookMenuOpenCloseEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("MenuOpenCloseEvent") == true) {
		return;
	}
	BSTEventSource<MenuOpenCloseEvent>* eventSource = UI::GetSingleton()->GetEventSource<MenuOpenCloseEvent>();
	if (eventSource) {
		MenuOpenCloseEventSink* OnMenuOpenCloseEventSink = new MenuOpenCloseEventSink();
		eventSource->RegisterSink(OnMenuOpenCloseEventSink);
		Info.hookedList.at("MenuOpenCloseEvent") = true;
	}
}

void TryHookTESLoadGameEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("TESLoadGameEvent") == true) {
		return;
	}
	BSTEventSource<TESLoadGameEvent>* eventSource = TESLoadGameEvent::GetEventSource();
	if (eventSource) {
		TESLoadGameEventSink* OnTESLoadGameEvent = new TESLoadGameEventSink();
		eventSource->RegisterSink(OnTESLoadGameEvent);
		Info.hookedList.at("TESLoadGameEvent") = true;
	}
}

void TryHooks() {
	HookInfo& Info = HookInfo::getInstance();
	if (!Info.hookedList.empty()) {
		int i = 0;
		for (const std::pair<const char*, bool>& n : Info.hookedList) {
			if (n.second) {
				++i;
			}
		}
		if (i && i == Info.hookedList.size()) {
			return;
		}
	}

	logInfo("Trying for hooks...");
	TryHookMenuOpenCloseEvent();
	TryHookTESLoadGameEvent();
}

void TrySpecialHooks() {
	HookInfo& Info = HookInfo::getInstance();

	logInfo("Trying for special hooks...");
}
#pragma endregion

#pragma region Init
void initHooks() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.empty()) {
		Info.hookedList = {
			{ "MenuOpenCloseEvent", false },
			{ "TESLoadGameEvent", false },
		};
	}
	TryHooks();
	logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " Hooks Install Complete "sv, 120));
	print_map(std::as_const(Info.hookedList));
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 120));

	ShaderInfo& Shader = ShaderInfo::getInstance();
	logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " Shader "sv, 120));
	ShaderInfo::PrintAllShaderInfo(std::as_const(Shader.shaderList));
	logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 120));
}

//Mostly for global events
void initSpecialHooks() {
	HookInfo& Info = HookInfo::getInstance();
	if (!Info.hookedList.empty()) {
		int i = 0;
		for (const std::pair<const char*, bool>& n : Info.hookedList) {
			if (n.second) {
				++i;
			}
		}
		if (i && i == Info.hookedList.size()) {
			return;
		}
	}
	TrySpecialHooks();
	logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " Special Hooks Install Complete "sv, 120));
	print_map(std::as_const(Info.hookedList));
	logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 120));
}
#pragma endregion
