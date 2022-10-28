#pragma once

#include "f4se/BSGraphics.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameForms.h"
#include "f4se/NiObjects.h"
#include "f4se/NiProperties.h"
#include "f4se/NiTypes.h"

class BSMultiBoundRoom;
class BSPortalGraphEntry;
class BSPortalGraph;
class SceneGraph;

//I made this not knowing that Heap_Allocate() from f4se does the same thing
//class MemoryManager {
//public:
//
//	MEMBER_FN_PREFIX(MemoryManager);
//	DEFINE_MEMBER_FN(Allocate, void*, 0x01B0EFD0, unsigned __int64 a_size, unsigned int a_alignment, bool a_alignmentRequired);
//
//	void* Allocate(unsigned __int64 a_size, unsigned int a_alignment, bool a_alignmentRequired);
//};
//extern RelocPtr<MemoryManager>	MemoryManager_Instance;

class Main {
public:

	MEMBER_FN_PREFIX(Main);
	DEFINE_MEMBER_FN(GetCameraPortalGraphEntry, BSPortalGraphEntry*, 0x00D3CA50);

	BSPortalGraphEntry* GetCameraPortalGraphEntry();
};
extern RelocPtr<Main*>					appMain;
extern RelocPtr<NiPointer<SceneGraph>>	Main__spWorldSceneGraph;
extern RelocPtr<NiPointer<SceneGraph>>	Main__spMenuRoot;
extern RelocPtr<NiPointer<SceneGraph>>	Main__sp3DMenuRoot;

class TES {
public:

	MEMBER_FN_PREFIX(TES);
};
extern RelocPtr<TES*> tes;

class BSPortalGraph : public NiRefObject {
public:
	BSTArray<void*> QOccluderList; //NiTPointerList<BSOcclusionShape *>
	BSTArray<void*> QPortalList; //NiTPointerList<BSPortal *>
	BSTArray<NiPointer<BSMultiBoundRoom>> QRooms;
	BSTArray<NiPointer<NiAVObject>> QAlwaysRenderArray;
	NiNode* QPortalNodeRoot;
	BSTArray<void*> unk78;
	BSTArray<void*> unk90;
	BSTArray<NiPointer<NiNode>> QUnboundNodes;
	UInt32 QWorldID;
};

class BSPortalGraphEntry : public NiRefObject {
public:
	BSPortalGraph* QPortalGraph;
	BSTArray<NiPointer<BSMultiBoundRoom>> QRoomAccumList;
	BSMultiBoundRoom* QRoomRoot;
	UInt8 gap38[12];
	UInt32 field_44;
	UInt32 field_48;
	UInt32 field_4C;
	UInt32 field_50;
	UInt8 gap54[12];
	UInt64 field_60;
	BSCompoundFrustum QUnboundCompoundFrustum;
	bool QVisibleUnboundSpace;
	UInt32 field_13C;
	UInt16 field_140;
	UInt32 field_144;
	UInt32 field_148;
};

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
	DEFINE_MEMBER_FN(GetViewFrustrum, NiFrustum &, 0x0010A010);
	DEFINE_MEMBER_FN(GetViewPort, NiRect<float> &, 0x00AE3F90);
	DEFINE_MEMBER_FN(SetViewFrustrum, void, 0x01BAC520, NiFrustum & a1);
	DEFINE_MEMBER_FN(SetViewPort, void, 0x00AEC560, NiRect<float> & port);

	NiFrustum & GetViewFrustrum();
	NiRect<float> & GetViewPort();
	void SetViewFrustrum(NiFrustum & a1);
	void SetViewPort(NiRect<float>& port);
};
//STATIC_ASSERT(sizeof(NiCamera) == 0x1A0);

enum class _D3DBLEND;    // NOLINT(bugprone-reserved-identifier)
enum class _D3DBLENDOP;  // NOLINT(bugprone-reserved-identifier)
enum class _D3DCMPFUNC;  // NOLINT(bugprone-reserved-identifier)

