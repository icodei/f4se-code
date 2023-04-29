#pragma once
#include "Global.h"

void IsButtonDoubleTapFunctor(int32_t id, void (*functor)(int32_t));
bool IsButtonPressed(ButtonEvent* btnEvent);
bool IsHoldingButton(ButtonEvent* btnEvent);
