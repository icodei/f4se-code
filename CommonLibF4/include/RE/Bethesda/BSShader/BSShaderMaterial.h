#pragma once
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPlane.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSEffectShaderPropertyColorController;
	class BSEffectShaderPropertyFloatController;
	class BSLightingShaderMaterialBase;
	class BSLightingShaderMaterialEnvmap;
	class BSLightingShaderPropertyColorController;
	class BSLightingShaderPropertyFloatController;
	class BSLightingShaderPropertyUShortController;
	class BSNiAlphaPropertyTestRefController;
	class BSShaderData;
	class BSShaderProperty;
	class BSTextureSet;
	class NiTexture;

	class BSShaderMaterial : public BSIntrusiveRefCounted
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShaderMaterial };
		static constexpr auto VTABLE{ VTABLE::BSShaderMaterial };

		enum ShaderTypes
		{
			kDefault = 0,
			kEnvmap,
			kGlowmap,
			kParallax,
			kFace,
			kSkinTint,
			kHairTint,
			kParallaxOcc,
			kLandscape,
			kLODLandscape,
			kSnow,
			kMultiLayerParallax,
			kTreeAnim,
			kLODObjects,
			kMultiIndexSnow,
			kLODObjectsHD,
			kEye,
			kCloud,
			kLODLandscapeNoise,
			kLODLandscapeBlend,
			kDismemberment
		};

		enum MATERIAL_DIFFERENCES
		{
			MD_TYPE = 0x0,
			MD_END = 0x1,
		};


		virtual ~BSShaderMaterial();

		//add
		virtual BSShaderMaterial* Create();
		virtual void CopyMembers(const BSShaderMaterial* other);
		virtual void ComputeCRC32(std::uint32_t, bool);
		virtual BSShaderMaterial* GetDefault();
		virtual std::uint32_t GetFeature();
		virtual std::uint32_t GetType();
		virtual void ReceiveValuesFromRootMaterial(BSShaderProperty* a_property);
		virtual bool DoIsCopy(const BSShaderMaterial* other);

		//members
		NiPoint2 textCoordOffset[2];  // 0C
		NiPoint2 textCoordScale[2];   // 1C
		std::uint32_t unk2C;          // 2C
		std::uint32_t uiHashKey;      // 30
		std::uint32_t uiUniqueCode;   // 34
	};
	static_assert(sizeof(BSShaderMaterial) == 0x38);

	REL::Relocation<BSShaderMaterial*> BSShaderMaterial__pDefault(95118);


	class BSWaterShaderMaterial : public BSShaderMaterial
	{
	public:
		static constexpr auto RTTI{ RTTI::BSWaterShaderMaterial };
		static constexpr auto VTABLE{ VTABLE::BSWaterShaderMaterial };

		//members
		NiPointer<NiTexture> spStaticReflectionMap;
		NiPointer<NiTexture> spNormalMap01;
		NiPointer<NiTexture> spNormalMap02;
		NiPointer<NiTexture> spNormalMap03;
		NiColorA kShallowColor;
		NiColorA kDeepColor;
		NiColorA kReflectionColor;
		NiColorA kUnderwaterFogColor;
		NiColorA kLightSiltColor;
		NiColorA kDarkSiltColor;
		NiColorA kVarAmounts;
		NiColorA kWaterParams;
		NiColorA kWaterParams2;
		NiColorA kWaterParams3;
		NiColorA kWaterParams4;
		NiColorA kNormalsScroll1;
		NiColorA kNormalsScroll2;
		NiColorA kNormalsScale;
		NiColorA kNormalsAmplitude;
		NiPlane kReflectPlane;
		int uwTexOffsetX;
		int uwTexOffsetY;
		bool bUpdateConstants;
		bool bUseDefaultReflectionTexture;
		bool bUseSSR;
	};
}