struct EffectShaderData {
public:
	// members
	_D3DBLEND textureBlendModeSource;									// 00
	_D3DBLENDOP textureBlendOperation;									// 04
	_D3DCMPFUNC textureZTestFunction;									// 08
	UInt32 fillColor1;													// 0C
	float fillAlphaFadeInTime;                                          // 10
	float fillAlphaFullTime;                                            // 14
	float fillAlphaFadeOutTime;                                         // 18
	float fillAlphaPersistentPercent;                                   // 1C
	float fillAlphaPulseAmplitude;                                      // 20
	float fillAlphaPulseFrequency;                                      // 24
	float fillTextureUAnimSpeed;                                        // 28
	float fillTextureVAnimSpeed;                                        // 2C
	float edgeExponentValue;                                            // 30
	UInt32 edgeColor;													// 34
	float edgeAlphaFadeInTime;                                          // 38
	float edgeAlphaFullTime;                                            // 3C
	float edgeAlphaFadeOutTime;                                         // 40
	float edgeAlphaPersistentPercent;                                   // 44
	float edgeAlphaPulseAmplitude;                                      // 48
	float edgeAlphaPulseFrequency;                                      // 4C
	float fillAlphaFullPercent;                                         // 50
	float edgeAlphaFullPercent;                                         // 54
	_D3DBLEND textureBlendModeDest;										// 58
	float alphaTestStartTime;                                           // 5C
	float alphaTestEndTime;                                             // 60
	float alphaTestStartValue;                                          // 64
	float alphaTestEndValue;                                            // 68
	BGSSoundDescriptorForm* ambientSound;                               // 70
	UInt32 fillColor2;													// 78
	UInt32 fillColor3;													// 7C
	float fillColorScaleA[3];                                           // 80
	float fillColorTimeA[3];                                            // 8C
	UInt32 flags;														// 98
	float fillTextureUScale;                                            // 9C
	float fillTextureVScale;                                            // A0
	SInt8 boneDepth;													// A4
};
STATIC_ASSERT(sizeof(EffectShaderData) == 0xA8);

class __declspec(novtable) TESEffectShader : public TESForm, public TESModel {
public:

	// members
	EffectShaderData data;                    // 050
	TESTexture textureShaderTexture;          // 0F8
	TESTexture blockOutTexture;               // 108
	TESTexture paletteTexture;                // 118
	NiPointer<BSGeometry> shareableGeometry;  // 128

	MEMBER_FN_PREFIX(TESEffectShader);

	DEFINE_MEMBER_FN(StartEffectShader, unsigned int, 0x00311AF0, TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4);
	DEFINE_MEMBER_FN(StopEffectShader, void, 0x00311CC0, TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData);

	DEFINE_MEMBER_FN(CreateEffectShaderData, BSEffectShaderData*, 0x00311570, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);
	DEFINE_MEMBER_FN(ResetEffectShaderData, void, 0x003116D0, BSEffectShaderData* effectShaderData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);

	unsigned int StartEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4);
	void StopEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData);

	BSEffectShaderData* CreateEffectShaderData(NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);
	void ResetEffectShaderData(BSEffectShaderData* shadeData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);
};
STATIC_ASSERT(sizeof(TESEffectShader) == 0x130);

class DrawWorld {
public:
	
	MEMBER_FN_PREFIX(DrawWorld);
};

//DrawWorld Static Stuff
extern RelocPtr<NiAVObject*>			DrawWorld_p1stPerson;
extern RelocPtr<NiAVObject*>			DrawWorld_pScreenSplatterRoot;
extern RelocPtr<NiCamera*>				DrawWorld_pCamera;
extern RelocPtr<NiCamera*>				DrawWorld_pVisCamera;
extern RelocPtr<NiCamera*>				DrawWorld_pScreenSplatterCamera;

typedef void(**_VATSEffectRenderFunc)(NiCamera*);
extern RelocPtr<_VATSEffectRenderFunc*>	DrawWorld_VATSEffectRenderFunc;
typedef void(**_Interface3DRenderFN)(UInt32);
extern RelocPtr<_Interface3DRenderFN*>	DrawWorld_Interface3DRenderFN;
typedef void(**_Additional1stPersonFunc)(BSTArray<NiPointer<NiAVObject>>&);
extern RelocPtr<_Additional1stPersonFunc*>	DrawWorld_Additional1stPersonFunc;

extern RelocPtr<NiPointer<BSGeometry>>	DrawWorld_spUnitBox;
extern RelocPtr<NiPointer<NiCamera>>	DrawWorld_sp1stPersonCamera;

extern RelocPtr<NiPointer<BSShaderAccumulator>>	DrawWorld_spDraw1stPersonAccum;

extern RelocAddr<BSCullingGroup>		DrawWorld_k1stPersonCullingGroup;
extern RelocAddr<BSTArray<NiPointer<NiAVObject>>>	DrawWorld_Additional1stPersonGeom;
//DrawWorld Static Stuff End

namespace BSUtilities {
	NiAVObject* GetObjectByName(NiAVObject* target, const BSFixedString& name, bool a3, bool a4);
}
typedef NiAVObject* (*_GetObjectByName)(NiAVObject* target, const BSFixedString& name, bool a3, bool a4);
extern RelocAddr<_GetObjectByName> GetObjectByName_Internal;

void InstallExtraFunc();



extern RelocPtr<NiPointer<NiCamera>>	spCustomCamera;
extern RelocPtr<NiPointer<NiCamera>>	spCamera;

