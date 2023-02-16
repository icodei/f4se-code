#include "f4se/GameFormComponents.h"
#include "f4se/GameForms.h"

RelocAddr <_EvaluationConditions> EvaluationConditions(0x0072AF80);

#ifdef _DEBUG
#include "f4se/GameExtraData.h"

void BGSInventoryItem::Dump()
{
	_MESSAGE("%016I64X %s", form->formID, GetObjectClassName(form));
	gLog.Indent();
	stack->Dump();
	gLog.Outdent();
}

void BGSInventoryItem::Stack::Dump()
{
	_MESSAGE("Count: %d", count);
	if(extraData)
		extraData->Dump();

	if(next) {
		gLog.Indent();
		next->Dump();
		gLog.Outdent();
	}
	
}
#endif

bool IAnimationGraphManagerHolder::GetGraphVariableInt(const BSFixedString& asVariableName, UInt32 unk2) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, GetGraphVariableInt)(asVariableName, unk2);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::GetGraphVariableFloat(const BSFixedString& asVariableName, float unk2) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, GetGraphVariableFloat)(asVariableName, unk2);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::GetGraphVariableBool(const BSFixedString& asVariableName, bool unk2) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, GetGraphVariableBool)(asVariableName, unk2);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::GetGraphVariableNiPoint3(const BSFixedString& asVariableName, NiPoint3 unk2) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, GetGraphVariableNiPoint3)(asVariableName, unk2);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::GetGraphVariableImplBool(const BSFixedString& asVariableName) {
	if (asVariableName) {
		bool out = true;
		CALL_MEMBER_FN(this, GetGraphVariableImplBool)(asVariableName, out);
		return out;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::SetGraphVariableBool(const BSFixedString& asVariableName, bool newVal) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, SetGraphVariableBool)(asVariableName, newVal);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::SetGraphVariableInt(const BSFixedString& asVariableName, UInt32 newVal) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, SetGraphVariableInt)(asVariableName, newVal);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::SetGraphVariableFloat(const BSFixedString& asVariableName, float newVal) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, SetGraphVariableFloat)(asVariableName, newVal);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::SetGraphVariableNiPoint3(const BSFixedString& asVariableName, NiPoint3 newVal) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, SetGraphVariableNiPoint3)(asVariableName, newVal);
		return true;
	}
	else {
		return false;
	}
}
bool IAnimationGraphManagerHolder::SetGraphVariableNiQuaternion(const BSFixedString& asVariableName, NiQuaternion newVal) {
	if (asVariableName) {
		CALL_MEMBER_FN(this, SetGraphVariableNiQuaternion)(asVariableName, newVal);
		return true;
	}
	else {
		return false;
	}
}

bool IAnimationGraphManagerHolder::NotifyAnimationGraphImpl(const BSFixedString& asEventName){
	if (asEventName) {
		CALL_MEMBER_FN(this, NotifyAnimationGraphImpl)(asEventName);
		return true;
	}
	else {
		return false;
	}
}
