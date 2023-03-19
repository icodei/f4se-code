#pragma once
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSShader/ImageSpace.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiTArray.h"
#include "RE/NetImmerse/NiMain/NiTCollection.h"

namespace RE
{
	class ImageSpaceShaderParam : public ImageSpaceEffectParam
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceShaderParam };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceShaderParam };

		#define VCONSTANT_REG_START 0;
		#define PCONSTANT_REG_START 0;
		#define TEXOFFSET_MAX 3;

		ImageSpaceShaderParam() { ctor(); }

		virtual ~ImageSpaceShaderParam() {}

		void ResizeConstantGroup(std::uint32_t a1, std::uint32_t a2)
		{
			using func_t = decltype(&ImageSpaceShaderParam::ResizeConstantGroup);
			REL::Relocation<func_t> func{ REL::ID(707810) };
			return func(this, a1, a2);
		}

		void SetPixelConstant(std::uint32_t a1, float a2, float a3, float a4, float a5)
		{
			using func_t = decltype(&ImageSpaceShaderParam::SetPixelConstant);
			REL::Relocation<func_t> func{ REL::ID(959652) };
			return func(this, a1, a2, a3, a4, a5);
		}

		//members
		std::uint32_t field_8;
		bool SLIMode;
		float field_10;
		float field_14;
		float field_18;
		float field_1C;
		char field_20;
		std::uint32_t field_24;
		std::uint8_t gap28[4];
		float field_2C;
		float* vertexConstantGroup;
		std::uint32_t arraySize_38;
		float* pixelConstantGroup;
		std::uint32_t arraySize_48;
		NiTObjectArray<NiPointer<NiTexture>> ObjArray__NiTexture;
		NiTPrimitiveArray<BSGraphics::TextureFilterMode> tArray__TextureFilterMode;
		std::uint32_t dispatchVal_80;
		std::uint32_t dispatchVal_84;
		std::uint8_t gap88[4];
		std::uint32_t field_8C;

	private:
		ImageSpaceShaderParam* ctor()
		{
			using func_t = decltype(&ImageSpaceShaderParam::ctor);
			REL::Relocation<func_t> func{ REL::ID(109702) };
			return func(this);
		}
	};
	static_assert(sizeof(ImageSpaceShaderParam) == 0x90);
}
