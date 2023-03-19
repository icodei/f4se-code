#include "Global.h"

BSTEventSource<void*>* GetGlobalEventSource(BSTGlobalEvent_OLD* globalEvents, const char* globalName) {
	auto sources = (globalEvents->eventSources);
	for (auto elem = sources.begin(); elem != sources.end(); ++elem) {
		const char* name = GetObjectClassName(elem) + 15;
		if (globalName == name) {
			return (BSTEventSource<void*>*)&((elem));
		}
	}
	return nullptr;
}

const char* GetObjectClassNameImpl(const char* result, void* objBase) {
	using namespace RTTI;
	void** obj = (void**)objBase;
	CompleteObjectLocator** vtbl = (CompleteObjectLocator**)obj[0];
	CompleteObjectLocator* rtti = vtbl[-1];
	RVA<TypeDescriptor> typeDesc = rtti->typeDescriptor;

	// starts with ,?
	const char* _name = typeDesc->mangled_name();
	if ((_name[0] == '.') && (_name[1] == '?')) {
		// is at most 100 chars long
		for (uint32_t i = 0; i < 100; i++) {
			if (_name[i] == 0) {
				// remove the .?AV
				return _name + 4;
				break;
			}
		}
	}
	return result;
}

const char* GetObjectClassName(void* objBase) {
	const char* result = "<no rtti>";
	__try {
		result = GetObjectClassNameImpl(result, objBase);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		// return the default
	}

	return result;
}

bool IsReloading() {
	if (!pc) {
		return false;
	}
	return ((pc)->ActorState::gunState) == GUN_STATE::kReloading;
}

bool IsSprinting() {
	if (!pc) {
		return false;
	}
	return (pc)->ActorState::moveMode & 0x0100;
}

bool IsFirstPerson() {
	if (!pcam) {
		return false;
	}
	return (pcam)->currentState == (pcam)->cameraStates[CameraState::kFirstPerson];
}

bool IsThirdPerson() {
	if (!pcam) {
		return false;
	}
	return (pcam)->currentState == (pcam)->cameraStates[CameraState::k3rdPerson];
}

bool IsWeaponDrawn() {
	if (!pc) {
		return false;
	}
	return (pc)->GetWeaponMagicDrawn();
}

bool IsButtonPressed(ButtonEvent* btnEvent) {
	if (btnEvent->value == BUTTON_UP && (btnEvent->heldDownSecs > 0 && btnEvent->heldDownSecs < BUTTON_HOLD_TIMER)) {
		return true;
	}
	return false;
}

bool IsHoldingButton(ButtonEvent* btnEvent) {
	if (btnEvent->value == BUTTON_DOWN && btnEvent->heldDownSecs >= BUTTON_HOLD_TIMER) {
		return true;
	}
	return false;
}

bool IsThrowableWeapon(uint32_t equipIndex) {
	return equipIndex == EquipIndex::kEquipIndex_Throwable;
}

typedef bool (*_IsReloadable)(IsReloadableDataWrapper*, EquippedItem*);
bool IsWeaponReloadable() {
	if (!pc || !(pc)->currentProcess || !(pc)->currentProcess->middleHigh) {
		return false;
	}

	const BSTArray<EquippedItem> equipDataArr = *GetPlayerEquippedItemArray();
	if (equipDataArr.empty()) {
		return false;
	}

	EquippedItem* equipData = nullptr;
	for (auto& elem : equipDataArr) {
		uint32_t equipIndex = elem.equipIndex.index;
		if (equipIndex == 0) {
			equipData = const_cast<EquippedItem*>(&elem);
			break;
		}
	}
	if (!equipData) {
		return false;
	}

	IsReloadableData data = { 0 };
	data.actor = pc;

	IsReloadableDataWrapper wrapper = { &data.unk00, &data.actor };
	using func_t = _IsReloadable;
	REL::Relocation<func_t> func{ REL::ID(1089596) };

	return !func(&wrapper, equipData);
}

typedef bool (*_WornHasKeywordActor)(BSScript::IVirtualMachine* vm, uint32_t stackId, Actor* akTarget, BGSKeyword* akKeyword);
bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword) {
	GameVM* g_gameVM = GameVM::GetSingleton();
	using func_t = _WornHasKeywordActor;
	REL::Relocation<func_t> func{ REL::ID(295765) };
	if (func((g_gameVM)->impl.get(), 1, akTarget, akKeyword)) {
		return true;
	}
	return false;
}

