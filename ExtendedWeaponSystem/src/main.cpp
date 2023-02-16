#include "Global.h"

F4SE::PluginHandle g_pluginHandle = NULL;
F4SE::MessagingInterface* g_messaging;

void init() {
	pc = PlayerCharacter::GetSingleton();
	pcam = PlayerCamera::GetSingleton();
	logger::info(FMT_STRING("PlayerCharacter {}"), pc);
}

void OnF4SEMessage(F4SE::MessagingInterface::Message* msg) {
	if (msg->type == F4SE::MessagingInterface::kGameLoaded) {

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
		logger::critical("loaded in editor"sv);
		return false;
	}

	const auto ver = a_f4se->RuntimeVersion();
	if (ver < F4SE::RUNTIME_1_10_162) {
		logger::critical(FMT_STRING("unsupported runtime v{}"), ver.string());
		return false;
	}

	g_pluginHandle = F4SE::GetPluginHandle();
	g_messaging = const_cast<F4SE::MessagingInterface*>(F4SE::GetMessagingInterface());

	F4SE::AllocTrampoline(8 * 8);

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);

	F4SE::Trampoline& g_trampoline = F4SE::GetTrampoline();

	if (!g_messaging) {
		logger::critical("Couldn't get messaging interface"sv);
		return false;
	}

	if (g_messaging->RegisterListener(OnF4SEMessage)) {
		logger::info("Registered listener"sv);
	}

	return true;
}
