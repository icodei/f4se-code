#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/NiTypes.h"
#include "f4se/NiObjects.h"

class NiCamera : public NiAVObject {
public:
	NiCamera() { CALL_MEMBER_FN(this, ctor)(); };
	NiCamera(NiCamera* cam) { CALL_MEMBER_FN(cam, ctor)(); };
	//virtual ~NiCamera();  // 00

	// members
	float worldToCam[4][4];  // 120
	NiFrustum viewFrustum;   // 160
	float minNearPlaneDist;  // 17C
	float maxFarNearRatio;   // 180
	NiRect<float> port;      // 184
	float lodAdjust;         // 194

	MEMBER_FN_PREFIX(NiCamera);
	DEFINE_MEMBER_FN(ctor, void, 0x01BAC3F0);
	DEFINE_MEMBER_FN(GetViewFrustrum, NiFrustum&, 0x0010A010);
	DEFINE_MEMBER_FN(GetViewPort, NiRect<float>&, 0x00AE3F90);
	DEFINE_MEMBER_FN(SetViewFrustrum, void, 0x01BAC520, NiFrustum& a1);
	DEFINE_MEMBER_FN(SetViewPort, void, 0x00AEC560, NiRect<float>& port);

	NiFrustum& GetViewFrustrum();
	NiRect<float>& GetViewPort();
	void SetViewFrustrum(NiFrustum& a1);
	void SetViewPort(NiRect<float>& port);
};
//STATIC_ASSERT(sizeof(NiCamera) == 0x1A0);