typedef bool (*_IKeywordFormBase_HasKeyword)(IKeywordFormBase* keywordFormBase, BGSKeyword* keyword, uint32_t unk3);
bool HasKeyword(TESForm* form, BGSKeyword* keyword) {
	IKeywordFormBase* keywordFormBase = form->As<IKeywordFormBase>();
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

	for (uint32_t i = 0; i < keywordForm->numKeywords; i++) {
		BGSKeyword* curr = keywordForm->keywords[i];
		if (curr == kwdToCheck) {
			return true;
		}
	}
	return false;
}

TESForm* GetFormFromIdentifier(const string& identifier) {
	auto delimiter = identifier.find('|');
	if (delimiter != string::npos) {
		string modName = identifier.substr(0, delimiter);
		string modForm = identifier.substr(delimiter + 1);

		TESDataHandler* g_dataHandler = TESDataHandler::GetSingleton();

		const TESFile* mod = (g_dataHandler)->LookupModByName(modName.c_str());
		uint8_t modIndex = mod->compileIndex;
		if (mod && modIndex != -1) {
			uint32_t formID = stoul(modForm, nullptr, 16) & 0xFFFFFF;
			uint32_t flags = GetOffset<uint32_t>(mod, 0x334);
			if (flags & (1 << 9)) {
				// ESL
				formID &= 0xFFF;
				formID |= 0xFE << 24;
				formID |= GetOffset<uint32_t>(mod, 0x372) << 12;  // ESL load order
			} else {
				formID |= (modIndex) << 24;
			}
			return TESForm::GetFormByID(formID);
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
	//ThermalFXS = reinterpret_cast<TESEffectShader*>(GetFormFromIdentifier("Code_SharedAttachments.esm|5BCB"));
	//if (!ThermalFXS) {
	//	log("Unable to get ThermalFXS, you are lacking some file/files");
	//}
	return true;
}

std::string GetFullNameWEAP(TESObjectWEAP* weap) {
	TESFullName* pFullName = (TESFullName*)weap;
	std::string sName = (pFullName->fullName).c_str();
	return sName;
}

const BSTArray<EquippedItem>* GetPlayerEquippedItemArray() {
	if (!pc || !(pc)->currentProcess || !(pc)->currentProcess->middleHigh) {
		return nullptr;
	}

	BSTArray<EquippedItem>* equipDataArray = (pc)->currentProcess->GetEquippedItemArray();
	if (equipDataArray->empty()) {
		return nullptr;
	}
	return equipDataArray;
}

const EquippedItem* GetPlayerEquippedItemByFormID(uint32_t formId) {
	const BSTArray<EquippedItem>* equipDataArray = GetPlayerEquippedItemArray();
	if (!equipDataArray) {
		return nullptr;
	}

	for (auto elem = equipDataArray->begin(); elem != equipDataArray->end(); ++elem) {
		if (elem->item.object->formID == formId) {
			return elem;
		}
	}
	return nullptr;
}

const EquippedItem* GetPlayerEquippedItemByEquipIndex(EquipIndex equipIndex) {
	EquippedItem item;
	BGSEquipIndex bgsindex = BGSEquipIndex(equipIndex);

	if ((pc)->currentProcess->GetEquippedItemByIndex(bgsindex, item)) {
		return &item;
	}

	const BSTArray<EquippedItem>* equipDataArray = GetPlayerEquippedItemArray();
	if (!equipDataArray) {
		return nullptr;
	}
	for (auto elem = equipDataArray->begin(); elem != equipDataArray->end(); ++elem) {
		uint32_t eIdx = elem->equipIndex.index;
		if (eIdx == (uint32_t)equipIndex) {
			return elem;
		}
	}
	return nullptr;
}

const EquippedWeapon* GetPlayerEquippedWeaponByEquipIndex(EquipIndex equipIndex) {
	EquippedWeapon weapon;
	BGSEquipIndex bgsindex = BGSEquipIndex(equipIndex);

	if (!(pc)->currentProcess) {
		return nullptr;
	}

	if ((pc)->currentProcess->GetEquippedWeaponByIndex(bgsindex, weapon)) {
		return &weapon;
	}

	BSTArray<EquippedWeapon>* equipDataArray = nullptr;
	(pc)->currentProcess->GetEquippedWeapons(*equipDataArray);
	if (!equipDataArray) {
		return nullptr;
	}
	for (auto elem = equipDataArray->begin(); elem != equipDataArray->end(); ++elem) {
		uint32_t eIdx = elem->equipIndex.index;
		if (eIdx == (uint32_t)equipIndex) {
			return elem;
		}
	}
	return nullptr;
}

const EquippedWeaponData* GetPlayerEquippedWeaponDataByEquipIndex(EquipIndex equipIndex) {
	NiPointer<EquippedWeaponData> spWeaponData;
	BGSEquipIndex bgsindex = BGSEquipIndex(equipIndex);

	if (!(pc)->currentProcess) {
		return nullptr;
	}

	if ((pc)->currentProcess->GetEquippedWeaponData(bgsindex, spWeaponData)) {
		return spWeaponData.get();
	}
	return nullptr;
}

const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst) {
	if (!weapForm || !weapInst) {
		return nullptr;
	}

	TESObjectWEAP::InstanceData* weapInstData = reinterpret_cast<TESObjectWEAP::InstanceData*>(weapInst);
	if (weapInstData) {
		return weapInstData;
	}

	TESObjectWEAP* objWeap = weapForm->As<TESObjectWEAP>();
	if (!objWeap) {
		return nullptr;
	}
	return &objWeap->weaponData;
}

const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedItem& a_item) {
	if (a_item.item.object->formType != ENUM_FORM_ID::kWEAP) {
		return nullptr;
	}
	TESObjectWEAP::InstanceData* weapInstData = static_cast<TESObjectWEAP::InstanceData*>(a_item.item.instanceData.get());
	if (!weapInstData) {
		return nullptr;
	}
	return weapInstData;
}

