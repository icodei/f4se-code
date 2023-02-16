#include "f4se/DrawWorld.h"

//DrawWorld Static Stuff
RelocPtr<NiAVObject*>				DrawWorld_p1stPerson(0x06723200);
RelocPtr<NiAVObject*>				DrawWorld_pScreenSplatterRoot(0x06723230);
RelocPtr<NiCamera*>					DrawWorld_pCamera(0x06723238);
RelocPtr<NiCamera*>					DrawWorld_pVisCamera(0x06723240);
RelocPtr<NiCamera*>					DrawWorld_pScreenSplatterCamera(0x06723248);

RelocPtr<_VATSEffectRenderFunc*>	DrawWorld_VATSEffectRenderFunc(0x06723290);
RelocPtr<_Interface3DRenderFN*>		DrawWorld_Interface3DRenderFN(0x06723298);
RelocPtr<_Additional1stPersonFunc*>	DrawWorld_Additional1stPersonFunc(0x067232B0);

RelocPtr<NiPointer<BSGeometry>>		DrawWorld_spUnitBox(0x067232F0);
RelocPtr<NiPointer<NiCamera>>		DrawWorld_sp1stPersonCamera(0x067232F8);

RelocPtr<NiPointer<BSShaderAccumulator>>	DrawWorld_spDraw1stPersonAccum(0x06723358);

RelocAddr<BSCullingGroup>			DrawWorld_k1stPersonCullingGroup(0x067236A0);
RelocAddr<BSTArray<NiPointer<NiAVObject>>>	DrawWorld_Additional1stPersonGeom(0x067239C8);
//DrawWorld Static Stuff End