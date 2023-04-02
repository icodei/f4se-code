#include "Global.h"

void initPlugin() {
	pc = PlayerCharacter::GetSingleton();
	logger::info(FMT_STRING("Player: {:p}"), fmt::ptr(pc));
	pcam = PlayerCamera::GetSingleton();
	logger::info(FMT_STRING("Player Camera: {:p}"), fmt::ptr(pcam));

	if (!GetForms()) {
		logError("You are missing some forms");
	}

	ignoreEquip = false;
	ignoreScope = false;
	readyForRender = false;
	reloadHasEnded = true;
	reloadHasStarted = false;
	weaponHasSequentialReload = false;
	weaponHasScopeThermal = false;
}

void initLog() {
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		stl::report_and_fail("Failed to find standard logging directory"sv);
	}

	*path /= fmt::format(FMT_STRING("{:s}.log"), Version::PROJECT);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
	log->flush_on(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("[%m/%d/%Y - %T] [EWS] [%^%l%$] %v"s);

	logger::info(FMT_STRING("{:s} v{:s}"), Version::PROJECT, Version::NAME);
}

void OnF4SEMessage(F4SE::MessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SE::MessagingInterface::kPostLoad:

	case F4SE::MessagingInterface::kPostPostLoad:
		
	case F4SE::MessagingInterface::kPreLoadGame:

	case F4SE::MessagingInterface::kPostLoadGame:
		if (reinterpret_cast<bool>(msg->data)) {
			initSpecialHooks();
			gameLoadingSave = true;
		}
		break;
	case F4SE::MessagingInterface::kPreSaveGame:

	case F4SE::MessagingInterface::kPostSaveGame:

	case F4SE::MessagingInterface::kDeleteGame:

	case F4SE::MessagingInterface::kInputLoaded:

	case F4SE::MessagingInterface::kNewGame:
		initSpecialHooks();
		gameLoadingSave = true;
		break;
	case F4SE::MessagingInterface::kGameLoaded:
		
	case F4SE::MessagingInterface::kGameDataReady:
		if (reinterpret_cast<bool>(msg->data)) {
			initPlugin();
			initHooks();
			WeaponInfo::InitSDM();
		}
		break;
	}
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
	a_info->infoVersion = F4SE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_f4se->IsEditor()) {
		stl::report_and_fail(fmt::format(FMT_STRING("loaded in editor")));
		return false;
	}

	const auto ver = a_f4se->RuntimeVersion();
	if (ver < F4SE::RUNTIME_1_10_162) {
		stl::report_and_fail(fmt::format(FMT_STRING("unsupported runtime v{:s}"), ver.string()));
		return false;
	}

	F4SE::AllocTrampoline(8 * 8);

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	initLog();
	logger::info(FMT_STRING("{:s} Loaded"), Version::PROJECT);
	F4SE::Init(a_f4se);
	
	g_trampoline = &F4SE::GetTrampoline();
	g_taskInterface = F4SE::GetTaskInterface();
	g_pluginHandle = F4SE::GetPluginHandle();
	g_messaging = F4SE::GetMessagingInterface();

	if (!g_messaging) {
		logCritical("Couldn't get messaging interface");
		return false;
	}
	if (g_messaging->RegisterListener(OnF4SEMessage)) {
		logInfo("Registered listener");
	}
	return true;
}
