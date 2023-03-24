#include "Global.h"

bool ignore = false;
bool isEmptyReload = false;
bool logEnabled = true;
bool oncePerSession = false;
bool processCurrentScope = false;
bool processCurrentWeap = false;
bool readyForRender = false;
bool reloadEnd = true;
bool reloadStarted = false;

int ammoCapacity = 0;
int currentAmmoCount = 0;
int incrementor = 0;
int toAdd = 0;
int totalAmmoCount = 0;

BGSKeyword* reloadSequentialKeyword = nullptr;
BGSKeyword* ThermalScopeKeyword = nullptr;
TESObjectWEAP::InstanceData* currentWeapInstance = nullptr;
