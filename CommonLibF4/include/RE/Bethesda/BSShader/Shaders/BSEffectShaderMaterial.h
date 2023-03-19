#pragma once
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSShader/BSShaderMaterial.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiTexture;

	class BSEffectShaderMaterial : public BSShaderMaterial
	{
	public:
		static constexpr auto RTTI{ RTTI::BSEffectShaderMaterial };
		static constexpr auto VTABLE{ VTABLE::BSEffectShaderMaterial };
		static constexpr auto TYPE{ BSMATERIAL_TYPE_EFFECT };

		virtual ~BSEffectShaderMaterial();

		static BSEffectShaderMaterial* GetDefaultMaterial()
		{
			REL::Relocation<BSEffectShaderMaterial**> singleton{ REL::ID(1415090) };
			return *singleton;
		}

		void SetBaseTexture(NiTexture* newTex)
		{
			NiTexture* oldTex = spBaseTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				spBaseTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetEnvMap(NiTexture* newTex)
		{
			NiTexture* oldTex = spEnvironmentMapTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				spEnvironmentMapTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetEnvMapMask(NiTexture* newTex)
		{
			NiTexture* oldTex = spEnvironmentMapMaskTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				spEnvironmentMapMaskTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetGrayscaleTexture(NiTexture* newTex)
		{
			NiTexture* oldTex = spGrayscaleTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				spGrayscaleTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetNormalMap(NiTexture* newTex)
		{
			NiTexture* oldTex = spNormalTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				spNormalTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

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
}
