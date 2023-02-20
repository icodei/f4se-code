#pragma once
#include "RE/Bethesda/BSFixedString.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTArray.h"


namespace RE
{
	class ImageSpaceManager;
	class BSTriShape;

	class ImageSpaceTexture
	{
	public:

		//ImageSpaceTexture::GetRenderTarget(): This is not a render target.  Use QIsRenderTarget() first.
		//ImageSpaceTexture::GetDepthStencilBuffer(): This is not depth stencil buffer.  Use QIsDepthStencilBuffer() first
	};

	class ImageSpaceEffectParam
	{
	public:

		static constexpr auto RTTI{ RTTI::ImageSpaceEffectParam };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectParam };

		virtual ~ImageSpaceEffectParam(){};


	};

	class ImageSpaceShaderParam : public ImageSpaceEffectParam
	{
	public:

		static constexpr auto RTTI{ RTTI::ImageSpaceShaderParam };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceShaderParam };

		ImageSpaceShaderParam() { ctor(); };
		//virtual ~ImageSpaceShaderParam();

		void ResizeConstantGroup(std::uint32_t a1, std::uint32_t a2) {
			using func_t = decltype(&ImageSpaceShaderParam::ResizeConstantGroup);
			REL::Relocation<func_t> func{ REL::ID(707810) };
			return func(this, a1, a2);
		}

		void SetPixelConstant(std::uint32_t a1, float a2, float a3, float a4, float a5) {
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
		ImageSpaceShaderParam* ctor() {
			using func_t = decltype(&ImageSpaceShaderParam::ctor);
			REL::Relocation<func_t> func{ REL::ID(109702) };
			return func(this);
		}
	};

	class ImageSpaceEffect
	{
	public:

		static constexpr auto RTTI{ RTTI::ImageSpaceEffect };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceEffect };

		class EffectInput
		{
		public:
		};
		class EffectDesc
		{
		public:
			
			//members
			std::uint64_t field_0;
			std::uint64_t field_8;
			std::uint64_t field_10;
			std::uint64_t field_18;
		};

		ImageSpaceEffect() {}

		virtual ~ImageSpaceEffect(){};

		//add
		virtual void Render(BSTriShape*, ImageSpaceEffectParam*){};
		virtual void Dispatch(ImageSpaceEffectParam*, bool, std::uint32_t, EffectDesc*){};
		virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*){};
		virtual void Shutdown(void){};
		virtual void BorrowTextures(ImageSpaceEffectParam*){};
		virtual void ReturnTextures(void){};
		virtual void UpdateComputeShaderParam(std::uint32_t){};
		virtual bool IsActive(void){};
		virtual bool UpdateParams(ImageSpaceEffectParam*){};
		virtual bool SetRenderStates(ImageSpaceEffectParam*){};
		virtual bool RestoreRenderStates(ImageSpaceEffectParam*){};

		//members
		std::uint64_t unk08;
		NiTPrimitiveArray<ImageSpaceEffect*> pImageSpaceEffectArray;
		NiTPrimitiveArray<ImageSpaceEffectParam*> pImageSpaceEffectParamArray;
		NiTPrimitiveArray<ImageSpaceTexture*> texArray;
		NiTPrimitiveArray<ImageSpaceTexture*> field_58;
		NiTPrimitiveArray<EffectInput*> pEffectInputArray;
		NiTPrimitiveArray<int*> pIntArray;
		bool field_A0;
		std::uint8_t field_A1;
		std::uint32_t field_A4;
		bool UseDynamicResolution;
		NiPointer<NiTexture> tex_B0;
		NiPointer<NiTexture> field_B8;
		std::uint32_t field_C0;
		std::uint8_t field_C4;
		std::uint8_t field_C5;
		std::uint8_t field_C6;
		std::uint8_t field_C7;
		std::uint8_t field_C8;
		std::uint64_t field_D0;
		std::uint64_t field_D8;
		BSTArray<void*> field_E0;
		BSTArray<void*> field_F8;
		std::uint8_t gap110[44];
		std::uint8_t field_13C;

	private:
		ImageSpaceEffect* ctor()
		{
			using func_t = decltype(&ImageSpaceEffect::ctor);
			REL::Relocation<func_t> func{ REL::ID(343213) };
			return func(this);
		}
	};

	class ImageSpaceBaseData
	{
	public:

		//members
		float hdrData[9];
		float cinematicData[3];
		float tintData[4];
		float dofData[6];
	};

	class ImageSpaceLUTData
	{
	public:

		//members
		BSFixedString field_0;
		std::uint8_t gap8[24];
		BSFixedString field_20;
		NiPointer<NiTexture> field_28;
		NiPointer<NiTexture> field_30;
		std::uint64_t field_38;
		std::uint64_t field_40;
		std::uint64_t field_48;
		std::uint64_t final1;
	};
}
