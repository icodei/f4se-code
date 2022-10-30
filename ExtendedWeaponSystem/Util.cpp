#include "Global.h"
bool IsReloading() {
	if (!*g_player) { return false; }
	UInt32 reload_flag = ((*g_player)->actorState.flags >> 14) & 0xF;
	return reload_flag == 0x04;
}

bool IsSprinting() {
	if (!*g_player) { return false; }
	return (*g_player)->actorState.unk08 & 0x0100;
}

bool IsFirstPerson() {
	if (!*g_playerCamera) { return false; }
	return (*g_playerCamera)->cameraState == (*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_FirstPerson];
}

bool IsThirdPerson() {
	if (!*g_playerCamera) { return false; }
	return (*g_playerCamera)->cameraState == (*g_playerCamera)->cameraStates[PlayerCamera::kCameraState_ThirdPerson2];
}

bool IsWeaponDrawn() {
	if (!*g_player) { return false; }
	return (*g_player)->actorState.IsWeaponDrawn();
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

RelocAddr <_IsReloadable> IsReloadable_Internal(0xE24B80);
bool IsWeaponReloadable() {
	if (!*g_player || !(*g_player)->middleProcess || !(*g_player)->middleProcess->unk08) { return false; }

	tArray<Actor::MiddleProcess::Data08::EquipData> equipDataArr = reinterpret_cast<tArray<Actor::MiddleProcess::Data08::EquipData> &>((*g_player)->middleProcess->unk08->equipData);
	if (equipDataArr.count == 0) {
		return false;
	}

	Actor::MiddleProcess::Data08::EquipData* equipData = nullptr;
	for (UInt32 i = 0; i < equipDataArr.count; i++) {
		UInt32 equipIndex = *reinterpret_cast<UInt32*>(&equipDataArr.entries[i].unk18);
		if (equipIndex == 0) {
			equipData = &equipDataArr.entries[i];
			break;
		}
	}
	if (!equipData) { return false; }

	IsReloadableData data = { 0 };
	data.actor = *g_player;

	IsReloadableDataWrapper wrapper = { &data.unk00, &data.actor };

	return !IsReloadable_Internal(&wrapper, equipData);
}

RelocAddr <_SetAnimationVariableBoolPapyrus> SetAnimationVariableBoolPapyrusInternal(0x140EB30);
void SetAnimationVariableBoolPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, bool newVal) {
	SetAnimationVariableBoolPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

RelocAddr <_SetAnimationVariableIntPapyrus> SetAnimationVariableIntPapyrusInternal(0x140EC70);
void SetAnimationVariableIntPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, int newVal) {
	SetAnimationVariableIntPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

RelocAddr <_SetAnimationVariableFloatPapyrus> SetAnimationVariableFloatPapyrusInternal(0x140EBD0);
void SetAnimationVariableFloatPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, float newVal) {
	SetAnimationVariableFloatPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

RelocAddr <_SetSubGraphFloatVariablePapyrus> SetSubGraphFloatVariablePapyrusInternal(0x138B430);
void SetSubGraphFloatVariablePapyrus(Actor* actor, BSFixedString& asVariableName, float newVal) {
	SetSubGraphFloatVariablePapyrusInternal((*g_gameVM)->m_virtualMachine, 0, actor, asVariableName, newVal);
}

RelocAddr <_CreateNS_NiCamera_Create_Internal> CreateNS_NiCamera_Create_Internal(0x1BAE180);
NiObject* CreateNS_NiCamera_Create() {
	return CreateNS_NiCamera_Create_Internal();
}

RelocAddr <_CreateNS_NiNode_Create_Internal> CreateNS_NiNode_Create_Internal(0x01B99E60);
NiObject* CreateNS_NiNode_Create() {
	return CreateNS_NiNode_Create_Internal();
}

RelocAddr <_WornHasKeywordActor> Actor_WornHasKeyword(0x138C440);
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
		if (pFullName) {
			return pFullName->name;
		}
	}
	return BSFixedString();
}

std::string GetFullNameWEAP(TESObjectWEAP* weap) {
	TESFullName* pFullName = DYNAMIC_CAST(weap, TESObjectWEAP, TESFullName);
	std::string sName = (pFullName->name).c_str();
	return sName;
}

