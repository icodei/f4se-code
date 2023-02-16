#pragma once
#include "RE/NetImmerse/NiNode.h"

namespace RE
{
	class BSSceneGraph : public NiNode
	{
	public:

		static constexpr auto RTTI{ RTTI::BSSceneGraph };
		static constexpr auto VTABLE{ VTABLE::BSSceneGraph };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSSceneGraph };

		virtual ~BSSceneGraph();

		//add
		virtual void GetFarDistance();
		virtual void GetNearDistance();
		virtual void SetViewDistanceBasedOnFrameRate();
	};
}
