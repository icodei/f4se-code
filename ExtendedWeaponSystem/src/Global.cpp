#include "Global.h"

F4SE::PluginHandle g_pluginHandle = NULL;
const F4SE::MessagingInterface* g_messaging = nullptr;
const F4SE::TaskInterface* g_taskInterface = nullptr;
const F4SE::Trampoline* g_trampoline = nullptr;

PlayerCharacter* pc = nullptr;
PlayerCamera* pcam = nullptr;

bool gameLoading = false;
bool gameLoadingSave = false;
bool ignoreEquip = false;
bool ignoreScope = false;
bool isEmptyReload = false;
bool readyForRender = false;
bool reloadHasEnded = true;
bool reloadHasStarted = false;
bool weaponHasScopeNV = false;
bool weaponHasScopePIP = false;
bool weaponHasScopeThermal = false;
bool weaponHasSequentialReload = false;
bool weaponHasSpeedReload = false;
bool weaponIsClosedBolt = false;
bool weaponIsOpenBolt = false;
bool weaponIsQueued = false;

BGSKeyword* weaponHasSequentialReloadKeyword = nullptr;
BGSKeyword* weaponHasSpeedReloadKeyword = nullptr;
BGSKeyword* weaponHasThermalScopeKeyword = nullptr;
BGSKeyword* weaponIsClosedBoltKeyword = nullptr;
BGSKeyword* weaponIsOpenBoltKeyword = nullptr;