const tArray<Actor::MiddleProcess::Data08::EquipData>* GetEquipDataArray() {
	if (!*g_player || !(*g_player)->middleProcess || !(*g_player)->middleProcess->unk08) { return nullptr; }

	tArray<Actor::MiddleProcess::Data08::EquipData> equipDataArray = reinterpret_cast<tArray<Actor::MiddleProcess::Data08::EquipData>&>((*g_player)->middleProcess->unk08->equipData);
	if (equipDataArray.count == 0) { return nullptr; }

	return &reinterpret_cast<tArray<Actor::MiddleProcess::Data08::EquipData>&>((*g_player)->middleProcess->unk08->equipData);
}

Actor::MiddleProcess::Data08::EquipData* GetEquipDataByFormID(UInt32 formId) {
	const tArray<Actor::MiddleProcess::Data08::EquipData>* equipDataArray = GetEquipDataArray();
	if (!equipDataArray) { return nullptr; }

	for (UInt32 i = 0; i < equipDataArray->count; i++) {
		if (equipDataArray->entries[i].item->formID == formId) {
			return &equipDataArray->entries[i];
		}
	}

	return nullptr;
}

Actor::MiddleProcess::Data08::EquipData* GetEquipDataByEquipIndex(EquipIndex equipIndex) {
	const tArray<Actor::MiddleProcess::Data08::EquipData>* equipDataArray = GetEquipDataArray();
	if (!equipDataArray) { return nullptr; }
	
	for (UInt32 i = 0; i < equipDataArray->count; i++) {
		UInt32 eIdx = reinterpret_cast<UInt32&>(equipDataArray->entries[i].unk18);
		if (eIdx == equipIndex) {
			return &equipDataArray->entries[i];
		}
	}

	return nullptr;
}

TESObjectWEAP::InstanceData* GetWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst) {
	TESObjectWEAP::InstanceData* weapInstData = (TESObjectWEAP::InstanceData*)Runtime_DynamicCast(weapInst, RTTI_TBO_InstanceData, RTTI_TESObjectWEAP__InstanceData);
	if (weapInstData) {
		return weapInstData;
	}
	TESObjectWEAP* objWeap = DYNAMIC_CAST(weapForm, TESForm, TESObjectWEAP);

	if (!objWeap) { return nullptr; }
		
	return &objWeap->weapData;
}

UInt32 GetInventoryItemCount(Actor* actor, TESForm* item) {
	if (!actor || !item) { return NULL; }

	BGSInventoryList* inventory = actor->inventoryList;
	if (!inventory) { return NULL; }

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
		logIfNeeded(";====================== Game Loaded. Getting Initial Weapon Stats =====================;");
		logIfNeeded("Weapon: " + GetFullNameWEAP(weap));
		logIfNeeded("TotalAmmoCount: " + std::to_string(totalAmmoCount));
		logIfNeeded("CurrentAmmoCount: " + std::to_string(currentAmmoCount));
		logIfNeeded("AmmoCapacity: " + std::to_string(ammoCapacity));
		if (WornHasKeywordActor(*g_player, reloadSequentialKeyword)) {
			processCurrentWeap = true;
			logIfNeeded(GetFullNameWEAP(weap) + " has the reloadSequentialKeyword.");
		} else {
			processCurrentWeap = false;
			logIfNeeded(GetFullNameWEAP(weap) + " does not have the reloadSequentialKeyword.");
		}
		if (WornHasKeywordActor(*g_player, ThermalScopeKeyword)) {
			processCurrentScope = true;
			logIfNeeded(GetFullNameWEAP(weap) + " has the ThermalScopeKeyword.");
		} else {
			processCurrentScope = false;
			ScopeTextureLoader = nullptr;
			logIfNeeded(GetFullNameWEAP(weap) + "does not have the ThermalScopeKeyword.");
		}
		logIfNeeded(";======================================================================================;");
	}
}

//Equip Handler
void HanldeWeaponEquip(TESObjectWEAP::InstanceData* weap) {
	TESObjectWEAP::InstanceData* equippedWeaponInstance = weap;
	currentWeapInstance = equippedWeaponInstance;
	if (HasKeywordInstWEAP(weap, reloadSequentialKeyword) || WornHasKeywordActor(*g_player, reloadSequentialKeyword)) {
		processCurrentWeap = true;
		ammoCapacity = equippedWeaponInstance->ammoCapacity;
		logIfNeeded("reloadSequentialKeyword found. We should process this weapon for sequential reloads.");
		logIfNeeded("weapon instance equipped with ammo capacity of:" + std::to_string(currentWeapInstance->ammoCapacity));
	} else {
		logIfNeeded("No reloadSequentialKeyword found. We can ignore this weapon for sequential reloads.");
		processCurrentWeap = false;
	}
	if (HasKeywordInstWEAP(weap, ThermalScopeKeyword) || WornHasKeywordActor(*g_player, ThermalScopeKeyword)) {
		processCurrentScope = true;
		logIfNeeded("ThermalScopeKeyword found. We should process this weapon for special scope utility.");
	} else {
		processCurrentScope = false;
		logIfNeeded("No ThermalScopeKeyword found. We can ignore this weapon for special scope utility.");
	}
	logIfNeeded(";======================================================================================;");
}

