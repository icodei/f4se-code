#pragma once

enum AmmoType {
	kAmmoType_Default = 0x00,
	kAmmoType_Charging = 0x01,
	kAmmoType_FusionCore = 0x02,
	kAmmoType_NeverEnding = 0x04
};

enum EquipIndex {
	kEquipIndex_Default = 0,
	kEquipIndex_Throwable = 2
};

struct IsReloadableData {
	UInt64 unk00;
	Actor* actor;
};

struct IsReloadableDataWrapper {
	void* arg1;
	void* arg2;
};

bool IsReloading();
bool IsSprinting();
bool IsFirstPerson();
bool IsThirdPerson();
bool IsWeaponDrawn();

typedef bool (*_IsReloadable)(IsReloadableDataWrapper*, Actor::MiddleProcess::Data08::EquipData*);
bool IsWeaponReloadable();

bool IsButtonPressed(ButtonEvent* btnEvent);
bool IsHoldingButton(ButtonEvent* btnEvent);

template <typename T>
T GetVirtualFunction(void* baseObject, int vtblIndex) {
	uintptr_t* vtbl = reinterpret_cast<uintptr_t**>(baseObject)[0];
	return reinterpret_cast<T>(vtbl[vtblIndex]);
}

template <typename T>
T GetOffset(const void* baseObject, int offset) {
	return *reinterpret_cast<T*>((uintptr_t)baseObject + offset);
}

typedef bool(*_WornHasKeywordActor)(VirtualMachine* vm, UInt32 stackId, Actor* akTarget, BGSKeyword* akKeyword);
bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword);

typedef bool(*_IKeywordFormBase_HasKeyword)(IKeywordFormBase* keywordFormBase, BGSKeyword* keyword, UInt32 unk3);
bool HasKeyword(TESForm* form, BGSKeyword* keyword);
bool HasKeywordInstWEAP(TESObjectWEAP::InstanceData* thisInstance, BGSKeyword* kwdToCheck);
TESForm* GetFormFromIdentifier(const std::string& identifier);
bool GetForms();
BSFixedString GetDisplayName(ExtraDataList* extraDataList, TESForm* kbaseForm);
std::string GetFullNameWEAP(TESObjectWEAP* weap);
Actor::MiddleProcess::Data08::EquipData* GetEquipDataByFormID(UInt32 formId);
Actor::MiddleProcess::Data08::EquipData* GetEquipDataByEquipIndex(EquipIndex equipIndex);
TESObjectWEAP::InstanceData* GetWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst);
UInt32 GetInventoryItemCount(Actor* actor, TESForm* item);

void FillWeaponInfo();
void HanldeWeaponEquip(TESObjectWEAP::InstanceData* weap);
void HanldeWeaponEquipAfter3D();
NiAVObject* GetByNameHelper(const BSFixedString& name);
void SetupTextureLoaderWithEffectShader();
void SetupImageSpaceShader(BSGeometry* objGeom, bool active);
BSEffectShaderData* CreateEffectShaderDataCustom(TESEffectShader* shader, NiTexture* tex1, NiTexture* tex2, NiTexture* tex3);

void reloadStop();
void reloadContinue();
void reloadContinueFromEmpty();
void reloadStartHandle();
void reloadEndHandle();

void StopLesserAmmo();

void SetWeapAmmoCapacity(int amount);

const std::string currentDateTime();
const std::string prefixLog();
void logIfNeeded(std::string text);
void log(std::string text);

