#pragma once
#include "RE/NetImmerse/NiNode.h"

namespace RE
{
	class ShadowSceneNode : public NiNode
	{
	public:

		static constexpr auto RTTI{ RTTI::ShadowSceneNode };
		static constexpr auto VTABLE{ VTABLE::ShadowSceneNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::ShadowSceneNode };

		void ProcessQueuedLights(BSCullingProcess* cullproc) {

		}
	};
}
