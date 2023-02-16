#include "Global.h"

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName) {
	for (int i = 0; i < globalEvents->eventSources.count; i++) {
		const char* name = GetObjectClassName(globalEvents->eventSources[i]) + 15;
		if (strstr(name, dispatcherName) == name) {
			return &globalEvents->eventSources[i]->eventDispatcher;
		}
	}
	return nullptr;
}

bool IsReloading() {
	if (!*g_player) {
		return false;
	}
	UInt32 reload_flag = ((*g_player)->ActorState::flags >> 14) & 0xF;
	return reload_flag == 0x04;
}

bool IsSprinting() {
	if (!*g_player) {
		return false;
	}
	return (*g_player)->ActorState::unk08 & 0x0100;
}

bool IsFirstPerson() {
	if (!*g_playerCamera) {
		return false;
	}
	return (*g_playerCamera)->currentState == (*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_FirstPerson];
}

bool IsThirdPerson() {
	if (!*g_playerCamera) {
		return false;
	}
	return (*g_playerCamera)->currentState == (*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_ThirdPerson2];
}

bool IsWeaponDrawn() {
	if (!*g_player) {
		return false;
	}
	return (*g_player)->IsWeaponDrawn();
}

bool IsButtonPressed(ButtonEvent* btnEvent) {
	if (btnEvent->isDown == BUTTON_UP && (btnEvent->timer > 0 && btnEvent->timer < BUTTON_HOLD_TIMER)) {
		return true;
	}
	return false;
}

bool IsHoldingButton(ButtonEvent* btnEvent) {
	if (btnEvent->isDown == BUTTON_DOWN && btnEvent->timer >= BUTTON_HOLD_TIMER) {
		return true;
	}
	return false;
}

bool IsThrowableWeapon(UInt32 equipIndex) {
	return equipIndex == EquipIndex::kEquipIndex_Throwable;
}

typedef bool (*_IsReloadable)(IsReloadableDataWrapper*, EquippedItem*);
RelocAddr <_IsReloadable> IsReloadable_Internal(0xE24B80);
bool IsWeaponReloadable() {
	if (!*g_player || !(*g_player)->currentProcess || !(*g_player)->currentProcess->middleHigh) { 
		return false;
	}

	const BSTArray<EquippedItem> equipDataArr = *GetPlayerEquippedItemArray();
	if (equipDataArr.count == 0) {
		return false;
	}

	EquippedItem* equipData = nullptr;
	for (UInt32 i = 0; i < equipDataArr.count; i++) {
		UInt32 equipIndex = equipDataArr.entries[i].equipIndex.index;
		if (equipIndex == 0) {
			equipData = &equipDataArr.entries[i];
			break;
		}
	}
	if (!equipData) { 
		return false;
	}

	IsReloadableData data = { 0 };
	data.actor = *g_player;

	IsReloadableDataWrapper wrapper = { &data.unk00, &data.actor };

	return !IsReloadable_Internal(&wrapper, equipData);
}

typedef bool(*_WornHasKeywordActor)(VirtualMachine* vm, UInt32 stackId, Actor* akTarget, BGSKeyword* akKeyword);
RelocAddr <_WornHasKeywordActor> Actor_WornHasKeyword(0x138C440);
bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword) {
	if (Actor_WornHasKeyword((*g_gameVM)->m_virtualMachine, 1, akTarget, akKeyword)) {
		return true;
	}
	return false;
}

typedef bool(*_IKeywordFormBase_HasKeyword)(IKeywordFormBase* keywordFormBase, BGSKeyword* keyword, UInt32 unk3);
bool HasKeyword(TESForm* form, BGSKeyword* keyword) {
	IKeywordFormBase* keywordFormBase = DYNAMIC_CAST(form, TESForm, IKeywordFormBase);
	if (!keywordFormBase) {
		logIfNeeded("HasKeyword:: Failed to cast keyword to base type.");
		return false;
	}
	auto HasKeyword_Internal = GetVirtualFunction<_IKeywordFormBase_HasKeyword>(keywordFormBase, 1);
	if (!HasKeyword_Internal) {
		logIfNeeded("HasKeyword:: Failed to get virtual function.");
		return false;
	}
	if (HasKeyword_Internal(keywordFormBase, keyword, 0)) {
		return true;
	}
	return false;
}

bool HasKeywordInstWEAP(TESObjectWEAP::InstanceData* thisInstance, BGSKeyword* kwdToCheck) {
	BGSKeywordForm* keywordForm = nullptr;
	keywordForm = thisInstance->keywords;
	if (!keywordForm) {
		logIfNeeded("This weapInstance has no keywords");
		return false;
	}

	if (keywordForm->HasKeyword(kwdToCheck)) {
		return true;
	}

	for (UInt32 i = 0; i < keywordForm->numKeywords; i++) {
		BGSKeyword* curr = keywordForm->keywords[i];
		if (curr == kwdToCheck) {
			return true;
		}
	}
	return false;
}

