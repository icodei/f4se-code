#include "InputUtil.h"

void IsButtonDoubleTapFunctor(int32_t id, void (*functor)(int32_t)) {
	if (keyPressedLast != (uint32_t)id) {
		keyPressedLast = id;
		keyPressedCount = 1;
		keyPressedLastTime = std::chrono::system_clock::now().time_since_epoch();
		return;
	}
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() - keyPressedLastTime).count() < BUTTON_TIMEOUT * 1000.0f) {
		++keyPressedCount;
		if (keyPressedCount >= BUTTON_DOUBLE_TAP) {
			keyPressedLast = id;
			keyPressedCount = 0;
			functor(id);
		}
	} else {
		keyPressedCount = 1;
	}
	keyPressedLastTime = std::chrono::system_clock::now().time_since_epoch();
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
