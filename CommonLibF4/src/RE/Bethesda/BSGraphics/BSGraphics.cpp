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
}
