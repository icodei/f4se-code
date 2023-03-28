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
bool weaponHasSequentialReload = false;
bool weaponHasSpeedReload = false;
bool weaponHasThermalScope = false;
bool weaponIsClosedBolt = false;
bool weaponIsOpenBolt = false;
bool weaponIsQueued = false;

//int weapAmmoCapacity = 0;
//int weapAmmoCurrentCount = 0;
//int weapAmmoIncrementor = 0;
//int weapAmmoToAdd = 0;
//int weapAmmoTotalCount = 0;

BGSKeyword* weaponHasSequentialReloadKeyword = nullptr;
BGSKeyword* weaponHasSpeedReloadKeyword = nullptr;
BGSKeyword* weaponHasThermalScopeKeyword = nullptr;
BGSKeyword* weaponIsClosedBoltKeyword = nullptr;
BGSKeyword* weaponIsOpenBoltKeyword = nullptr;

//TESObjectWEAP::InstanceData* currentWeapInstance = nullptr;
