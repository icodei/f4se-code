#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSCullingGroup;
	class BSCullingProcess;
	class BSGeometry;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiCamera;
	class ShadowSceneNode;

	class DrawWorld
	{
	public:
		using Additional1stPersonFunc_t = void (*)(BSTArray<NiPointer<NiAVObject>>&);
		using CompanionLocalMapRenderFn_t = void (*)(void);
		using Interface3DRenderFn_t = void (*)(std::uint32_t);
		using LensFlareRenderFn_t = void (*)(NiCamera&);
		using OcclusionMapRenderFn_t = void (*)(void);
		using VATSEffectRenderFunc_t = void (*)(NiCamera*);
	};
}