//Called from anim event of weapon equip. This should happen after the 3d is loaded hopefully
void HanldeWeaponEquipAfter3D() {
	BSGeometry* objGeom;
	NiCamera* currentCam;
	NiCamera* cam;
	NiCamera* newCam;

	const BSFixedString geomName = "TextureLoader:0";
	const BSFixedString camName = "ScopePOV";
	if (processCurrentScope && ignore == false) {
		logIfNeeded("The 3D should be loaded now. We should be able to interact with geometry now.");
		objGeom = (BSGeometry*)GetByNameHelper(geomName);
		if (objGeom != ScopeTextureLoader) {
			if (objGeom) {
				ScopeTextureLoader = objGeom;
				logIfNeeded("Found the geometry of the scope.");
			}
		}
		cam = (NiCamera*)GetByNameHelper(camName);
		if (cam) {
			newCam = cam;
		} else {
			newCam = nullptr;
			scopePOV = scopePOV_BACKUP;
			scopePOVRoot = scopePOVRoot_BACKUP;
		}
		currentCam = scopePOV;
		if (currentCam != newCam) {
			if (newCam) {
				scopePOV = newCam;
				if (scopePOV->m_parent) {
					scopePOVRoot = scopePOV->m_parent;
				}
				logIfNeeded("Found the scope camera.");
			}
			if (currentCam && !InterlockedDecrement(&currentCam->m_uiRefCount)) {
				currentCam->DeleteThis();
			}
		}
		//TODO: add actor value or something similar to set what the FOV should be on the camera of each scope
		if (scopePOV) {
			float FOV = (*g_playerCamera)->fDefault1stPersonFOV;
			BSShaderUtil::SetCameraFOV((*Main__spWorldSceneGraph), (float)(FOV/4), 0, scopePOV, 1); //TEMP for testing. Right now I just have it as 4x zoom
		}
		
		//if (scopePOV && scopeRenderer) {
		//	scopeRenderer->scopeCam.camera = scopePOV;
		//}
		//SetupTextureLoaderWithEffectShader();
		//SetupImageSpaceShader(ScopeTextureLoader, true);
		if (!objGeom) {
			logIfNeeded("Could not find the geometry of the scope.");
			//(ThermalFXS)->StopEffectShader(ThermalFXS, ScopeTextureLoader, effectShaderData);
			processCurrentScope = false;
		}
	}
}

void SetupImageSpaceShader(BSGeometry* objGeom, bool active) {
	BSImagespaceShader* BSImageShader = (BSImagespaceShader*)(*ImageSpaceManager_pInstance)->GetEffect(ImageSpaceManager::ImageSpaceEffectEnum::kBSHUDGlassCopy);
	NiPointer<BSShaderProperty> shaderProperty;
	BSEffectShaderProperty* effectShaderProperty;
	BSEffectShaderMaterial* effectShaderMaterial;
	shaderProperty = ni_cast(objGeom->shaderProperty, BSShaderProperty);
	effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
	if (shaderProperty.get()) {
		effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->shaderMaterial);
		BSImageShader->Render((BSTriShape*)objGeom, BSImagespaceShader_DefaultParam);
		logIfNeeded("Scope materials setup complete.");
	}
}

void SetupTextureLoaderWithEffectShader() {
	NiPointer<BSShaderProperty> shaderProperty;
	BSEffectShaderProperty* effectShaderProperty;
	BSEffectShaderMaterial* effectShaderMaterial;
	shaderProperty = ni_cast(ScopeTextureLoader->shaderProperty, BSShaderProperty);
	effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
	if (shaderProperty.get()) {
		logIfNeeded("Got the EffectShaderProperty");
		effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->shaderMaterial);
		//effectShaderData = ThermalFXS->CreateEffectShaderData(ScopeTextureLoader, effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get());
		effectShaderData = CreateEffectShaderDataCustom(ThermalFXS, effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get());
		effectShaderProperty->SetEffectShaderData(effectShaderData);
		if (effectShaderProperty->SetupGeometry(ScopeTextureLoader)) {
			logIfNeeded("Geometry was setup with the shaders.");
		} else {
			logIfNeeded("Geometry was unable to be setup.");
		}
		logIfNeeded("Scope materials setup complete.");
	}
}

