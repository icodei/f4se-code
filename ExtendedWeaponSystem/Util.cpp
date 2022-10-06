#include "Global.h"

bool IsReloading() {
	if (!*g_player)
		return false;

	UInt32 reload_flag = ((*g_player)->actorState.flags >> 14) & 0xF;
	return reload_flag == 0x04;
}

bool IsSprinting() {
	if (!*g_player)
		return false;

	return (*g_player)->actorState.unk08 & 0x0100;
}

bool IsFirstPerson() {
	if (!*g_playerCamera)
		return false;

	return (*g_playerCamera)->cameraState == (*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_FirstPerson];
}

bool IsThirdPerson() {
	if (!*g_playerCamera)
		return false;

	return (*g_playerCamera)->cameraState == (*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_ThirdPerson2];
}

bool IsWeaponDrawn() {
	if (!*g_player)
		return false;

	return (*g_player)->actorState.IsWeaponDrawn();
}

bool IsButtonPressed(ButtonEvent* btnEvent) {
	if (btnEvent->isDown == BUTTON_UP && (btnEvent->timer > 0 && btnEvent->timer < BUTTON_HOLD_TIMER))
		return true;
	return false;
}

bool IsHoldingButton(ButtonEvent* btnEvent) {
	if (btnEvent->isDown == BUTTON_DOWN && btnEvent->timer >= BUTTON_HOLD_TIMER)
		return true;
	return false;
}

bool IsThrowableWeapon(UInt32 equipIndex) {
	return equipIndex == EquipIndex::kEquipIndex_Throwable;
}

RelocAddr <_IsReloadable> IsReloadable_Internal(0xE24B80);
bool IsWeaponReloadable() {
	if (!*g_player || !(*g_player)->middleProcess || !(*g_player)->middleProcess->unk08)
		return false;

	tArray<Actor::MiddleProcess::Data08::EquipData> equipDataArr = reinterpret_cast<tArray<Actor::MiddleProcess::Data08::EquipData> &>((*g_player)->middleProcess->unk08->equipData);
	if (equipDataArr.count == 0)
		return false;

	Actor::MiddleProcess::Data08::EquipData* equipData = nullptr;
	for (UInt32 ii = 0; ii < equipDataArr.count; ii++) {
		UInt32 equipIndex = *reinterpret_cast<UInt32*>(&equipDataArr.entries[ii].unk18);
		if (equipIndex == 0) {
			equipData = &equipDataArr.entries[ii];
			break;
		}
	}
	if (!equipData)
		return false;

	IsReloadableData data = { 0 };
	data.actor = *g_player;

	IsReloadableDataWrapper wrapper = { &data.unk00, &data.actor };

	return !IsReloadable_Internal(&wrapper, equipData);
}

RelocAddr <_SetAnimationVariableBoolPapyrus > SetAnimationVariableBoolPapyrusInternal(0x140EB30);
void SetAnimationVariableBoolPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, bool newVal) {
	SetAnimationVariableBoolPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

RelocAddr <_SetAnimationVariableIntPapyrus > SetAnimationVariableIntPapyrusInternal(0x140EC70);
void SetAnimationVariableIntPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, int newVal) {
	SetAnimationVariableIntPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

RelocAddr <_SetAnimationVariableFloatPapyrus > SetAnimationVariableFloatPapyrusInternal(0x140EBD0);
void SetAnimationVariableFloatPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, float newVal) {
	SetAnimationVariableFloatPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

RelocAddr <_SetSubGraphFloatVariablePapyrus > SetSubGraphFloatVariablePapyrusInternal(0x138B430);
void SetSubGraphFloatVariablePapyrus(Actor* actor, BSFixedString& asVariableName, float newVal) {
	SetSubGraphFloatVariablePapyrusInternal((*g_gameVM)->m_virtualMachine, 0, actor, asVariableName, newVal);
}

RelocAddr <_CreateNS_NiCamera_Create_Internal > CreateNS_NiCamera_Create_Internal(0x1BAE180);
NiObject* CreateNS_NiCamera_Create() {
	CreateNS_NiCamera_Create_Internal();
}

RelocAddr <_WornHasKeywordActor > Actor_WornHasKeyword(0x138C440);
bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword) {
	if (Actor_WornHasKeyword((*g_gameVM)->m_virtualMachine, 1, akTarget, akKeyword)) {
		return true;
	}
	return false;
}

