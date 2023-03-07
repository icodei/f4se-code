#pragma once
#include "RE/Bethesda/BSSceneGraph.h"

namespace RE
{
	class SceneGraph : public BSSceneGraph
	{
	public:
		static constexpr auto RTTI{ RTTI::SceneGraph };
		static constexpr auto VTABLE{ VTABLE::SceneGraph };
		static constexpr auto Ni_RTTI{ Ni_RTTI::SceneGraph };

		virtual ~SceneGraph();

		//members
		float nearDistance;			//160
		float farDistance;			//164
		bool useCustomNearDistance;	//168
		bool useCustomFarDistance;	//169
	};
	static_assert(sizeof(SceneGraph) == 0x170);
}
