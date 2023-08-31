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
		// members
		bool forceAniso;                           // 00
		NiTexture* texture;                        // 08
		std::int32_t renderTarget;                 // 10
		std::int32_t depthBuffer;                  // 14
		std::int32_t stencilBuffer;                // 18
		BSGraphics::TextureFilterMode filterMode;  // 1C
		BSGraphics::TextureAddressMode clampMode;  // 20
		bool acquiredTarget;                       // 24
	};
	static_assert(sizeof(ImageSpaceTexture) == 0x28);

	class __declspec(novtable) ImageSpaceEffectParam
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceEffectParam };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceEffectParam };

		ImageSpaceEffectParam()
		{
			typedef ImageSpaceEffectParam* func_t(ImageSpaceEffectParam*);
			REL::Relocation<func_t> func{ REL::ID(1464304) };
			func(this);
		}

		virtual ~ImageSpaceEffectParam() {}	// 00
	};

	class __declspec(novtable) ImageSpaceEffect
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceEffect };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceEffect };

		struct EffectDesc
		{
		public:
			// members
			std::uint32_t startEffect;       // 00
			std::uint32_t lastEffect;        // 04
			ImageSpaceEffect* parentEffect;  // 08
			std::uint64_t labelWait;         // 10
			std::uint64_t* writeLabel;       // 18
		};
		static_assert(sizeof(EffectDesc) == 0x20);

		struct EffectInput
		{
		public:
			// members
			std::int32_t texIndex;                     // 00
			BSGraphics::TextureFilterMode filterMode;  // 04
		};
		static_assert(sizeof(EffectInput) == 0x08);

		ImageSpaceEffect()
		{
			typedef ImageSpaceEffect* func_t(ImageSpaceEffect*);
			REL::Relocation<func_t> func{ REL::ID(343213) };
			func(this);
		}

		virtual ~ImageSpaceEffect() {}

		// add
		virtual void Render(BSTriShape* a_geometry, ImageSpaceEffectParam* a_param);                                                   // 01
		virtual void Dispatch(ImageSpaceEffectParam* a_param, bool a_useAsyncPipe, std::uint32_t a_effect, EffectDesc* a_effectDesc);  // 02 - Only BSImagespaceComputeShaders should call dispatch.
		virtual void Setup(ImageSpaceManager* a_manager, ImageSpaceEffectParam* a_param);                                              // 03
		virtual void Shutdown();                                                                                                       // 04
		virtual void BorrowTextures(ImageSpaceEffectParam* a_param);                                                                   // 05
		virtual void ReturnTextures();                                                                                                 // 06
		virtual void UpdateComputeShaderParam(std::uint32_t a_effect);                                                                 // 07
		virtual bool IsActive();                                                                                                       // 08
		virtual bool UpdateParams(ImageSpaceEffectParam* a_param);                                                                     // 09
		virtual bool SetRenderStates(ImageSpaceEffectParam* a_param);                                                                  // 0A
		virtual bool RestoreRenderStates(ImageSpaceEffectParam* a_param);                                                              // 0B

		// members
		bool isActive;                                              // 08
		bool paramsChanged;                                         // 09
		NiTPrimitiveArray<ImageSpaceEffect*> effectList;            // 10
		NiTPrimitiveArray<ImageSpaceEffectParam*> effectParamList;  // 28
		NiTPrimitiveArray<ImageSpaceTexture*> textures;             // 40
		NiTPrimitiveArray<ImageSpaceTexture*> vsTextures;           // 58
		NiTPrimitiveArray<EffectInput*> effectInputs;               // 70
		NiTPrimitiveArray<std::int32_t*> effectOutput;              // 88
		bool isComputeShader;                                       // A0
		std::uint32_t nbOutput;                                     // A4
		bool useDynamicResolution;                                  // A8
	};
	static_assert(sizeof(ImageSpaceEffect) == 0xB0);

	struct ImageSpaceBaseData
	{
	public:
		// members
		float hdrData[9];        // 00
		float cinematicData[3];  // 24
		float tintData[4];       // 30
		float dofData[6];        // 40
	};
	static_assert(sizeof(ImageSpaceBaseData) == 0x58);

	struct ImageSpaceLUTData
	{
	public:
		// members
		BSFixedString filename[4];          // 00
		float weight[4];                    // 20
		NiPointer<NiTexture> niTexture[4];  // 30
		BSGraphics::Texture* texture[4];    // 50
	};
	static_assert(sizeof(ImageSpaceLUTData) == 0x70);

	struct ImageSpaceModData
	{
	public:

		enum data
		{
		};

		// members
		float data[20];  // 00
	};
	static_assert(sizeof(ImageSpaceModData) == 0x50);

	struct ImageSpaceData
	{
	public:
		// members
		ImageSpaceBaseData baseData;  //00
		ImageSpaceModData modData;    //58
		float highestTintAmount;      //A8
		float highestFadeAmount;      //AC
	};
	static_assert(sizeof(ImageSpaceData) == 0xB0);
}
