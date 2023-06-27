#pragma once
#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BSCore/BSSimpleList.h"
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"

#include <DirectXMath.h>
#include <d3d11.h>

namespace RE
{
	namespace BSGraphics
	{
		class RenderTargetManager
		{
		public:
			[[nodiscard]] static RenderTargetManager& GetSingleton()
			{
				REL::Relocation<RenderTargetManager*> singleton{ REL::ID(1508457) };
				return *singleton;
			}

			enum class TARGET_PERSISTENCY
			{
				TARGET_PERSISTENCY_SHARED,
				TARGET_PERSISTENCY_ALWAYS,
				TARGET_PERSISTENCY_NEVER
			};

			struct TargetHandle
			{
			public:
				//members
				std::uint32_t TargetId;
				BSTAtomicValue<std::int32_t> AcquireCount;
				BSTAtomicValue<std::int32_t> Reserved;
			};

			using TargetHandleList = BSSimpleList<BSGraphics::RenderTargetManager::TargetHandle*>;

			struct Persistency
			{
			public:
				//members
				TARGET_PERSISTENCY m_Persistency;
				bool m_KeepTarget;
			};

			RenderTargetManager();
			~RenderTargetManager();

			void SetFrameBufferProperties();  //TODO

			void CreateRenderTarget(std::uint32_t target, RenderTargetProperties& targetProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(43433) };
				return func(this, target, targetProps, persist);
			}

			void CreateDepthStencilTarget(std::uint32_t target, DepthStencilTargetProperties& depthProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateDepthStencilTarget);
				REL::Relocation<func_t> func{ REL::ID(1159619) };
				return func(this, target, depthProps, persist);
			}

