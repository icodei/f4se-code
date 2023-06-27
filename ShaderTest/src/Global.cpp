#include "Global.h"

F4SE::PluginHandle g_pluginHandle = NULL;
const F4SE::MessagingInterface* g_messaging = nullptr;
const F4SE::TaskInterface* g_taskInterface = nullptr;

PlayerCharacter* pc = nullptr;
PlayerCamera* pcam = nullptr;
PlayerControls* pcon = nullptr;

bool gameLoading = false;
bool gameLoadingSave = false;