bool HasKeyword(TESForm* form, BGSKeyword* keyword) {
	IKeywordFormBase* keywordFormBase = DYNAMIC_CAST(form, TESForm, IKeywordFormBase);
	if (keywordFormBase) {
		auto HasKeyword_Internal = GetVirtualFunction<_IKeywordFormBase_HasKeyword>(keywordFormBase, 1);
		if (HasKeyword_Internal(keywordFormBase, keyword, 0)) {
			return true;
		}
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

	if (keywordForm) {
		if (keywordForm->HasKeyword(kwdToCheck)) {
			return true;
		}
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
			}
			else {
				formID |= (mod->modIndex) << 24;
			}
			return LookupFormByID(formID);
		}
	}
	return nullptr;
}

//Gather the forms we need
bool GetForms() {
	bool toReturn = true;

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

	return toReturn;
}

BSFixedString GetDisplayName(ExtraDataList* extraDataList, TESForm* kbaseForm) {
	TESForm* baseForm = kbaseForm;

	if (baseForm) {
		if (extraDataList) {
			BSExtraData* extraData = extraDataList->GetByType(ExtraDataType::kExtraData_TextDisplayData);
			if (extraData) {
				ExtraTextDisplayData* displayText = DYNAMIC_CAST(extraData, BSExtraData, ExtraTextDisplayData);
				if (displayText) {
					return *CALL_MEMBER_FN(displayText, GetReferenceName)(baseForm);
				}
			}
		}

		TESFullName* pFullName = DYNAMIC_CAST(baseForm, TESForm, TESFullName);
		if (pFullName)
			return pFullName->name;
	}

	return BSFixedString();
}

std::string GetFullNameWEAP(TESObjectWEAP* weap) {
	TESFullName* pFullName = DYNAMIC_CAST(weap, TESObjectWEAP, TESFullName);
	std::string sName = (pFullName->name).c_str();
	return sName;
}

const tArray<Actor::MiddleProcess::Data08::EquipData>* GetEquipDataArray() {
	if (!*g_player || !(*g_player)->middleProcess || !(*g_player)->middleProcess->unk08)
		return nullptr;

	tArray<Actor::MiddleProcess::Data08::EquipData> equipDataArray = reinterpret_cast<tArray<Actor::MiddleProcess::Data08::EquipData>&>((*g_player)->middleProcess->unk08->equipData);
	if (equipDataArray.count == 0)
		return nullptr;

	return &reinterpret_cast<tArray<Actor::MiddleProcess::Data08::EquipData>&>((*g_player)->middleProcess->unk08->equipData);
}

Actor::MiddleProcess::Data08::EquipData* GetEquipDataByFormID(UInt32 formId) {
	const tArray<Actor::MiddleProcess::Data08::EquipData>* equipDataArray = GetEquipDataArray();
	if (!equipDataArray)
		return nullptr;

	for (UInt32 ii = 0; ii < equipDataArray->count; ii++) {
		if (equipDataArray->entries[ii].item->formID == formId)
			return &equipDataArray->entries[ii];
	}

	return nullptr;
}

Actor::MiddleProcess::Data08::EquipData* GetEquipDataByEquipIndex(EquipIndex equipIndex) {
	const tArray<Actor::MiddleProcess::Data08::EquipData>* equipDataArray = GetEquipDataArray();
	if (!equipDataArray)
		return nullptr;

	for (UInt32 i = 0; i < equipDataArray->count; i++) {
		UInt32 eIdx = reinterpret_cast<UInt32&>(equipDataArray->entries[i].unk18);
		if (eIdx == equipIndex)
			return &equipDataArray->entries[i];
	}
	return nullptr;
}

