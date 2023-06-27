#pragma once
#include "RE/Bethesda/BSShader/BSShaderProperty.h"
#include "RE/Bethesda/BSShader/Shaders/BSEffectShaderMaterial.h"

namespace RE
{
	class NiTexture;

	class BSEffectShaderProperty : public BSShaderProperty
	{
	public:
		static constexpr auto RTTI{ RTTI::BSEffectShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSEffectShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSEffectShaderProperty };

		NiTexture* GetBaseTexture()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetBaseTexture);
			REL::Relocation<func_t> func{ REL::ID(1334794) };
			return func(this);
		}

		BSEffectShaderMaterial* GetEffectShaderMaterial()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetEffectShaderMaterial);
			REL::Relocation<func_t> func{ REL::ID(1096263) };
			return func(this);
		}

		NiTexture* GetEnvMap()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetEnvMap);
			REL::Relocation<func_t> func{ REL::ID(364155), 0x90 };
			return func(this);
		}

		NiTexture* GetEnvMapMask()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetEnvMapMask);
			REL::Relocation<func_t> func{ REL::ID(364155), 0xA0 };
			return func(this);
		}

		NiTexture* GetGrayscaleTexture()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetGrayscaleTexture);
			REL::Relocation<func_t> func{ REL::ID(364155), 0xB0 };
			return func(this);
		}

		NiTexture* GetNormalMap()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetNormalMap);
			REL::Relocation<func_t> func{ REL::ID(1321110), 0x10 };
			return func(this);
		}

		void SetBaseTexture(NiTexture* newTex)
		{
			BSEffectShaderMaterial* pMaterial = (BSEffectShaderMaterial*)this->material;
			NiTexture* oldTex = pMaterial->spBaseTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					InterlockedIncrement(&newTex->refCount);
				}
				pMaterial->spBaseTexture.reset(newTex);
				if (oldTex) {
					if (!InterlockedDecrement(&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetEnvMap(NiTexture* newTex)
		{
			using func_t = decltype(&BSEffectShaderProperty::SetEnvMap);
			REL::Relocation<func_t> func{ REL::ID(855637), 0x3F };
			return func(this, newTex);
		}

		void SetEnvMapMask(NiTexture* newTex)
		{
			BSEffectShaderMaterial* pMaterial = (BSEffectShaderMaterial*)material;
			NiTexture* oldTex = pMaterial->spEnvironmentMapMaskTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					InterlockedIncrement(&newTex->refCount);
				}
				pMaterial->spEnvironmentMapMaskTexture.reset(newTex);
				if (oldTex) {
					if (!InterlockedDecrement(&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetGrayscaleTexture(NiTexture* newTex)
		{
			BSEffectShaderMaterial* pMaterial = (BSEffectShaderMaterial*)material;
			NiTexture* oldTex = pMaterial->spGrayscaleTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					InterlockedIncrement(&newTex->refCount);
				}
				pMaterial->spGrayscaleTexture.reset(newTex);
				if (oldTex) {
					if (!InterlockedDecrement(&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetNormalMap(NiTexture* newTex)
		{
			BSEffectShaderMaterial* pMaterial = (BSEffectShaderMaterial*)material;
			NiTexture* oldTex = pMaterial->spNormalTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					InterlockedIncrement(&newTex->refCount);
				}
				pMaterial->spNormalTexture.reset(newTex);
				if (oldTex) {
					if (!InterlockedDecrement(&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		static NiObject* CreateObject()
		{
			using func_t = decltype(&BSEffectShaderProperty::CreateObject);
			REL::Relocation<func_t> func{ REL::ID(373342) };
			return func();
		}

		static BSEffectShaderProperty* Create()
		{
			return (BSEffectShaderProperty*)CreateObject();
		}

		//members
		BSParticleShaderCubeEmitter* pEnvCubeEmitter;  // 70
		NiColor* pExternalEmitColor;                   // 78
		std::uint32_t uBaseTextureIndex;               // 80
		float unk84;                                   // 84
	};
	static_assert(sizeof(BSEffectShaderProperty) == 0x88);
}
