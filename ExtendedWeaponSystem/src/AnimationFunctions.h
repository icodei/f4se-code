#pragma once
#include "Global.h"

void SetPlayerAnimationVariableBool(BSFixedString& asVariableName, bool newVal);
void SetPlayerAnimationVariableFloat(BSFixedString& asVariableName, float newVal);
void SetPlayerAnimationVariableInt(BSFixedString& asVariableName, int newVal);

void ReloadSubgraph();
