#pragma once
#include "RE/Bethesda/BSShader/BSShaderMaterial.h"

namespace RE
{
	class BSLightingShaderMaterialEnvmap;
	class NiTexture;

	class BSLightingShaderMaterialBase : public BSShaderMaterial
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialBase };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialBase };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES
		{
			MD_BASEMAP = 0x1,
			MD_NORMALMAP = 0x2,
			MD_GLOWMAP = 0x3,
			MD_SMOOTHSPECMAP = 0x4,
			MD_LOOKUPMAP = 0x5,
			MD_ALPHA = 0x6,
			MD_SMOOTHNESS = 0x7,
			MD_SPEC_RED = 0x8,
			MD_SPEC_GREEN = 0x9,
			MD_SPEC_BLUE = 0xA,
			MD_SPEC_SCALE = 0xB,
			MD_REFRACTION_POW = 0xC,
			MD_SUBSURF_ROLLOFF = 0xD,
			MD_RIMLIGHT_POW = 0xE,
			MD_BACKLIGHT_POW = 0xF,
			MD_LOOKUP_SCALE = 0x10,
			MD_FRESNEL_POWER = 0x11,
			MD_WETNESS_SPEC_SCALE = 0x12,
			MD_WETNESS_SPEC_POWER = 0x13,
			MD_WETNESS_SPEC_MIN = 0x14,
			MD_WETNESS_ENVMAP_SCALE = 0x15,
			MD_WETNESS_FRESNEL_POWER = 0x16,
			MD_WETNESS_METALNESS = 0x17,
			MD_DISPLACEMENTMAP = 0x18,
			MD_LS_END = 0x19,
		};

		//add
		virtual BSLightingShaderMaterialEnvmap* IsLightingShaderMaterialEnvmap();
		virtual void ClearTextures();
		virtual void GetTextures(NiTexture** textures, [[maybe_unused]] std::uint32_t a_amount);
		virtual void SaveBinary(NiStream* stream);
		virtual void LoadBinary(NiStream* stream);
		virtual void OnPrefetchTextures();
		virtual void OnLoadTextureSet();
		virtual void OnLoadTextureSet(const BSTextureSet*);
		virtual void DoReceiveValuesFromRootMaterial(const BSShaderData& a_data);

		//members
		NiColor kSpecularColor;                            // 38
		NiPointer<NiTexture> spDiffuseTexture;             // 48
		NiPointer<NiTexture> spNormalTexture;              // 50
		NiPointer<NiTexture> spRimSoftLightingTexture;     // 58
		NiPointer<NiTexture> spSmoothnessSpecMaskTexture;  // 60
		NiPointer<NiTexture> spLookupTexture;              // 68
		BSGraphics::TextureAddressMode eTextureClampMode;  // 70
		NiPointer<BSTextureSet> spTextureSet;              // 78
		float fMaterialAlpha;                              // 80
		float fRefractionPower;                            // 84
		float fSmoothness;                                 // 88
		float fSpecularColorScale;                         // 8C
		float fFresnelPower;                               // 90
		float fWetnessControl_SpecScale;                   // 94
		float fWetnessControl_SpecPowerScale;              // 98
		float fWetnessControl_SpecMin;                     // 9C
		float fWetnessControl_EnvMapScale;                 // A0
		float fWetnessControl_FresnelPower;                // A4
		float fWetnessControl_Metalness;                   // A8
		float fSubsurfaceLightRolloff;                     // AC
		float fRimLightPower;                              // B0
		float fBackLightPower;                             // B4
		float fLookupScale;                                // B8
		BSNonReentrantSpinLock LoadTextureSetLock;         // BC
	};
	static_assert(sizeof(BSLightingShaderMaterialBase) == 0xC0);

	REL::Relocation<BSLightingShaderMaterialBase*> BSLightingShaderMaterialBase__pLightingDefault(1060450);

	class BSLightingShaderMaterial : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterial };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterial };
		static constexpr auto TYPE{ ShaderTypes::kDefault };

		virtual ~BSLightingShaderMaterial();
	};

	class BSLightingShaderMaterialDismemberment : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialDismemberment };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialDismemberment };
		static constexpr auto TYPE{ ShaderTypes::kDismemberment };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_DISMEMBER
		{
			MD_LS_DISMEMBER = 0x19,
			MD_LS_DISMEMBER_END = 0x1A,
		};

		//members
		NiPointer<NiTexture> spDisplacementTexture;
	};

	class BSLightingShaderMaterialEnvmap : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialEnvmap };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialEnvmap };
		static constexpr auto TYPE{ ShaderTypes::kEnvmap };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_ENVMAP
		{
			MD_LS_ENVMAP = 0x19,
			MD_LS_ENVMAP_MASK = 0x1A,
			MD_LS_ENVMAP_SCALE = 0x1B,
			MD_LS_ENVMAP_SSR = 0x1C,
			MD_LS_ENVMAP_SSR_WET = 0x1D,
			MD_LS_ENVMAP_END = 0x1E,
		};
		//members
		NiPointer<NiTexture> spEnvTexture;
		NiPointer<NiTexture> spEnvMaskTexture;
		float fEnvmapScale;
		bool bUseScreenSpaceReflections;
		bool bWetnessControl_UseScreenSpaceReflections;
	};

	class BSLightingShaderMaterialEye : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialEye };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialEye };
		static constexpr auto TYPE{ ShaderTypes::kEye };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_EYE
		{
			MD_LS_EYE = 0x19,
			MD_LS_EYE_MASK = 0x1A,
			MD_LS_EYE_CENTER_0_X = 0x1B,
			MD_LS_EYE_CENTER_0_Y = 0x1C,
			MD_LS_EYE_CENTER_0_Z = 0x1D,
			MD_LS_EYE_CENTER_1_X = 0x1E,
			MD_LS_EYE_CENTER_1_Y = 0x1F,
			MD_LS_EYE_CENTER_1_Z = 0x20,
			MD_LS_EYE_SCALE = 0x21,
			MD_LS_EYE_END = 0x22,
		};

		//members
		NiPointer<NiTexture> spEnvTexture;
		NiPointer<NiTexture> spEnvMaskTexture;
		NiPoint3 kEyeCenter[2];
		float fEnvmapScale;
	};

	class BSLightingShaderMaterialFace : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialFace };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialFace };
		static constexpr auto TYPE{ ShaderTypes::kFace };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_FACE
		{
			MD_LS_FACE_WRINKLE = 0x19,
			MD_LS_FACE_END = 0x1A,
		};

		//members
		NiPointer<NiTexture> spWrinklesTexture;
	};

	class BSLightingShaderMaterialGlowmap : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialGlowmap };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialGlowmap };
		static constexpr auto TYPE{ ShaderTypes::kGlowmap };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_GLOWMAP
		{
			MD_LS_GLOWMAP = 0x19,
			MD_LS_GLOWMAP_END = 0x1A,
		};

		//members
		NiPointer<NiTexture> spGlowTexture;
	};

	class BSLightingShaderMaterialLODLandscape : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialLODLandscape };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialLODLandscape };
		static constexpr auto TYPE{ ShaderTypes::kLODLandscape };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_LOD_LANDSCAPE
		{
			MD_LS_LOD_LANDSCAPE_DIFFUSE = 0x19,
			MD_LS_LOD_LANDSCAPE_NORMAL = 0x1A,
			MD_LS_LOD_LANDSCAPE_NOISE = 0x1B,
			MD_LS_LOD_LANDSCAPE_TEX_OFFSET_X = 0x1C,
			MD_LS_LOD_LANDSCAPE_TEX_OFFSET_Y = 0x1D,
			MD_LS_LOD_LANDSCAPE_TEX_FADE = 0x1E,
			MD_LS_LOD_LANDSCAPE_END = 0x1F,
		};

		//members
		NiPointer<NiTexture> spParentDiffuseTexture;
		NiPointer<NiTexture> spParentNormalTexture;
		NiPointer<NiTexture> spLandscapeNoiseTexture;
		NiPointer<NiTexture> spLandscapeDetailNormalTexture;
		float fTerrainTexOffsetX;
		float fTerrainTexOffsetY;
		float fTerrainTexFade;
	};

	class BSLightingShaderMaterialLandscape : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialLandscape };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialLandscape };
		static constexpr auto TYPE{ ShaderTypes::kLandscape };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_LANDSCAPE
		{
			MD_LS_LANDSCAPE_TEXTURES = 0x19,
			MD_LS_LANDSCAPE_DIFFUSE_0 = 0x1A,
			MD_LS_LANDSCAPE_DIFFUSE_1 = 0x1B,
			MD_LS_LANDSCAPE_DIFFUSE_2 = 0x1C,
			MD_LS_LANDSCAPE_NORMAL_0 = 0x1D,
			MD_LS_LANDSCAPE_NORMAL_1 = 0x1E,
			MD_LS_LANDSCAPE_NORMAL_2 = 0x1F,
			MD_LS_LANDSCAPE_SMOOTH_0 = 0x20,
			MD_LS_LANDSCAPE_SMOOTH_1 = 0x21,
			MD_LS_LANDSCAPE_SMOOTH_2 = 0x22,
			MD_LS_LANDSCAPE_LOD_BLEND = 0x23,
			MD_LS_LANDSCAPE_NOISE = 0x24,
			MD_LS_LANDSCAPE_BLEND_R = 0x25,
			MD_LS_LANDSCAPE_BLEND_G = 0x26,
			MD_LS_LANDSCAPE_BLEND_B = 0x27,
			MD_LS_LANDSCAPE_BLEND_A = 0x28,
			MD_LS_LANDSCAPE_TEX_OFFSET_X = 0x29,
			MD_LS_LANDSCAPE_TEX_OFFSET_Y = 0x2A,
			MD_LS_LANDSCAPE_TEX_FADE = 0x2B,
			MD_LS_LANDSCAPE_END = 0x2C,
		};

		//members
		bool bLandscape_WetnessControl_UseScreenSpaceReflections[3];
		float fLandscape_WetnessControl_SpecScale[3];
		float fLandscape_WetnessControl_SpecPowerScale[3];
		float fLandscape_WetnessControl_SpecMin[3];
		float fLandscape_WetnessControl_EnvMapScale[3];
		float fLandscape_WetnessControl_FresnelPower[3];
		float fLandscape_WetnessControl_Metalness[3];
		std::uint32_t uiNumLandscapeTextures;
		NiPointer<NiTexture> spLandscapeDiffuseTexture[3];
		NiPointer<NiTexture> spLandscapeNormalTexture[3];
		NiPointer<NiTexture> spLandscapeSmoothSpecTexture[3];
		NiPointer<NiTexture> spLandscapeLODBlendTexture;
		NiPointer<NiTexture> spLandscapeNoiseTexture;
		NiPointer<NiTexture> spLandscapeDetailNormalTexture;
		NiColorA kLandBlendParams;
		float fTerrainTexOffsetX;
		float fTerrainTexOffsetY;
		float fTerrainTexFade;
	};

	class BSLightingShaderMaterialMultiLayerParallax : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialMultiLayerParallax };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialMultiLayerParallax };
		static constexpr auto TYPE{ ShaderTypes::kMultiLayerParallax };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_ML_PARALAX
		{
			MD_LS_ML_PARALLAX_LAYER = 0x19,
			MD_LS_ML_PARALLAX_ENV = 0x1A,
			MD_LS_ML_PARALLAX_ENV_MASK = 0x1B,
			MD_LS_ML_PARALLAX_THICKNESS = 0x1C,
			MD_LS_ML_PARALLAX_REFRACTION_SCALE = 0x1D,
			MD_LS_ML_PARALLAX_INNER_SCALE_U = 0x1E,
			MD_LS_ML_PARALLAX_INNER_SCALE_V = 0x1F,
			MD_LS_ML_PARALLAX_ENV_SCALE = 0x20,
			MD_LS_ML_PARALLAX_END = 0x21,
		};

		//members
		NiPointer<NiTexture> spLayerTexture;
		NiPointer<NiTexture> spEnvTexture;
		NiPointer<NiTexture> spEnvMaskTexture;
		float fParallaxLayerThickness;
		float fParallaxRefractionScale;
		float fParallaxInnerLayerUScale;
		float fParallaxInnerLayerVScale;
		float fEnvmapScale;
	};

	class BSLightingShaderMaterialParallax : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialParallax };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialParallax };
		static constexpr auto TYPE{ ShaderTypes::kParallax };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_PARALLAX
		{
			MD_LS_PARALLAX_HEIGHT = 0x19,
			MD_LS_PARALLAX_END = 0x1A,
		};

		//members
		NiPointer<NiTexture> spHeightTexture;
	};

	class BSLightingShaderMaterialParallaxOcc : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialParallaxOcc };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialParallaxOcc };
		static constexpr auto TYPE{ ShaderTypes::kParallaxOcc };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_PARALLAX_OCC
		{
			MD_LS_PARALLAX_OCC_HEIGHT = 0x19,
			MD_LS_PARALLAX_OCC_MAXPASSES = 0x1A,
			MD_LS_PARALLAX_OCC_SCALE = 0x1B,
			MD_LS_PARALLAX_OCC_END = 0x1C,
		};

		//members
		NiPointer<NiTexture> spHeightTexture;
		float fParallaxOccMaxPasses;
		float fParallaxOccScale;
	};

	class BSLightingShaderMaterialSkinTint : public BSLightingShaderMaterialBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderMaterialSkinTint };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterialSkinTint };
		static constexpr auto TYPE{ ShaderTypes::kSkinTint };

		enum LIGHTING_SHADER_MATERIAL_DIFFERENCES_SKIN_TINT
		{
			MD_LS_SKIN_TINT_COLOR_R = 0x19,
			MD_LS_SKIN_TINT_COLOR_G = 0x1A,
			MD_LS_SKIN_TINT_COLOR_B = 0x1B,
			MD_LS_SKIN_TINT_COLOR_A = 0x1C,
			MD_LS_SKIN_TINT_END = 0x1D,
		};

		//members
		NiColorA kTintColor;
	};
}
