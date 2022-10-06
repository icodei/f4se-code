#pragma once

#include "f4se/NiTypes.h"
#include "f4se/GameTypes.h"

enum class UI_DEPTH_PRIORITY;

class BSGeometry;
class BSShaderAccumulator;
class NiAVObject;
class NiCamera;
class NiLight;
class NiDirectionalLight;
class ShadowSceneNode;


struct UIShaderColors
{
public:
	enum class Flags
	{
		kBackgroundQuad = 1u << 0,
		kColorMultiplier = 1u << 1,
		kVerticalGradient = 1u << 2,
		kUseAlphaForDropshadow = 1u << 3
	};

	// members
	NiRect<float> backgroundQuad;                          // 00
	NiColorA backgroundColor;                              // 10
	NiColorA colorMultipliers;                             // 20
	float colorBrightness;                                 // 30
	Flags enabledStates;  // 34
};
STATIC_ASSERT(sizeof(UIShaderColors) == 0x38);

struct alignas(0x10) UIShaderFXInfo
{
public:
	// members
	NiRect<float> renderQuad;  // 00
	UIShaderColors shaderFX;   // 10
};
STATIC_ASSERT(sizeof(UIShaderFXInfo) == 0x50);



class Interface3D {
public:
	enum class BackgroundMode {
		kLive,
		kStatic,
		kSolidColor
	};

	enum class PostEffect {
		kNone,
		kPipboy,
		kHUDGlass,
		kHUDGlassWithMod,
		kModMenu,
		kModMenuHighlightAll,
		kModMenuHighlightAllNoPulseOrScanLines
	};

	enum class HighlightEffect {
		kNone,
		kVATS
	};

	enum class OffscreenMenuSize {
		kPipboy,
		kFullFrame,
		kFullFrameText
	};

	enum class ScreenMode {
		kNone,
		kWorldAttached,
		kScreenAttached
	};

	enum class OffscreenMenuBlendMode {
		kAdditive,
		kAlpha
	};

	enum class LightType {
		kSpot,
		kShadowSpot,
		kPoint
	};

	class OldScreenEffectControl {
	public:
		// members
		NiPoint2 uvOffset;         // 00
		float burstAmount;         // 08
		float brightness;          // 0C
		float vScanState;          // 10
		float vScanRate;           // 14
		float pulseIntensity;      // 18
		float pulseRate;           // 1C
		float flickerMinDelay;     // 20
		float flickerMaxDelay;     // 24
		float flickerMinDuration;  // 28
		float flickerMaxDuration;  // 2C
		float flickerFrequency;    // 30
		float flickerBrightness;   // 34
		float vScanDelayMin;       // 38
		float vScanDelayMax;       // 3C
		bool doScanlines;          // 40
		float burstState;          // 44
		float burstFadeRate;       // 48
		float shudderState;        // 4C
		float vScanDelay;          // 50
		float flickerDelay;        // 54
		float vHoldState;          // 58
		float shudderScale;        // 5C
		float shudderLength;       // 60
		float vHoldRate;           // 64
		float time;                // 68
		bool flickering;           // 6C
	};
	STATIC_ASSERT(sizeof(OldScreenEffectControl) == 0x70);

	class Renderer
	{
	public:
		struct LightParams
		{
		public:
			// members
			UInt32 type;  // 00
			float spotFOV;                                   // 04
			NiPoint3 lookAtPos;                              // 08
			NiPointer<NiAVObject> lookAtObject;              // 18
			NiPointer<NiLight> light;                        // 20
		};
		STATIC_ASSERT(sizeof(LightParams) == 0x28);


		// members
		tArray<UIShaderFXInfo> colorFXInfos;                      // 000
		tArray<UIShaderFXInfo> backgroundFXInfos;                 // 018
		BSReadWriteLock cachedQuadsLock;                                   // 030
		NiColorA clearColor;                                               // 038
		float opacityAlpha;                                                // 048
		bool enabled;                                                      // 04C
		bool offscreen3DEnabled;                                           // 04D
		bool hideScreenWhenDisabled;                                       // 04E
		bool usePremultAlpha;                                              // 04F
		bool clearRenderTarget;                                            // 050
		bool clearDepthStencilMainScreen;                                  // 051
		bool clearDepthStencilOffscreen;                                   // 052
		bool postAA;                                                       // 053
		bool useFullPremultAlpha;                                          // 054
		bool alwaysRenderWhenEnabled;                                      // 055
		bool defRenderMainScreen;                                          // 056
		bool enableAO;                                                     // 057
		bool useLongRangeCamera;                                           // 058
		bool needsLightSetup;                                              // 059
		bool needsLightSetupOffscreen;                                     // 05A
		BackgroundMode bgmode;												// 05C
		PostEffect postfx;													// 060
		HighlightEffect highlightfx;										// 064
		OffscreenMenuSize omsize;											// 068
		ScreenMode screenmode;												// 06C
		OffscreenMenuBlendMode menuBlend;									// 070
		UI_DEPTH_PRIORITY depth;											// 074
		NiPointer<NiAVObject> worldAttachedElementRoot;						// 078
		NiPointer<NiAVObject> screenAttachedElementRoot;					// 080
		NiPointer<NiAVObject> offscreenElement;								// 088
		tArray<NiPointer<BSGeometry>> displayGeometry;						// 090
		NiAVObject* elementRequiringFullVieport;							// 0A8
		NiAVObject* highlightedElement;										// 0B0
		bool highlightOffscreen;											// 0B8
		OldScreenEffectControl pipfx;										// 0BC
		OldScreenEffectControl vatsfx;										// 12C
		NiPointer<BSShaderAccumulator> accum;								// 1A0
		NiPointer<NiCamera> pipboyAspect;									// 1A8
		NiPointer<NiCamera> nativeAspect;									// 1B0
		NiPointer<NiCamera> nativeAspectLongRange;							// 1B8
		UInt32 customRenderTarget;											// 1C0
		UInt32 customSwapTarget;											// 1C4
		tArray<LightParams> mainLights;										// 1C8
		tArray<LightParams> offscreenLights;								// 1E0
		float menuDiffuseIntensity;											// 1F8
		float menuEmitIntensity;											// 1FC
		float menuDiffuseIntensityWA;										// 200
		float menuEmitIntensityWA;                                         // 204
		BSFixedString name;                                                // 208
		BSFixedString screenGeomName;                                      // 210
		BSFixedString screenMaterialName;                                  // 218
		BSFixedString maskedGeomName;                                      // 220
		BSFixedString maskedMaterialName;                                  // 228
		NiDirectionalLight* directionalLight;                              // 230
		NiPointer<ShadowSceneNode> screenSSN;                              // 238
		NiPointer<ShadowSceneNode> offscreenSSN;                           // 240
	};
	STATIC_ASSERT(sizeof(Renderer) == 0x248);


	MEMBER_FN_PREFIX(Interface3D);


};