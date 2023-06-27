#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiTArray.h"
#include "RE/NetImmerse/NiMain/NiTexture.h"

namespace RE
{
	class ImageSpaceManager;
	class BSTriShape;

	class ImageSpaceTexture
	{
	public:
		//ImageSpaceTexture::GetDepthStencilBuffer(): This is not depth stencil buffer.  Use QIsDepthStencilBuffer() first

		//void SetTextureRenderTarget(std::int32_t a_target) {}                       //TODO
		//void SetTextureDepthBuffer(std::int32_t a_target) {}                        //TODO
		//void SetTextureStencilBuffer(std::int32_t a_target) {}                      //TODO
		//void SetTexture(NiTexture* a_texture) {}                                    //TODO
		//void GetDimensions(std::int32_t& a_width, std::int32_t& a_height) const {}  //TODO
		NiTexture* GetTexture() const {}                                            //TODO

		std::int32_t GetRenderTarget() const
		{
			if (RenderTarget < 0) {
				//Assert: ImageSpaceTexture::GetRenderTarget(): This is not a render target.  Use QIsRenderTarget() first.
			}
			using func_t = decltype(&ImageSpaceTexture::GetRenderTarget);
			REL::Relocation<func_t> func{ REL::ID(332612) };
			return func(this);
		}

		ImageSpaceTexture& operator=(ImageSpaceTexture& a_ref) { return op_equals(a_ref); }

		//members
		bool unk01;
		NiPointer<NiTexture> tex;
		int RenderTarget;
		int DepthBuffer;
		int StencilBuffer;
		BSGraphics::TextureFilterMode FilterMode;
		BSGraphics::TextureAddressMode ClampMode;
		bool isAcquired;

	private:
		//ImageSpaceTexture* ctor() {}
		//ImageSpaceTexture* copy_ctor(ImageSpaceTexture& a_ref) {}
		ImageSpaceTexture& op_equals(ImageSpaceTexture& a_ref)
		{
			using func_t = decltype(&ImageSpaceTexture::op_equals);
			REL::Relocation<func_t> func{ REL::ID(1420823) };
			return func(this, a_ref);
		}
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
		virtual void Dispatch(ImageSpaceEffectParam*, bool, std::uint32_t, EffectDesc*) { return; }	//Assert: Only BSImagespaceComputeShaders should call dispatch.
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
		bool isComputeShader;
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
