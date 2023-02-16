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

	};
}
