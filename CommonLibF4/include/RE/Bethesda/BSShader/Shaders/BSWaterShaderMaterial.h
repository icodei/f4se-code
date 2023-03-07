#pragma once
#include "RE/Bethesda/BSShader/BSShaderMaterial.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPlane.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class NiTexture;

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