NiAVObject* GetByNameHelper(const BSFixedString& name) {
	BSFadeNode* player3D = (*g_player) ? (BSFadeNode*)(*g_player)->GetObjectRootNode() : nullptr;
	if (player3D) {
		//logIfNeeded("Got player 3D.");
		NiAVObject* obj;
		obj = BSUtilities::GetObjectByName(player3D, name, true, true);
		//if (!obj) {
		//	logIfNeeded("Unable to find scope geometry with BSUtilities. Now attempting to find it in the FlattenedGeometryData...");
		//	for (UInt32 i = 0; i < player3D->kGeomArray.count; i++) {
		//		BSGeometry* object = player3D->kGeomArray.entries[i] ? player3D->kGeomArray.entries[i]->spGeometry.get() : nullptr;
		//		if (object->m_name == name) {
		//			obj = (NiAVObject*)object;
		//			return obj;
		//		}
		//	}
		//}
		//if (!obj) {
		//	logIfNeeded("Unable to find scope geometry in FlattenedGeometryData. Now attempting to find it in the ninode children...");
		//	for (UInt32 i = 0; i < player3D->m_children.m_emptyRunStart; i++) {
		//		NiPointer<NiAVObject> object(player3D->m_children.m_data[i]);
		//		if (object) {
		//			if (object->m_name == name) {
		//				obj = object.get();
		//				return obj;
		//			}
		//		}
		//	}
		//}
		if (obj) {
			return obj;
		} else { return nullptr; }
	} else { return nullptr; }
}