			void CreateCubeMapRenderTarget(std::uint32_t target, CubeMapRenderTargetProperties& cubeProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateCubeMapRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1397856) };
				return func(this, target, cubeProps, persist);
			}

			void SetRenderTargetPersistency();           //TODO
			void QRenderTargetTextureWidth();            //TODO
			void QRenderTargetTextureHeight();           //TODO
			void QRenderTargetRenderingWidth();          //TODO
			void QRenderTargetRenderingHeight();         //TODO
			void QCurrentRenderTargetWidth();            //TODO
			void QCurrentRenderTargetHeight();           //TODO
			void QRenderTargetProperties();              //TODO
			void QCurrentRenderTarget();                 //TODO
			void QCurrentPlatformRenderTarget();         //TODO
			void QDepthStencilTargetWidth();             //TODO
			void QDepthStencilTargetHeight();            //TODO
			void QCurrentDepthStencilTarget();           //TODO
			void QCurrentPlatformDepthStencilTarget();   //TODO
			void QCubeMapRenderTargetWidth();            //TODO
			void QCubeMapRenderTargetHeight();           //TODO
			void QCurrentCubeMapRenderTargetWidth();     //TODO
			void QCurrentCubeMapRenderTargetHeight();    //TODO
			void QCurrentCubeMapRenderTarget();          //TODO
			void QCurrentPlatformCubeMapRenderTarget();  //TODO

			void SetCurrentRenderTarget(std::int32_t shadowRenderTarget, std::int32_t renderTarget, SetRenderTargetMode targetMode)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1502425) };
				return func(this, shadowRenderTarget, renderTarget, targetMode);
			}

			void SetCurrentDepthStencilTarget(std::int32_t depthStencilTarget, SetRenderTargetMode targetMode, std::int32_t depthStencilSliceIndex, [[maybe_unused]] bool a3)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentDepthStencilTarget);
				REL::Relocation<func_t> func{ REL::ID(704517) };
				return func(this, depthStencilTarget, targetMode, depthStencilSliceIndex, a3);
			}

			void SetCurrentCubeMapRenderTarget();       //TODO
			void SetCurrentViewportCustomDimensions();  //TODO
			void SetCurrentViewportDefault();           //TODO

			void SetCurrentViewportForceToRenderTargetDimensions()
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentViewportForceToRenderTargetDimensions);
				REL::Relocation<func_t> func{ REL::ID(1208720) };
				return func(this);
			}

			void SetUseDynamicResolutionViewportAsDefaultViewport(bool a1)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetUseDynamicResolutionViewportAsDefaultViewport);
				REL::Relocation<func_t> func{ REL::ID(676851) };
				return func(this, a1);
			}

			void GetUseDynamicResolutionViewportAsDefaultViewport();  //TODO
			void UpdateDynamicResolution();                           //TODO
			void QGetDynamicWidthRatio();                             //TODO
			void SetDynamicWidthRatio();                              //TODO
			void QGetDynamicHeightRatio();                            //TODO
			void SetDynamicHeightRatio();                             //TODO
			void QIsDynamicResolutionCurrentlyActivated();            //TODO
			void SetLowestWidthRatio();                               //TODO
			void SetLowestHeightRatio();                              //TODO
			void SetFreezeDynamicResolution();                        //TODO
			void QGetFreezeDynamicResolution();                       //TODO
			void QGetEnableDynamicResolution();                       //TODO
			void SetEnableDynamicResolution();                        //TODO
			void QIncreaseSpeed();                                    //TODO
			void QDecreaseSpeed();                                    //TODO
			void SetIncreaseSpeedRatio();                             //TODO
			void SetDecreaseSpeedRatio();                             //TODO
			void SetIncreaseResolution();                             //TODO
			void SetMovementDelta();                                  //TODO
			void SetOnlyIncreaseWhenMoving();                         //TODO
			void QOnlyIncreaseWhenMoving();                           //TODO
			void SetNbFramePause();                                   //TODO

			void SetTextureRenderTarget(std::int32_t textureID, std::int32_t renderTargetID, bool copyView)
			{
				if (textureID >= 16) {
					//Assert: Bad texture stage
				}
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1433009) };
				return func(this, textureID, renderTargetID, copyView);
			}

			void SetTextureRenderTarget_2(std::uint32_t textureID, std::int32_t renderTargetID, BSGraphics::TextureAddressMode texMode, bool copyView)
			{
				if (textureID >= 16) {
					//Assert: Bad texture stage
				}
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureRenderTarget_2);
				REL::Relocation<func_t> func{ REL::ID(1513035) };
				return func(this, textureID, renderTargetID, texMode, copyView);
			}

			void SetTextureDepth(std::int32_t textureID, std::int32_t depthStencilTargetID)
			{
				if (textureID >= 16) {
					//Assert: Bad texture stage
				}
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureDepth);
				REL::Relocation<func_t> func{ REL::ID(182949) };
				return func(this, textureID, depthStencilTargetID);
			}

			void SetTextureDepth_2(std::int32_t textureID, std::int32_t depthStencilTargetID, BSGraphics::TextureAddressMode texMode)
			{
				if (textureID >= 16) {
					//Assert: Bad texture stage
				}
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureDepth_2);
				REL::Relocation<func_t> func{ REL::ID(1405563) };
				return func(this, textureID, depthStencilTargetID, texMode);
			}

			void SetTextureStencil();              //TODO
			void SetTextureStencil_2();            //TODO
			void SetTextureCubeMap();              //TODO
			void SetVSTextureRenderTarget();       //TODO
			void SetVSTextureRenderTarget_2();     //TODO
			void SetVSTextureDepthStencil();       //TODO
			void SetVSTextureDepthStencil_2();     //TODO
			void SetCSTextureRenderTarget();       //TODO
			void SetCSTextureDepthStencil();       //TODO
			void SetCSTextureDepthStencilHTILE();  //TODO
			void SetCSUnorderedAccessTarget();     //TODO

			void CopyRenderTargetToRenderTargetCopy(std::uint32_t target, std::uint32_t target2)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToRenderTargetCopy);
				REL::Relocation<func_t> func{ REL::ID(591200) };
				return func(this, target, target2);
			}

			void AcquireRenderTarget(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(1468639) };
				return func(this, target);
			}

			void ReleaseRenderTarget(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1374956) };
				return func(this, target);
			}

			void AcquireDepthStencil(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(1015879) };
				return func(this, target);
			}

			void ReleaseDepthStencil(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(922599) };
				return func(this, target);
			}

			void AcquireCubemap(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireCubemap);
				REL::Relocation<func_t> func{ REL::ID(563587) };
				return func(this, target);
			}

			void ReleaseCubemap(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseCubemap);
				REL::Relocation<func_t> func{ REL::ID(469959) };
				return func(this, target);
			}

			bool QIsAcquiredRenderTarget(std::int32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::QIsAcquiredRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(110930) };
				return func(this, target);
			}

			void QIsAcquiredDepthStencil();                  //TODO
			void QIsAcquiredCubemap();                       //TODO
			void SyncRenderTarget();                         //TODO
			void SyncDepthTarget();                          //TODO
			void DestroyRenderTargets();                     //TODO
			void GetPlatformTargetFromRenderTarget();        //TODO
			void GetPlatformTargetFromDepthStencilTarget();  //TODO

			using CreateFunc = void (*)();

			void SetRecreateRenderTargetsCallback();  //TODO
			void RecreateRenderTargets();             //TODO

			void CopyRenderTargetToClipboard(std::int32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToClipboard);
				REL::Relocation<func_t> func{ REL::ID(1295596) };
				return func(this, target);
			}

			void CopyRenderTargetToTexture(std::int32_t target, Texture* tex, bool a3, bool a4)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToTexture);
				REL::Relocation<func_t> func{ REL::ID(1561984) };
				return func(this, target, tex, a3, a4);
			}

			Texture* SaveRenderTargetToTexture(std::int32_t renderTargetID, bool srgb, bool a2, Usage use)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SaveRenderTargetToTexture);
				REL::Relocation<func_t> func{ REL::ID(950217) };
				return func(this, renderTargetID, srgb, a2, use);
			}

