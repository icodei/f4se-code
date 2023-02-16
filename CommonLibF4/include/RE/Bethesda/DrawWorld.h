#pragma once
#include "RE/Bethesda/BSCulling.h"
#include "RE/Bethesda/BSShader.h"
#include "RE/NetImmerse/NiCamera.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class DrawWorld
	{
	private:
		using VATSEffectRenderFunc_t = void (*)(NiCamera*);
		using Interface3DRenderFN_t = void (*)(std::uint32_t);
		using Additional1stPersonFunc_t = void (*)(BSTArray<NiPointer<NiAVObject>>&);

	public:
		REL::Relocation<NiAVObject*> DrawWorld_p1stPerson{ REL::ID() };
		REL::Relocation<NiAVObject*> DrawWorld_pScreenSplatterRoot{ REL::ID() };
		REL::Relocation<NiCamera*> DrawWorld_pCamera{ REL::ID() };
		REL::Relocation<NiCamera*> DrawWorld_pVisCamera{ REL::ID() };
		REL::Relocation<NiCamera*> DrawWorld_pScreenSplatterCamera{ REL::ID() };

		REL::Relocation<VATSEffectRenderFunc_t*> DrawWorld_VATSEffectRenderFunc{ REL::ID() };

		REL::Relocation<Interface3DRenderFN_t*> DrawWorld_Interface3DRenderFN{ REL::ID() };

		REL::Relocation<Additional1stPersonFunc_t*> DrawWorld_Additional1stPersonFunc{ REL::ID() };

		REL::Relocation<NiPointer<BSGeometry>> DrawWorld_spUnitBox{ REL::ID() };
		REL::Relocation<NiPointer<NiCamera>> DrawWorld_sp1stPersonCamera{ REL::ID() };

		REL::Relocation<NiPointer<BSShaderAccumulator>> DrawWorld_spDraw1stPersonAccum{ REL::ID() };

		REL::Relocation<BSCullingGroup> DrawWorld_k1stPersonCullingGroup{ REL::ID() };
		REL::Relocation<BSTArray<NiPointer<NiAVObject>>> DrawWorld_Additional1stPersonGeom{ REL::ID() };
	};

}
