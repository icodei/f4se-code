#include "InputUtil.h"

void IsButtonDoubleTapFunctor(const ButtonEvent* btnEvent, void (*functor)()) {

	//UNFINISHED
	//DO NOT USE

	BSTimer& timer = BSTimer::GetTimer();

	if (!firstButton) {
		firstButton = btnEvent;
		secondButton = nullptr;
	}
	
	for (; btnEvent->next; btnEvent = (ButtonEvent*)btnEvent->next) {
		
		if ((btnEvent->device != INPUT_DEVICE::kGamepad) || (btnEvent->device != INPUT_DEVICE::kKeyboard)) {
			continue;
		}
		if (btnEvent->eventType != INPUT_EVENT_TYPE::kButton) {
			continue;
		}

		if (btnEvent->next) {
			
			if (firstButton->QIDCode() == ((ButtonEvent*)btnEvent->next)->QIDCode()) {
				secondButton = (ButtonEvent*)btnEvent->next;
				break;
			}
		}
		
	}

	if (!secondButton) {
		return;
	}

	if (keyPressedLast != btnEvent->QIDCode()) {
		keyPressedLast = btnEvent->QIDCode();
		keyPressedCount = 1;
		keyPressedLastTime = timer.realTimeDelta;
		return;
	}
	if (timer.realTimeDelta - keyPressedLastTime < BUTTON_TIMEOUT * 1000.0F) {
		++keyPressedCount;
		if (keyPressedCount >= BUTTON_DOUBLE_TAP) {
			keyPressedLast = btnEvent->QIDCode();
			keyPressedCount = 0;
			functor();
		}
	} else {
		keyPressedCount = 1;
	}
	keyPressedLastTime = timer.realTimeDelta;
}

bool IsButtonPressed(ButtonEvent* btnEvent) {
	return ((btnEvent->value == BUTTON_UP) && (btnEvent->heldDownSecs > 0 && btnEvent->heldDownSecs < BUTTON_HOLD_TIMER));
}

bool IsHoldingButton(ButtonEvent* btnEvent) {
	return (((btnEvent->value == BUTTON_DOWN) || (btnEvent->value != BUTTON_UP)) && (btnEvent->heldDownSecs >= BUTTON_HOLD_TIMER));
}
