#pragma once
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTArray.h"
#include "RE/NetImmerse/NiTexture.h"

namespace RE
{
	class ImageSpaceManager;
	class BSTriShape;

	class ImageSpaceTexture
	{
	public:
		//ImageSpaceTexture::GetRenderTarget(): This is not a render target.  Use QIsRenderTarget() first.
		//ImageSpaceTexture::GetDepthStencilBuffer(): This is not depth stencil buffer.  Use QIsDepthStencilBuffer() first

		//members
		bool unk01;
		NiPointer<NiTexture> tex;
		int RenderTarget;
		int DepthBuffer;
		int StencilBuffer;
		BSGraphics::TextureFilterMode FilterMode;
		BSGraphics::TextureAddressMode ClampMode;
		bool isAcquired;
	};

	class ImageSpaceEffectParam
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceEffectParam };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectParam };

		ImageSpaceEffectParam() { ctor(); }
		virtual ~ImageSpaceEffectParam() {}

	private:
		ImageSpaceEffectParam* ctor()
		{
			using func_t = decltype(&ImageSpaceEffectParam::ctor);
			REL::Relocation<func_t> func{ REL::ID(1464304) };
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
			//members
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

		ImageSpaceEffect() { ctor(); }

		virtual ~ImageSpaceEffect() {}

		//add
		virtual void Render(BSTriShape*, ImageSpaceEffectParam*) { return; }
		virtual void Dispatch(ImageSpaceEffectParam*, bool, std::uint32_t, EffectDesc*) { return; }
		virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*) { return; }
		virtual void Shutdown(void) { return; }
		virtual void BorrowTextures(ImageSpaceEffectParam*) { return; }
		virtual void ReturnTextures(void) { return; }
		virtual void UpdateComputeShaderParam(std::uint32_t) { return; }
		virtual bool IsActive(void) { return false; }
		virtual bool UpdateParams(ImageSpaceEffectParam*) { return false; }
		virtual bool SetRenderStates(ImageSpaceEffectParam*) { return false; }
		virtual bool RestoreRenderStates(ImageSpaceEffectParam*) { return false; }

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
	static_assert(sizeof(ImageSpaceBaseData) == 0x58);

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
