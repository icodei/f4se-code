#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/BSGeometry.h"
#include "f4se/BSShader.h"
#include "f4se/BSCulling.h"
#include "f4se/NiCamera.h"
#include "f4se/GameTypes.h"
#include "f4se/NiObjects.h"
#include "f4se/NiTypes.h"

class DrawWorld {
public:

	MEMBER_FN_PREFIX(DrawWorld);
};

//DrawWorld Static Stuff
extern RelocPtr<NiAVObject*>	DrawWorld_p1stPerson;
extern RelocPtr<NiAVObject*>	DrawWorld_pScreenSplatterRoot;
extern RelocPtr<NiCamera*>		DrawWorld_pCamera;
extern RelocPtr<NiCamera*>		DrawWorld_pVisCamera;
extern RelocPtr<NiCamera*>		DrawWorld_pScreenSplatterCamera;

typedef void(**_VATSEffectRenderFunc)(NiCamera*);
extern RelocPtr<_VATSEffectRenderFunc*>		DrawWorld_VATSEffectRenderFunc;
typedef void(**_Interface3DRenderFN)(UInt32);
extern RelocPtr<_Interface3DRenderFN*>		DrawWorld_Interface3DRenderFN;
typedef void(**_Additional1stPersonFunc)(BSTArray<NiPointer<NiAVObject>>&);
extern RelocPtr<_Additional1stPersonFunc*>	DrawWorld_Additional1stPersonFunc;

extern RelocPtr<NiPointer<BSGeometry>>	DrawWorld_spUnitBox;
extern RelocPtr<NiPointer<NiCamera>>	DrawWorld_sp1stPersonCamera;

extern RelocPtr<NiPointer<BSShaderAccumulator>>	DrawWorld_spDraw1stPersonAccum;

extern RelocAddr<BSCullingGroup>		DrawWorld_k1stPersonCullingGroup;
extern RelocAddr<BSTArray<NiPointer<NiAVObject>>>	DrawWorld_Additional1stPersonGeom;
//DrawWorld Static Stuff End