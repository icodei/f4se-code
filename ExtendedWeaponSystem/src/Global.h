#pragma once
#include "Custom Renderer/ScopeCamera.h"

#include "Custom Renderer/CustomRenderer.h"
#include "Custom Renderer/ExtraCameraManager.h"
#include "Custom Renderer/ScopeRendererManager.h"
#include "Custom Renderer/ScopeShaders.h"

#include "AnimationFunctions.h"
#include "Hooks.h"
#include "ReloadHandlers.h"
#include "Util.h"
#include "WeaponHandlers.h"

static PlayerCharacter* pc;
static PlayerCamera* pcam;

static bool ignore;
static bool isEmptyReload;
static bool logEnabled;
static bool oncePerSession;
static bool processCurrentScope;
static bool processCurrentWeap;
static bool readyForRender;
static bool reloadEnd;
static bool reloadStarted;

static int ammoCapacity;
static int currentAmmoCount;
static int incrementor;
static int toAdd;
static int totalAmmoCount;

static BGSKeyword* reloadSequentialKeyword;
static BGSKeyword* ThermalScopeKeyword;
static TESObjectWEAP::InstanceData* currentWeapInstance;

static const BSFixedString Event00("Event00");
static const BSFixedString LoadingMenu("LoadingMenu");
static const BSFixedString pipboyClosed("pipboyClosed");
static const BSFixedString pipboyOpened("pipboyOpened");
static const BSFixedString ReloadComplete("ReloadComplete");
static const BSFixedString ReloadEnd("ReloadEnd");
static const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");
static const BSFixedString reloadSequentialStart("reloadSequentialStart");
static const BSFixedString sightedStateEnter("sightedStateEnter");
static const BSFixedString sightedStateExit("sightedStateExit");
static const BSFixedString weapEquip("weapEquip");
static const BSFixedString weapForceEquip("weapForceEquip");
static const BSFixedString weaponDraw("weaponDraw");
static const BSFixedString WeaponFire("WeaponFire");
static const BSFixedString weaponInstantDown("weaponInstantDown");
static const BSFixedString weapUnequip("weapUnequip");

#define _BYTE std::uint8_t
#define _WORD std::uint16_t
#define _DWORD std::uint32_t
#define _QWORD std::uint64_t

#define BYTEn(x, n) (*((_BYTE*)&(x) + n))
#define WORDn(x, n) (*((_WORD*)&(x) + n))
#define DWORDn(x, n) (*((_DWORD*)&(x) + n))

#define LODWORD(x) DWORDn(x, LOW_IND(x, _DWORD))
#define HIDWORD(x) DWORDn(x, HIGH_IND(x, _DWORD))
#define BYTE0(x) BYTEn(x, 0)
#define BYTE1(x) BYTEn(x, 1)  // byte 1 (counting from 0)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define BYTE8(x) BYTEn(x, 8)
#define BYTE9(x) BYTEn(x, 9)
#define BYTE10(x) BYTEn(x, 10)
#define BYTE11(x) BYTEn(x, 11)
#define BYTE12(x) BYTEn(x, 12)
#define BYTE13(x) BYTEn(x, 13)
#define BYTE14(x) BYTEn(x, 14)
#define BYTE15(x) BYTEn(x, 15)
#define WORD1(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2)  // third word of the object, unsigned
#define WORD3(x) WORDn(x, 3)
#define WORD4(x) WORDn(x, 4)
#define WORD5(x) WORDn(x, 5)
#define WORD6(x) WORDn(x, 6)
#define WORD7(x) WORDn(x, 7)

#define FToRGB 0.0039215689F

#define FltPId2 1.570796371F
#define FltPI 3.141592741F
#define FltPIx2 6.283185482F
#define Flt2dPI 0.6366197467F
#define FltPId180 0.01745329238F
#define Flt180dPI 57.29578018F
#define DblPId180 0.017453292519943295F
#define Dbl180dPI 57.29577951308232F

#define BUTTON_UP 0.0F
#define BUTTON_DOWN 1.0F
#define BUTTON_HOLD_TIMER 0.4F