TESForm* GetFormFromIdentifier(const std::string& identifier) {
	auto delimiter = identifier.find('|');
	if (delimiter != std::string::npos) {
		std::string modName = identifier.substr(0, delimiter);
		std::string modForm = identifier.substr(delimiter + 1);

		const ModInfo* mod = (*g_dataHandler)->LookupModByName(modName.c_str());
		if (mod && mod->modIndex != -1) {
			UInt32 formID = std::stoul(modForm, nullptr, 16) & 0xFFFFFF;
			UInt32 flags = GetOffset<UInt32>(mod, 0x334);
			if (flags & (1 << 9)) {
				// ESL
				formID &= 0xFFF;
				formID |= 0xFE << 24;
				formID |= GetOffset<UInt16>(mod, 0x372) << 12;	// ESL load order
			} else {
				formID |= (mod->modIndex) << 24;
			}
			return LookupFormByID(formID);
		}
	}
	return nullptr;
}

//Gather the forms we need
bool GetForms() {

	reloadSequentialKeyword = reinterpret_cast<BGSKeyword*>(GetFormFromIdentifier("ExtendedWeaponSystem.esm|1ED4"));
	if (!reloadSequentialKeyword) {
		log("Unable to get reloadSequentialKeyword, you are lacking some file/files");
	}
	ThermalScopeKeyword = reinterpret_cast<BGSKeyword*>(GetFormFromIdentifier("Code_SharedAttachments.esm|6436"));
	if (!ThermalScopeKeyword) {
		log("Unable to get ThermalScopeKeyword, you are lacking some file/files");
	}
	ThermalFXS = reinterpret_cast<TESEffectShader*>(GetFormFromIdentifier("Code_SharedAttachments.esm|5BCB"));
	if (!ThermalFXS) {
		log("Unable to get ThermalFXS, you are lacking some file/files");
	}
	return true;
}

BSFixedString GetDisplayName(ExtraDataList* extraDataList, TESForm* kbaseForm) {

	if (!kbaseForm && !extraDataList) {
		return BSFixedString();
	}

	if (!kbaseForm) {
		BSExtraData* extraData = extraDataList->GetByType(ExtraDataType::kExtraData_TextDisplayData);
		ExtraTextDisplayData* displayText = DYNAMIC_CAST(extraData, BSExtraData, ExtraTextDisplayData);
		return *CALL_MEMBER_FN(displayText, GetReferenceName)(kbaseForm);
	}

	if (!extraDataList) {
		TESFullName* pFullName = DYNAMIC_CAST(kbaseForm, TESForm, TESFullName);
		return pFullName->name;
	}
	return BSFixedString();
}

std::string GetFullNameWEAP(TESObjectWEAP* weap) {
	TESFullName* pFullName = DYNAMIC_CAST(weap, TESObjectWEAP, TESFullName);
	std::string sName = (pFullName->name).c_str();
	return sName;
}

const BSTArray<EquippedItem>* GetPlayerEquippedItemArray() {
	if (!*g_player || !(*g_player)->currentProcess || !(*g_player)->currentProcess->middleHigh) { 
		return nullptr;
	}

	BSTArray<EquippedItem>* equipDataArray = (*g_player)->currentProcess->GetEquippedItemArray();
	if (equipDataArray->count == 0) { 
		return nullptr;
	}
	return equipDataArray;
}

EquippedItem* GetPlayerEquippedItemByFormID(UInt32 formId) {
	const BSTArray<EquippedItem>* equipDataArray = GetPlayerEquippedItemArray();
	if (!equipDataArray) {
		return nullptr;
	}

	for (UInt32 i = 0; i < equipDataArray->count; i++) {
		if (equipDataArray->entries[i].item.object->formID == formId) {
			return &equipDataArray->entries[i];
		}
	}
	return nullptr;
}

EquippedItem* GetPlayerEquippedItemByEquipIndex(EquipIndex equipIndex) {
	EquippedItem item;
	BGSEquipIndex bgsindex = BGSEquipIndex(equipIndex);

	if ((*g_player)->currentProcess->GetEquippedItem(bgsindex, item)) {
		return &item;
	}

	const BSTArray<EquippedItem>* equipDataArray = GetPlayerEquippedItemArray();
	if (!equipDataArray) {
		return nullptr;
	}
	for (UInt32 i = 0; i < equipDataArray->count; i++) {
		UInt32 eIdx = equipDataArray->entries[i].equipIndex.index;
		if (eIdx == equipIndex) {
			return &equipDataArray->entries[i];
		}
	}
	return nullptr;
}