const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedWeapon& a_weapon) {
	if (a_weapon.weapon.object->formType != ENUM_FORM_ID::kWEAP) {
		return nullptr;
	}
	//TESObjectWEAP::InstanceData* weapInstData = reinterpret_cast<TESObjectWEAP::InstanceData*>(a_weapon.weapon.instanceData.get());
	TESObjectWEAP::InstanceData* weapInstData = fallout_cast<TESObjectWEAP::InstanceData*, TBO_InstanceData>(a_weapon.weapon.instanceData.get());
	if (!weapInstData) {
		return nullptr;
	}
	return weapInstData;
}

const uint32_t GetInventoryItemCount(Actor* actor, TESForm* item) {
	if (!actor || !item) {
		return NULL;
	}

	BGSInventoryList* inventory = actor->inventoryList;
	if (!inventory) {
		return NULL;
	}

	uint32_t totalItemCount = 0;
	inventory->rwLock.lock_read();
	for (auto& elem : inventory->data) {
		if (elem.object == item) {
			BGSInventoryItem::Stack* sp = elem.stackData.get();
			while (sp) {
				totalItemCount += sp->count;
				sp = sp->nextStack.get();
			}
			break;
		}
	}
	inventory->rwLock.unlock_read();

	return totalItemCount;
}

const NiAVObject* GetByNameHelper(const BSFixedString& name) {
	BSFadeNode* player3D = (pc) ? (BSFadeNode*)(pc)->Get3D() : nullptr;
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
		for (std::uint32_t i = 0; i < player3D->kGeomArray.count; i++) {
			BSGeometry* object = player3D->kGeomArray.entries[i] ? player3D->kGeomArray.entries[i]->spGeometry.get() : nullptr;
			if (object->m_name == name) {
				obj = (NiAVObject*)object;
				return obj;
			}
		}
	}
	if (!obj) {
		logIfNeeded("Unable to find scope geometry in FlattenedGeometryData. Now attempting to find it in the ninode children...");
		for (std::uint32_t i = 0; i < player3D->m_children.m_emptyRunStart; i++) {
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

char tempbuf[8192] = { 0 };
char* _MESSAGE(const char* fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vsnprintf(tempbuf, sizeof(tempbuf), fmt, args);
	va_end(args);
	spdlog::log(spdlog::level::warn, tempbuf);

	return tempbuf;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

const string prefixLog() {
	std::stringstream buffer;
	buffer << "[" << currentDateTime() << "] [EWS] ";
	return (buffer.str());
}

//Write message log only if logEnabled == True
void logIfNeeded(string text) {
	if (logEnabled) {
		logger::info(FMT_STRING("{}"), text);
		//_MESSAGE("%s %s", prefixLog().c_str(), text.c_str());
	}
}

//Write message log always
void log(string text) {
	logger::info(FMT_STRING("{}"), text);
	//_MESSAGE("%s %s", prefixLog().c_str(), text.c_str());
}
