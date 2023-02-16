#include "f4se/NiCamera.h"

NiFrustum& NiCamera::GetViewFrustrum() {
	return CALL_MEMBER_FN(this, GetViewFrustrum)();
}
NiRect<float>& NiCamera::GetViewPort() {
	return CALL_MEMBER_FN(this, GetViewPort)();
}

void NiCamera::SetViewFrustrum(NiFrustum& a1) {
	CALL_MEMBER_FN(this, SetViewFrustrum)(a1);
}

void NiCamera::SetViewPort(NiRect<float>& port) {
	CALL_MEMBER_FN(this, SetViewPort)(port);
}