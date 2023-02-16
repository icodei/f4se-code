#include "f4se/GameCamera.h"

// 05C2864F8B39388E329CE28479B6A5636B4D529C+11
RelocPtr <PlayerCamera *> g_playerCamera(0x058CEB28);

SInt32 PlayerCamera::GetCameraStateId(TESCameraState * state)
{
	for(int i = 0; i < kNumCameraStates; i++) {
		if(state == cameraStates[i])
			return i;
	}

	return -1;
}

void TESCamera::AddRotationInput(float a1, float a2) {
	CALL_MEMBER_FN(this, AddRotationInput)(a1, a2);
}

void TESCamera::AddTranslationInput(float x, float y, float z) {
	CALL_MEMBER_FN(this, AddTranslationInput)(x, y, z);
}

void TESCamera::AddZoomInput(float zoom) {
	CALL_MEMBER_FN(this, AddZoomInput)(zoom);
}

bool TESCamera::GetCameraRoot(NiPointer<NiNode>& out) {
	CALL_MEMBER_FN(this, GetCameraRoot)(out);
}

void TESCamera::SetCameraEnabled(bool enabled) {
	CALL_MEMBER_FN(this, SetCameraEnabled)(enabled);
}

void TESCamera::SetCameraRoot(NiNode* newRoot) {
	CALL_MEMBER_FN(this, SetCameraRoot)(newRoot);
}

void TESCamera::SetCameraState(TESCameraState* newCameraState) {
	CALL_MEMBER_FN(this, SetCameraState)(newCameraState);
}