#pragma once
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiAlphaProperty.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiTexture;

	class BSEffectShaderData : public BSIntrusiveRefCounted
	{
	public:
		BSEffectShaderData() { ctor(); }

		//members
		bool(__cdecl* pNodeFilterFunction)(const BSFixedString*);  // 08
		NiPointer<NiTexture> spBaseTexture;                        // 10
		NiPointer<NiTexture> spPaletteTexture;                     // 18
		NiPointer<NiTexture> spBlockOutTexture;                    // 20
		BSGraphics::TextureAddressMode eTextureClampMode;          // 28
		NiColorA FillColor;                                        // 2C
		NiColorA RimColor;                                         // 3C
		float fBaseFillScale;                                      // 4C
		float fBaseFillAlpha;                                      // 50
		float fBaseRimAlpha;                                       // 54
		float fUOffset;                                            // 58
		float fVOffset;                                            // 5C
		float fUScale;                                             // 60
		float fVScale;                                             // 64
		float fEdgeExponent;                                       // 68
		float fBoundDiameter;                                      // 6C
		NiAlphaProperty::AlphaFunction eSrcBlend;                  // 70
		NiAlphaProperty::AlphaFunction eDestBlend;                 // 78
		BSGraphics::DepthStencilDepthMode eZTestFunc;              // 80
		std::uint8_t ucAlphaTestRef;                               // 84
		bool bGrayscaleToColor;                                    // 85
		bool bGrayscaleToAlpha;                                    // 86
		bool bIgnoreTextureAlpha;                                  // 87
		bool bBaseTextureProjectedUVs;                             // 88
		bool bIgnoreBaseGeomTexAlpha;                              // 89
		bool bLighting;                                            // 8A
		bool bAlpha;                                               // 8B

	private:
		BSEffectShaderData* ctor()
		{
			using func_t = decltype(&BSEffectShaderData::ctor);
			REL::Relocation<func_t> func{ REL::ID(796946) };
			return func(this);
		}
	};
}