TESObjectWEAP::InstanceData* GetWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst) {
	TESObjectWEAP::InstanceData* weapInstData = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(weapInst, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
	if (weapInstData)
		return weapInstData;

	TESObjectWEAP* objWeap = DYNAMIC_CAST(weapForm, TESForm, TESObjectWEAP);
	if (!objWeap)
		return nullptr;

	return &objWeap->weapData;
}

UInt32 GetInventoryItemCount(Actor* actor, TESForm* item) {
	if (!actor || !item)
		return 0;

	BGSInventoryList* inventory = actor->inventoryList;
	if (!inventory)
		return 0;

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

void FillWeaponInfo() {
	Actor::MiddleProcess::Data08::EquipData* equipData = GetEquipDataByEquipIndex(EquipIndex::kEquipIndex_Default);
	if (equipData) {
		TESObjectWEAP* weap = DYNAMIC_CAST(equipData->item, TESForm, TESObjectWEAP);;
		TESObjectWEAP::InstanceData* equippedWeaponInstance = GetWeaponInstanceData(equipData->item, equipData->instanceData);
		ammoCapacity = equippedWeaponInstance->ammoCapacity;
		currentAmmoCount = equipData->equippedData->unk18;
		totalAmmoCount = GetInventoryItemCount(*g_player, equippedWeaponInstance->ammo);

		logIfNeeded("Game Loaded. Getting Initial Weapon Stats");
		logIfNeeded(";======================================================================================;");
		logIfNeeded("Weapon: " + GetFullNameWEAP(weap));
		logIfNeeded("TotalAmmoCount: " + std::to_string(totalAmmoCount));
		logIfNeeded("CurrentAmmoCount: " + std::to_string(currentAmmoCount));
		logIfNeeded("AmmoCapacity: " + std::to_string(ammoCapacity));
		if (WornHasKeywordActor(*g_player, reloadSequentialKeyword)) {
			processCurrentWeap = true;
			logIfNeeded(GetFullNameWEAP(weap) + " has the reloadSequentialKeyword.");
		}
		else {
			processCurrentWeap = false;
			logIfNeeded(GetFullNameWEAP(weap) + " does not have the reloadSequentialKeyword.");
		}
		if (WornHasKeywordActor(*g_player, ThermalScopeKeyword)) {
			processCurrentScope = true;
			logIfNeeded(GetFullNameWEAP(weap) + " has the ThermalScopeKeyword.");
		}
		else {
			processCurrentScope = false;
			logIfNeeded(GetFullNameWEAP(weap) + "does not have the ThermalScopeKeyword.");
		}
		logIfNeeded(";======================================================================================;");
	}
}

//Equip Handler
void HanldeWeaponEquip(TESObjectWEAP::InstanceData* weap) {
	TESObjectWEAP::InstanceData* equippedWeaponInstance = weap;
	TESObjectWEAP* weapBase = (TESObjectWEAP*)equippedWeaponInstance;
	if (HasKeywordInstWEAP(weap, reloadSequentialKeyword) || (WornHasKeywordActor(*g_player, reloadSequentialKeyword))) {
		processCurrentWeap = true;
		if (equippedWeaponInstance && processCurrentWeap) {
			ammoCapacity = equippedWeaponInstance->ammoCapacity;
			weapInstance = equippedWeaponInstance;
			logIfNeeded("reloadSequentialKeyword found. We should process this weapon for sequential reloads.");
			logIfNeeded("weapon instance equipped with ammo capacity of:" + std::to_string(weapInstance->ammoCapacity));
		}
	}
	else {
		logIfNeeded("No reloadSequentialKeyword found. We can ignore this weapon for sequential reloads.");
		weapInstance = nullptr;
		processCurrentWeap = false;
	}

	NiAVObject* player3D = nullptr;
	NiAVObject* objGeom = nullptr;
	BSEffectShaderProperty* shadeprop;
	BSEffectShaderMaterial* shadematerial;
	BSFixedString targetName = "TextureLoader";
	if (HasKeywordInstWEAP(weap, ThermalScopeKeyword) || (WornHasKeywordActor(*g_player, ThermalScopeKeyword))) {
		logIfNeeded("ThermalScopeKeyword found. We should process this weapon for special scope utility.");
		if (player3D == nullptr || objGeom == nullptr) {
			player3D = (*g_player)->GetActorRootNode(true);
			if (player3D != nullptr) {
				logIfNeeded("Got player 3D.");
				//objGeom = player3D->GetObjectByName(targetName);
				objGeom = BSUtilities::GetObjectByName(player3D, targetName, true, true);
				//if (objGeom == nullptr) {
				//	logIfNeeded("NiNode vtable unable to find Scope Geom, Trying with BSUtilities now...");
				//	objGeom = BSUtilities::GetObjectByName(player3D, targetName, true, true);
				//}
				if (objGeom) {
					logIfNeeded("Found the geometry of the scope.");
					ScopeTextureLoader = objGeom->GetAsBSGeometry();
					shadeprop = (BSEffectShaderProperty*)ScopeTextureLoader->shaderProperty.m_pObject;
					shadematerial = shadeprop->QEffectShaderMaterial();
					shadeData = ThermalFXS->CreateEffectShaderData(ScopeTextureLoader, shadematerial->spBaseTexture.m_pObject, shadematerial->spBaseTexture.m_pObject, shadematerial->spBaseTexture.m_pObject);
					shadeprop->SetEffectShaderData(shadeData);
					shadeprop->SetupGeometry(ScopeTextureLoader);
					logIfNeeded("Scope materials setup complete.");
					processCurrentScope = true;
				}
				else {
					logIfNeeded("Could not find the geometry of the scope.");
					(ThermalFXS)->StopEffectShader(ThermalFXS, ScopeTextureLoader, shadeData);
					processCurrentScope = false;
					ScopeTextureLoader = nullptr;
					objGeom = nullptr;
					player3D = nullptr;
					shadeprop = nullptr;
					shadematerial = nullptr;
				}
			}
		}
	}
	else {
		logIfNeeded("No ThermalScopeKeyword found. We can ignore this weapon for special scope utility.");
		processCurrentScope = false;
		ScopeTextureLoader = nullptr;
		objGeom = nullptr;
		player3D = nullptr;
	}
}

//code from bingle
//void ReloadSubgraph()
//{
//	uint64_t oldSubgraph = p->currentProcess->middleHigh->currentWeaponSubGraphID[1].identifier;
//	p->HandleItemEquip(false);
//	std::thread([oldSubgraph]() -> void {
//		int timeout = 0;
//		while (oldSubgraph == p->currentProcess->middleHigh->currentWeaponSubGraphID[1].identifier && timeout < 100) {
//			++timeout;
//			std::this_thread::sleep_for(std::chrono::milliseconds(10));
//		}
//		*(float*)((uintptr_t)pcam->cameraStates[CameraState::kFirstPerson].get() + 0x78) = lastSightedTransition;
//		taskInterface->AddTask([]() {
//			F4::BGSAnimationSystemUtils::InitializeActorInstant(*p, false);
//			if (sideAim) {
//				NotifyWeaponGraphManager("Extend");
//			}
//			if (wantSighted && !UI::GetSingleton()->GetMenu("ScopeMenu").get()) {
//				pcon->DoAction(DEFAULT_OBJECT::kActionSighted, 2);
//				p->SetGraphVariableInt("iSyncWeaponDrawState", 1);
//				p->SetGraphVariableInt("iSyncSightedState", 1);
//				p->UpdateAnimation(0.05f);
//				NiUpdateData ud = NiUpdateData();
//				ud.unk10 = 0x303;
//				p->Get3D()->UpdateSelectedDownwardPass(ud, 0);
//			}
//			});
//		}).detach();
//}

//suggestions by Bingle
//BGSAnimationSystemUtils::InitializeActorInstant
//Actor::HandleItemEquip
//AIProcess::RequestLoadAnimationsForWeaponChange

void reloadStop() {
	logIfNeeded("Stopping reload loop");
	reloadEndHandle();
	(*g_player)->animGraphHolder.SetGraphVariableBool(BSFixedString("bReloadLoop"), false);
}

void reloadContinue() {
	logIfNeeded("Continuing reload loop");
	(*g_player)->animGraphHolder.SetGraphVariableBool(BSFixedString("bReloadLoop"), true);
	(*g_player)->animGraphHolder.NotifyAnimationGraphImpl(BSFixedString("reloadSequentialReserveStart"));
}

void reloadContinueFromEmpty() {
	logIfNeeded("Continuing reload loop");
	(*g_player)->animGraphHolder.SetGraphVariableBool(BSFixedString("bReloadLoop"), true);
	(*g_player)->animGraphHolder.NotifyAnimationGraphImpl(BSFixedString("reloadSequentialStart"));
}

//ready needed stuff when reload is started
void reloadStartHandle() {
	logIfNeeded("reloadStartHandle");
	incrementor = 0;
	toAdd = ammoCapacity - currentAmmoCount;
	reloadStarted = true;
	reloadEnd = false;
	SetWeapAmmoCapacity(currentAmmoCount);
}

//clear needed stuff when reload ends
void reloadEndHandle() {
	logIfNeeded("reloadEndHandle");
	reloadEnd = true;
	reloadStarted = false;
	incrementor = 0;
	toAdd = 0;
	SetWeapAmmoCapacity(ammoCapacity);
}

//Stops the reload early if there is not enough ammo in the inventory
void StopLesserAmmo() {
	if ((totalAmmoCount + currentAmmoCount) - ammoCapacity < 0) {
		toAdd = totalAmmoCount;
	}
}

//Set weapon capacity to needed amount to be sure reloadComplete fills needed amount of ammo
void SetWeapAmmoCapacity(int amount) {
	if (weapInstance) {
		if (amount > ammoCapacity) {
			weapInstance->ammoCapacity = ammoCapacity;
			logIfNeeded("ammo count set to: " + std::to_string(ammoCapacity));
		}
		else {
			weapInstance->ammoCapacity = amount;
			logIfNeeded("ammo count set to: " + std::to_string(amount));
		}
	}
	else {
		log("weapon instance is nullptr. Could not set ammo");
	}
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