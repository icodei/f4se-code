// F4SE
#include "common/IDebugLog.h"  // IDebugLog
#include <f4se/PluginAPI.h>

#include <shlobj.h>	// CSIDL_MYCODUMENTS

// User Defined Header
#include "Global.h"

PluginHandle			g_pluginHandle = kPluginHandle_Invalid;
F4SEMessagingInterface* g_messaging = NULL;

bool ignore = false;
bool isEmptyReload = false;
bool logEnabled = true;
bool oncePerSession = false;
bool processCurrentScope = false;
bool processCurrentWeap = false;
bool readyForRender = false;
bool reloadEnd = true;
bool reloadStarted = false;

int currentAmmoCount = 0;
int ammoCapacity = 0;
int totalAmmoCount = 0;
int incrementor = 0;
int toAdd = 0;

BSGeometry* ScopeTextureLoader = nullptr;
BSEffectShaderData* effectShaderData = nullptr;
TESEffectShader* ThermalFXS = nullptr;
BGSKeyword* ThermalScopeKeyword = nullptr;
BGSKeyword* reloadSequentialKeyword = nullptr;
TESObjectWEAP::InstanceData* currentWeapInstance = nullptr;

void initGameStartData() {
	reloadStarted = false;
	reloadEnd = true;
	processCurrentWeap = false;
	processCurrentScope = false;
	ignore = false;
	readyForRender = false;
}

void OnF4SEMessage(F4SEMessagingInterface::Message* msg) {
	switch (msg->type) {
	case F4SEMessagingInterface::kMessage_GameLoaded:
		if (GetForms()) {
			log("Got Forms");
		} else {
			log("Unable to get one of the form, game wont work");
		}
		if (!Install()) {
			log("Couldn't install hooks");
		}
		break;
	case F4SEMessagingInterface::kMessage_GameDataReady:
	case F4SEMessagingInterface::kMessage_NewGame:
		if (!oncePerSession) {
			if (!RegisterAfterLoadEvents()) {
				//log("Unable to register for events on new game");
			}
			oncePerSession = true;
		}
		break;
	case F4SEMessagingInterface::kMessage_PostLoadGame:
		initGameStartData();
		FillWeaponInfo();
		break;
	}
}

/* Plugin Query */
extern "C" {
	bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info) {
		std::string logPath{ "\\My Games\\Fallout4\\F4SE\\" PLUGIN_NAME ".log" };
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, logPath.c_str());
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);
		_MESSAGE("%s %s Query", prefixLog().c_str(), PLUGIN_NAME);

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = PLUGIN_NAME;
		info->version = PLUGIN_VERSION;

		if (f4se->runtimeVersion != RUNTIME_VERSION_1_10_163) {
			_MESSAGE("%s Unsupported runtime version %d", prefixLog().c_str(), f4se->runtimeVersion);
			//return false;
		}

		g_pluginHandle = f4se->GetPluginHandle();

		// Get the messaging interface
		g_messaging = (F4SEMessagingInterface*)f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging) {
			log("Couldn't get messaging interface");
			return false;
		}
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface* f4se) {
		_MESSAGE("%s %s Loaded", prefixLog().c_str(), PLUGIN_NAME);

		if (g_messaging) {
			log("Registered Listener");
			g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);
		}

		if (!g_localTrampoline.Create(1024 * 64, nullptr)) {
			_ERROR("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return false;
		}

		if (!g_branchTrampoline.Create(1024 * 64)) {
			_ERROR("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return false;
		}

		if (!g_localTrampoline.Create(1024 * 64, nullptr)) {
			_ERROR("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return false;
		}
		return true;
	}
}