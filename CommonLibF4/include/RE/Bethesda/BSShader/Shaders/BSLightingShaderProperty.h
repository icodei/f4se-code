#pragma once
#include "RE/Bethesda/BSShader/BSShaderProperty.h"

namespace RE
{
	class BSLightingShaderProperty : public BSShaderProperty
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSLightingShaderProperty };

		virtual ~BSLightingShaderProperty();

		NiTexture* GetBaseTexture()
		{
			using func_t = decltype(&BSLightingShaderProperty::GetBaseTexture);
			REL::Relocation<func_t> func{ REL::ID(1242168) };
			return func(this);
		}

		BSLightingShaderMaterialBase* GetLightingShaderMaterial()
		{
			using func_t = decltype(&BSLightingShaderProperty::GetLightingShaderMaterial);
			REL::Relocation<func_t> func{ REL::ID(958611) };
			return func(this);
		}

		NiTexture* GetNormalTexture()
		{
			using func_t = decltype(&BSLightingShaderProperty::GetNormalTexture);
			REL::Relocation<func_t> func{ REL::ID(407460), 0x57 };
			return func(this);
		}

		static NiObject* CreateObject()
		{
			using func_t = decltype(&BSLightingShaderProperty::CreateObject);
			REL::Relocation<func_t> func{ REL::ID(1120904) };
			return func();
		}

		static BSLightingShaderProperty* Create()
		{
			return (BSLightingShaderProperty*)CreateObject();
		}

		//members
		NiColorA kProjectedUVColor;                   // 70
		NiColorA kProjectedUVParams;                  // 80
		RenderPassArray kDepthMapRenderPassListA[3];  // 90
		BSRenderPass* pDepthRenderPass;               // A8
		RenderPassArray kForwardPassList;             // B0
		NiColor* pEmissiveColor;                      // B8
		BSFixedString rootName;                       // C0
		float fEmitColorScale;                        // C8
		float fForcedDarkness;                        // CC
		float fSpecularLODFade;                       // D0
		float fEnvmapLODFade;                         // D4
		std::uint32_t uiBaseTechniqueID;              // D8
		std::uint32_t ClearCommandBufferCount;        // DC
		std::uint16_t usDebugTintIndex;               // E0
		std::uint16_t uiStencilRef;                   // E2
	};
	static_assert(sizeof(BSLightingShaderProperty) == 0xE8);
}
