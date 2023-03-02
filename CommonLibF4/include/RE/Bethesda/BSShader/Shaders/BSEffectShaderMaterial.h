#pragma once
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSShader/BSShaderMaterial.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class NiTexture;

	class BSEffectShaderMaterial : public BSShaderMaterial
	{
	public:
		static constexpr auto RTTI{ RTTI::BSEffectShaderMaterial };
		static constexpr auto VTABLE{ VTABLE::BSEffectShaderMaterial };

		virtual ~BSEffectShaderMaterial();

		//members
		float fFalloffStartAngle;                          // 38
		float fFalloffStopAngle;                           // 3C
		float fFalloffStartOpacity;                        // 40
		float fFalloffStopOpacity;                         // 44
		NiColorA kBaseColor;                               // 48
		NiPointer<NiTexture> spBaseTexture;                // 58
		NiPointer<NiTexture> spGrayscaleTexture;           // 60
		NiPointer<NiTexture> spEnvironmentMapTexture;      // 68
		NiPointer<NiTexture> spEnvironmentMapMaskTexture;  // 70
		NiPointer<NiTexture> spNormalTexture;              // 78
		float fSoftDepth;                                  // 80
		float fBaseColorScale;                             // 84
		BSFixedString strBaseTexture;                      // 88
		BSFixedString strGrayscaleTexture;                 // 90
		BSFixedString strEnvironmentMapTexture;            // 98
		BSFixedString strEnvironmentMapMaskTexture;        // A0
		BSFixedString strNormalTexture;                    // A8
		union
		{
			float fEnvironmentMaskScale;  // B0
			float fRefractionPower;       // B0 - Needs kShaderFlags_Refraction
		};
		std::uint8_t uTextureClampMode;      // B4
		std::uint8_t uLightingInfluence;     // B5 - divided by 255
		std::uint8_t uEnvironmentMapMinLOD;  // B6
		std::uint8_t unkB7;                  // B7
	};
	static_assert(sizeof(BSEffectShaderMaterial) == 0xB8);

	REL::Relocation<BSEffectShaderMaterial*> BSEffectShaderMaterial__pEffectDefault(1415090);
}
