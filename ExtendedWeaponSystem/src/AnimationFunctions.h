#pragma once
#include "Global.h"

void SetAnimationVariableBoolPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, bool newVal);
void SetAnimationVariableFloatPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, float newVal);
void SetAnimationVariableIntPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, int newVal);
void SetSubGraphFloatVariablePapyrus(Actor* actor, BSFixedString& asVariableName, float newVal);

void ReloadSubgraph();