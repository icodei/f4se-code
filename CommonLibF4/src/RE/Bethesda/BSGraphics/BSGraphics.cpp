#include "RE/Bethesda/BSGraphics/BSGraphics.h"

namespace RE
{
	REL::Relocation<BSGraphics::Context*> BSGraphics__pDefaultContext{ REL::ID(33539) };
	REL::Relocation<BSGraphics::RendererWindow*> BSGraphics__pRendererWindow{ REL::ID(91810) };
	REL::Relocation<ID3D11Device*> BSGraphics__pDevice{ REL::ID(1454788) };
	REL::Relocation<ID3D11DeviceContext*> BSGraphics__pImmediateContext{ REL::ID(1396536) };
	REL::Relocation<ID3D11DeviceContext*> BSGraphics__pContext{ REL::ID(557671), 0xB18 };          //146A8CB18 - TLS
	REL::Relocation<BSGraphics::Context*> BSGraphics__pCurContext{ REL::ID(557671), 0xB20 };       //146A8CB20 - TLS
	REL::Relocation<std::uint32_t> BSGraphics__uiStreamingDynamicFlags{ REL::ID(557671), 0xB28 };  //146A8CB28 - TLS
	REL::Relocation<std::uint32_t> BSGraphics__uiLODLevel{ REL::ID(557671), 0x1530 };              //146A8D530 - TLS

	namespace BSGraphics
	{
		RendererWindow* GetCurrentRenderWindow()
		{
			REL::Relocation<RendererWindow**> pCurrentRenderWindow{ REL::ID(91810) };
			return *pCurrentRenderWindow;
		}

		ID3D11Device* GetDevice()
		{
			REL::Relocation<ID3D11Device**> pDevice{ REL::ID(1454788) };
			return *pDevice;
		}

		ID3D11DeviceContext* GetMainContext()
		{
			REL::Relocation<ID3D11DeviceContext**> pMainContext{ REL::ID(311146) };
			return *pMainContext;
		}

		ID3D11DeviceContext* GetImmediateContext()
		{
			REL::Relocation<ID3D11DeviceContext**> pImmediateContext{ REL::ID(1396536) };
			return *pImmediateContext;
		}

		Context* GetDefaultContext()
		{
			REL::Relocation<Context**> pDefaultContext{ REL::ID(33539) };
			return *pDefaultContext;
		}

		RendererShadowState& GetRendererShadowState()
		{
			using func_t = decltype(&BSGraphics::GetRendererShadowState);
			REL::Relocation<func_t> func{ REL::ID(697019), 0x60 };
			return func();
		}

		RendererShadowState& GetLastDrawCallRendererShadowState()
		{
			using func_t = decltype(&BSGraphics::GetLastDrawCallRendererShadowState);
			REL::Relocation<func_t> func{ REL::ID(1307082), 0xC9 };
			return func();
		}
	}
}
