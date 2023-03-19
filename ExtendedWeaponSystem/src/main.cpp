#include "Global.h"

F4SE::PluginHandle g_pluginHandle = NULL;
const F4SE::MessagingInterface* g_messaging;
const F4SE::TaskInterface* g_taskInterface;
const F4SE::Trampoline* g_trampoline;

void init() {
	pc = PlayerCharacter::GetSingleton();
	pcam = PlayerCamera::GetSingleton();

	reloadStarted = false;
	reloadEnd = true;
	processCurrentWeap = false;
	processCurrentScope = false;
	ignore = false;
	readyForRender = false;
}

void OnF4SEMessage(F4SE::MessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SE::MessagingInterface::kPostLoad:

	case F4SE::MessagingInterface::kPostPostLoad:

	case F4SE::MessagingInterface::kPreLoadGame:

	case F4SE::MessagingInterface::kPostLoadGame:
		FillWeaponInfo();
		break;
	case F4SE::MessagingInterface::kPreSaveGame:

	case F4SE::MessagingInterface::kPostSaveGame:

	case F4SE::MessagingInterface::kDeleteGame:

	case F4SE::MessagingInterface::kInputLoaded:

	case F4SE::MessagingInterface::kNewGame:

	case F4SE::MessagingInterface::kGameLoaded:
		if (!GetForms()) {
			logger::critical(FMT_STRING("ERROR: You are missing some forms"));
		}
		if (!Install()) {
			logger::critical(FMT_STRING("ERROR:: Could not install all hooks"));
		}
		break;
	case F4SE::MessagingInterface::kGameDataReady:
		init();
		break;
	}
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= fmt::format(FMT_STRING("{}.log"), Version::PROJECT);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::warn);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

	logger::info(FMT_STRING("{} v{}"), Version::PROJECT, Version::NAME);

	a_info->infoVersion = F4SE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_f4se->IsEditor()) {
		logger::critical(FMT_STRING("loaded in editor"));
		return false;
	}

	const auto ver = a_f4se->RuntimeVersion();
	if (ver < F4SE::RUNTIME_1_10_162) {
		logger::critical(FMT_STRING("unsupported runtime v{}"), ver.string());
		return false;
	}

	//F4SE::AllocTrampoline(1024 * 64);

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);
	logger::info(FMT_STRING("Plugin Load"));
	g_trampoline = &F4SE::GetTrampoline();
	g_taskInterface = F4SE::GetTaskInterface();
	g_pluginHandle = F4SE::GetPluginHandle();
	g_messaging = F4SE::GetMessagingInterface();

	//if (!g_messaging) {
	//	logger::critical(FMT_STRING("Couldn't get messaging interface"));
	//	return false;
	//}

	//if (g_messaging->RegisterListener(OnF4SEMessage)) {
	//	logger::info(FMT_STRING("Registered listener"));
	//}

	g_messaging->RegisterListener([](F4SE::MessagingInterface::Message* msg) -> void {
		if (msg->type == F4SE::MessagingInterface::kGameLoaded) {
			init();
			if (!GetForms()) {
				logger::critical(FMT_STRING("ERROR: You are missing some forms"));
			}
			if (!Install()) {
				logger::critical(FMT_STRING("ERROR:: Could not install all hooks"));
			}
		}
		if (msg->type == F4SE::MessagingInterface::kPostLoadGame) {
			FillWeaponInfo();
		}
	});
	
	return true;
}