EquippedWeapon* GetPlayerEquippedWeaponByEquipIndex(EquipIndex equipIndex) {
	EquippedWeapon weapon;
	BGSEquipIndex bgsindex = BGSEquipIndex(equipIndex);

	if (!(*g_player)->currentProcess) {
		return nullptr;
	}

	if ((*g_player)->currentProcess->GetEquippedWeapon(bgsindex, weapon)) {
		return &weapon;
	}

	BSTArray<EquippedWeapon>* equipDataArray;
	(*g_player)->currentProcess->GetEquippedWeapons(*equipDataArray);
	if (!equipDataArray) {
		return nullptr;
	}
	for (UInt32 i = 0; i < equipDataArray->count; i++) {
		UInt32 eIdx = equipDataArray->entries[i].equipIndex.index;
		if (eIdx == equipIndex) {
			return &equipDataArray->entries[i];
		}
	}
	return nullptr;
}

EquippedWeaponData* GetPlayerEquippedWeaponDataByEquipIndex(EquipIndex equipIndex) {
	NiPointer<EquippedWeaponData> spWeaponData;
	BGSEquipIndex bgsindex = BGSEquipIndex(equipIndex);

	if (!(*g_player)->currentProcess) {
		return nullptr;
	}

	if ((*g_player)->currentProcess->GetEquippedWeaponData(bgsindex, spWeaponData)) {
		return spWeaponData.get();
	}
	return nullptr;
}

TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst) {
	if (!weapForm || !weapInst) {
		return nullptr;
	}

	TESObjectWEAP::InstanceData* weapInstData = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(weapInst, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
	if (weapInstData) {
		return weapInstData;
	}

	TESObjectWEAP* objWeap = DYNAMIC_CAST(weapForm, TESForm, TESObjectWEAP);
	if (!objWeap) { 
		return nullptr;
	}
	return &objWeap->weapData;
}

TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedItem& a_item) {
	if (a_item.item.object->formType != 43) {
		return nullptr;
	}
	TESObjectWEAP::InstanceData* weapInstData = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(a_item.item.instanceData, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
	if (!weapInstData) {
		return nullptr;
	}
	return weapInstData;
}

TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedWeapon& a_weapon) {
	if (a_weapon.weapon.object->formType != 43) {
		return nullptr;
	}
	TESObjectWEAP::InstanceData* weapInstData = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(a_weapon.weapon.instanceData, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
	if (!weapInstData) {
		return nullptr;
	}
	return weapInstData;
}

UInt32 GetInventoryItemCount(Actor* actor, TESForm* item) {
	if (!actor || !item) {
		return NULL;
	}

	BGSInventoryList* inventory = actor->inventoryList;
	if (!inventory) {
		return NULL;
	}

	UInt32 totalItemCount = 0;
	inventory->inventoryLock.LockForRead();
	for (UInt32 i = 0; i < inventory->items.count; i++) {
		if (inventory->items[i].form == item) {
			BGSInventoryItem::Stack* sp = inventory->items[i].stack;
			while (sp) {
				totalItemCount += sp->count;
				sp = sp->next;
			}
			break;
		}
	}
	inventory->inventoryLock.Unlock();

	return totalItemCount;
}



NiAVObject* GetByNameHelper(const BSFixedString& name) {
	BSFadeNode* player3D = (*g_player) ? (BSFadeNode*)(*g_player)->GetObjectRootNode() : nullptr;
	if (!player3D) {
		return nullptr;
	}
	NiAVObject* obj;
	obj = BSUtilities::GetObjectByName(player3D, name, true, true);
	if (!obj) {
		return nullptr;
	}
	return obj;
	/*
	if (!obj) {
		logIfNeeded("Unable to find scope geometry with BSUtilities. Now attempting to find it in the FlattenedGeometryData...");
		for (UInt32 i = 0; i < player3D->kGeomArray.count; i++) {
			BSGeometry* object = player3D->kGeomArray.entries[i] ? player3D->kGeomArray.entries[i]->spGeometry.get() : nullptr;
			if (object->m_name == name) {
				obj = (NiAVObject*)object;
				return obj;
			}
		}
	}
	if (!obj) {
		logIfNeeded("Unable to find scope geometry in FlattenedGeometryData. Now attempting to find it in the ninode children...");
		for (UInt32 i = 0; i < player3D->m_children.m_emptyRunStart; i++) {
			NiPointer<NiAVObject> object(player3D->m_children.m_data[i]);
			if (object) {
				if (object->m_name == name) {
					obj = object.get();
					return obj;
				}
			}
		}
	}
	*/
}


// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

const std::string prefixLog() {
	std::stringstream buffer;
	buffer << "[" << currentDateTime() << "] [EWS] ";
	return(buffer.str());
}

//Write message log only if logEnabled == True
void logIfNeeded(std::string text) {
	if (logEnabled) {
		_MESSAGE("%s %s", prefixLog().c_str(), text.c_str());
	}
}

//Write message log always
void log(std::string text) {
	_MESSAGE("%s %s", prefixLog().c_str(), text.c_str());
}