#define MAX_RENDER_TARGETS 0x64         //static
#define MAX_DEPTH_STENCIL_TARGETS 0xC   //static
#define MAX_CUBEMAP_RENDER_TARGETS 0x1  //static

			//Here is where private would start
			//private:

			void MustBeKept();
			void InitializeTargets();
			void CreateTarget();
			void DestroyTarget();

			//members
			BSGraphics::RenderTargetProperties pRenderTargetDataA[MAX_RENDER_TARGETS];
			BSGraphics::DepthStencilTargetProperties pDepthStencilTargetDataA[MAX_DEPTH_STENCIL_TARGETS];
			BSGraphics::CubeMapRenderTargetProperties pCubeMapRenderTargetDataA[MAX_CUBEMAP_RENDER_TARGETS];
			std::uint32_t RenderTargetIdA[MAX_RENDER_TARGETS];
			std::uint32_t DepthStencilTargetIdA[MAX_DEPTH_STENCIL_TARGETS];
			std::uint32_t CubeMapRenderTargetIdA[MAX_CUBEMAP_RENDER_TARGETS];
			float fDynamicWidthRatio;
			float fDynamicHeightRatio;
			float fLowestWidthRatio;
			float fLowestHeightRatio;
			float fRatioIncreasePerSeconds;
			float fRatioDecreasePerSeconds;
			float fMovementDelta;
			bool bIncreaseResolution;
			bool bFreezeResolution;
			bool bUpdateResolutionOnlyWhenMoving;
			bool bUseDynamicResolutionViewportAsDefaultViewport;
			bool bIsDynamicResolutionCurrentlyActivated;
			std::uint32_t iNbFramePause;
			std::uint32_t iNbFramesSinceLastIncrease;
			BSTAtomicValue<std::uint32_t> uiDynamicResolutionDisabled;
			CreateFunc createRenderTargets;
		};
		static_assert(sizeof(RenderTargetManager) == 0xFC0);
	}
}
