#pragma once
#include "Global.h"

void IsButtonDoubleTapFunctor(const ButtonEvent* btnEvent, void (*functor)());
bool IsButtonPressed(ButtonEvent* btnEvent);
bool IsHoldingButton(ButtonEvent* btnEvent);