//TESEffectShader::CreateEffectShaderData but without the reset part breaking it
BSEffectShaderData* CreateEffectShaderDataCustom(TESEffectShader* shader, NiTexture* tex1, NiTexture* tex2, NiTexture* tex3) {
	BSEffectShaderData* newEffectShaderData = (BSEffectShaderData*)Heap_Allocate(0x88);
	if (newEffectShaderData) {
		newEffectShaderData->m_refCount = 0;
		newEffectShaderData->pNodeFilterFunction = 0i64;
		newEffectShaderData->spBaseTexture.m_pObject = NULL;
		newEffectShaderData->spPaletteTexture.m_pObject = NULL;
		newEffectShaderData->spBlockOutTexture.m_pObject = NULL;
		newEffectShaderData->eTextureClampMode = 3;
		newEffectShaderData->FillColor.g = 0.0;
		newEffectShaderData->FillColor.a = 0.0;
		newEffectShaderData->RimColor.g = 0.0;
		newEffectShaderData->RimColor.a = 0.0;
		newEffectShaderData->fBaseFillScale = 1.0;
		newEffectShaderData->fBaseFillAlpha = 1.0;
		newEffectShaderData->fBaseRimAlpha = 1.0;
		newEffectShaderData->fVOffset = 0.0;
		newEffectShaderData->fUScale = 1.0;
		newEffectShaderData->fVScale = 1.0;
		newEffectShaderData->fEdgeExponent = 1.0;
		newEffectShaderData->eSrcBlend = NiAlphaProperty::AlphaFunction::kAlpha_SrcAlpha;
		newEffectShaderData->eDestBlend = NiAlphaProperty::AlphaFunction::kAlpha_InvSrcAlpha;
		newEffectShaderData->eZTestFunc = 1;
		newEffectShaderData->bBaseTextureProjectedUVs = 0;
	} else {
		newEffectShaderData = NULL;
	}
	InterlockedIncrement(&newEffectShaderData->m_refCount);

	NiPointer<NiTexture> textureShaderTexture;
	NiPointer<NiTexture> blockOutTexture;
	NiPointer<NiTexture> paletteTexture;

	gShaderManagerInstance->GetTexture(shader->textureShaderTexture.str.c_str(), false, textureShaderTexture, true, true ,true);
	gShaderManagerInstance->GetTexture(shader->blockOutTexture.str.c_str(), false, blockOutTexture, true, true, true);
	gShaderManagerInstance->GetTexture(shader->paletteTexture.str.c_str(), false, paletteTexture, true, true, true);

	newEffectShaderData->spBaseTexture = textureShaderTexture;
	newEffectShaderData->spBlockOutTexture = blockOutTexture;
	newEffectShaderData->spPaletteTexture = paletteTexture;


	newEffectShaderData->FillColor.r = (float)BYTE0(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.g = (float)BYTE1(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.b = (float)BYTE2(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.a = 0.0 * FToRGB;

	float rimColorR = BYTE0(shader->data.edgeColor);
	float rimColorG = BYTE1(shader->data.edgeColor);
	float rimColorB = BYTE2(shader->data.edgeColor);

	newEffectShaderData->RimColor.r = (float)rimColorR * FToRGB;
	newEffectShaderData->RimColor.g = (float)rimColorG * FToRGB;
	newEffectShaderData->RimColor.b = (float)rimColorB * FToRGB;
	newEffectShaderData->RimColor.a = 0.0 * FToRGB;

	float fillAlpha;
	if (shader->data.fillAlphaFadeInTime == 0.0 && shader->data.fillAlphaFullTime == 0.0) {
		fillAlpha = shader->data.fillAlphaFullPercent;
	} else {
		fillAlpha = 0.0;
	}
	newEffectShaderData->fBaseFillAlpha = fillAlpha;
	float edgeAlpha;
	if (shader->data.edgeAlphaFadeInTime == 0.0 && shader->data.edgeAlphaFullTime == 0.0) {
		edgeAlpha = shader->data.edgeAlphaFullPercent;
	}
	newEffectShaderData->fBaseRimAlpha = edgeAlpha;
	newEffectShaderData->fUOffset = 0;
	newEffectShaderData->fUScale = shader->data.fillTextureUScale;
	newEffectShaderData->fVScale = shader->data.fillTextureVScale;
	newEffectShaderData->fEdgeExponent = shader->data.edgeExponentValue;

	newEffectShaderData->eSrcBlend = NiAlphaProperty::AlphaFunction::kAlpha_SrcAlpha;
	newEffectShaderData->eDestBlend = NiAlphaProperty::AlphaFunction::kAlpha_InvSrcAlpha;
	newEffectShaderData->eZTestFunc = 1;
	newEffectShaderData->ucAlphaTestRef = shader->data.alphaTestStartValue;
	newEffectShaderData->bGrayscaleToColor = (shader->data.flags & 2) != 0;
	newEffectShaderData->bGrayscaleToAlpha = (shader->data.flags & 4) != 0;
	newEffectShaderData->bIgnoreTextureAlpha = (shader->data.flags & 64) != 0;
	newEffectShaderData->bBaseTextureProjectedUVs = (shader->data.flags & 128) != 0;
	newEffectShaderData->bIgnoreBaseGeomTexAlpha = BYTE1(shader->data.flags) & 1;
	newEffectShaderData->bLighting = (shader->data.flags & 512) != 0;
	newEffectShaderData->bAlpha = (shader->data.flags & 2048) != 0;

	if ((shader->data.flags & 16) != 0) {
		rimColorG = rimColorG - 255.0;
		rimColorB = rimColorB - 255.0;
		newEffectShaderData->RimColor.r = (float)(rimColorR - 255.0) * FToRGB;
	} else {
		newEffectShaderData->RimColor.r = rimColorR * FToRGB;
	}
	newEffectShaderData->RimColor.g = rimColorG * FToRGB;
	newEffectShaderData->RimColor.b = rimColorB * FToRGB;
	newEffectShaderData->RimColor.a = 0.0 * FToRGB;

	if (effectShaderData == newEffectShaderData) {
		newEffectShaderData->~BSEffectShaderData();
		logIfNeeded("The BSEffectShaderData has already been made. We can delete the one just now created");
		return effectShaderData;

	} else {
		return newEffectShaderData;
	}
}


//code from Bingle
//void ReloadSubgraph() {
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
	if (currentWeapInstance) {
		if (amount > ammoCapacity) { //This if statement is for when ammo complete of the animation goes over the original max ammo count. Will be edited later for +1 and +2 loading
			currentWeapInstance->ammoCapacity = ammoCapacity;
			logIfNeeded("Ammo count set to: " + std::to_string(ammoCapacity));
		} else {
			currentWeapInstance->ammoCapacity = amount;
			logIfNeeded("Ammo count set to: " + std::to_string(amount));
		}
	} else {
		log("Weapon instance is nullptr. Could not set ammo.");
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