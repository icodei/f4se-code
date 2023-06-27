#pragma once
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"

#include <d3d9.h>

namespace RE
{
	namespace BSGraphics
	{
		class RendererData
		{
		public:
			[[nodiscard]] static RendererData* GetSingleton()
			{
				REL::Relocation<RendererData**> singleton{ REL::ID(1235449) };
				return *singleton;
			}

			// members
			RendererShadowState* shadowState;             // 0000
			BSD3DResourceCreator* resourceCreator;        // 0008
			std::uint32_t adapter;                        // 0010
			DXGI_RATIONAL desiredRefreshRate;             // 0014
			DXGI_RATIONAL actualRefreshRate;              // 001C
			DXGI_MODE_SCALING scaleMode;                  // 0024
			DXGI_MODE_SCANLINE_ORDER scanlineMode;        // 0028
			std::int32_t fullScreen;                      // 002C
			bool appFullScreen;                           // 0030
			bool borderlessWindow;                        // 0031
			bool vsync;                                   // 0032
			bool initialized;                             // 0033
			bool requestWindowSizeChange;                 // 0034
			std::uint32_t newWidth;                       // 0038
			std::uint32_t newHeight;                      // 003C
			std::uint32_t presentInterval;                // 0040
			ID3D11Device* device;                         // 0048
			ID3D11DeviceContext* context;                 // 0050
			RendererWindow renderWindow[32];              // 0058	- Window[0] seems to be the main display output
			RenderTarget renderTargets[101];              // 0A58
			DepthStencilTarget depthStencilTargets[13];   // 1D48
			CubeMapRenderTarget cubeMapRenderTargets[2];  // 2500
			std::byte rendererLock[0x25A8 - 0x2580];      // 2580 - TODO
			const char* className;                        // 25A8
			void* instance;                               // 25B0
			bool nvapiEnabled;                            // 25B8
		};
		static_assert(sizeof(RendererData) == 0x25C0);

		class Renderer
		{
		private:
			using ResetRenderTargets = void (*)();

		public:

			[[nodiscard]] static Renderer& GetSingleton()
			{
				REL::Relocation<Renderer*> singleton{ REL::ID(1378294) };
				return *singleton;
			}

			void Begin(std::uint32_t window) {
				using func_t = decltype(&BSGraphics::Renderer::Begin);
				REL::Relocation<func_t> func{ REL::ID(288964) };
				return func(this, window);
			}

			void End()
			{
				using func_t = decltype(&BSGraphics::Renderer::End);
				REL::Relocation<func_t> func{ REL::ID(700869) };
				return func(this);
			}

			void IncRef(Buffer* vertexBuffer)
			{
				using func_t = decltype(&BSGraphics::Renderer::IncRef);
				REL::Relocation<func_t> func{ REL::ID(1337764) };
				return func(this, vertexBuffer);
			}

			void DecRef(Buffer* vertexBuffer)
			{
				using func_t = decltype(&BSGraphics::Renderer::DecRef);
				REL::Relocation<func_t> func{ REL::ID(194808) };
				return func(this, vertexBuffer);
			}

			bool TryLock() {
				using func_t = decltype(&BSGraphics::Renderer::TryLock);
				REL::Relocation<func_t> func{ REL::ID(1259999) };
				return func(this);
			}

			void Lock() {
				using func_t = decltype(&BSGraphics::Renderer::Lock);
				REL::Relocation<func_t> func{ REL::ID(1087134) };
				return func(this);
			}

			void Unlock() {
				using func_t = decltype(&BSGraphics::Renderer::Unlock);
				REL::Relocation<func_t> func{ REL::ID(382332) };
				return func(this);
			}

			void ClearColor()
			{
				using func_t = decltype(&BSGraphics::Renderer::ClearColor);
				REL::Relocation<func_t> func{ REL::ID(673185) };
				return func(this);
			}

			Texture* CreateEmptyTexture(std::uint32_t width, std::uint32_t height)
			{
				using func_t = decltype(&BSGraphics::Renderer::CreateEmptyTexture);
				REL::Relocation<func_t> func{ REL::ID(1024513) };
				return func(this, width, height);
			}

			void DoZPrePass(NiCamera* cam1, NiCamera* cam2, float a1, float a2, float a3, float a4)
			{
				using func_t = decltype(&BSGraphics::Renderer::DoZPrePass);
				REL::Relocation<func_t> func{ REL::ID(1491502) };
				return func(this, cam1, cam2, a1, a2, a3, a4);
			}

			void Flush()
			{
				using func_t = decltype(&BSGraphics::Renderer::Flush);
				REL::Relocation<func_t> func{ REL::ID(952687) };
				return func(this);
			}

			bool MapTexture(BSGraphics::Texture* texture, Map mapType, TextureAccess& textureAccess)
			{
				using func_t = decltype(&BSGraphics::Renderer::MapTexture);
				REL::Relocation<func_t> func{ REL::ID(952687) };
				return func(this, texture, mapType, textureAccess);
			}

			void UnmapTexture(BSGraphics::Texture* texture)
			{
				using func_t = decltype(&BSGraphics::Renderer::UnmapTexture);
				REL::Relocation<func_t> func{ REL::ID(835184) };
				return func(this, texture);
			}

			void SetClearColor(float red, float green, float blue, float alpha)
			{
				using func_t = decltype(&BSGraphics::Renderer::SetClearColor);
				REL::Relocation<func_t> func{ REL::ID(1391151) };
				return func(this, red, green, blue, alpha);
			}

			void ResetZPrePass()
			{
				using func_t = decltype(&BSGraphics::Renderer::ResetZPrePass);
				REL::Relocation<func_t> func{ REL::ID(1359409) };
				return func(this);
			}

			void ResetState()
			{
				using func_t = decltype(&BSGraphics::Renderer::ResetState);
				REL::Relocation<func_t> func{ REL::ID(405603) };
				return func(this);
			}

			void RestorePreviousClearColor()
			{
				using func_t = decltype(&BSGraphics::Renderer::RestorePreviousClearColor);
				REL::Relocation<func_t> func{ REL::ID(593605) };
				return func(this);
			}

			//CUT DEBUG FUNCTIONS
			//Hook and overwrite the cut functions with these???
			//void PushDebugMarker(char const* a_name)
			//{
				//size_t v2;          // r8
				//wchar_t Dest[260];  // [rsp+20h] [rbp-208h] BYREF

				//v2 = -1;
				//do
				//	++v2;
				//while (a_name[v2]);
				//Dest[v2] = 0;
				//mbstowcs(Dest, a_name, v2);
				//D3DPERF_BeginEvent(0xFFFFFFFF, Dest);
			//}

			void PopDebugMarker()
			{
				D3DPERF_EndEvent();
			}

			// members
			bool skipNextPresent;                   // 00
			ResetRenderTargets resetRenderTargets;  // 08
			RendererData data;                      // 10
		};
		static_assert(sizeof(Renderer) == 0x25D0);
	}
}
