#pragma once
#include "RE/NetImmerse/NiMain/NiNode.h"

namespace RE
{
	class BSCullingProcess;
	class NiCamera;

	class BSSceneGraph : public NiNode
	{
	public:

		static constexpr auto RTTI{ RTTI::BSSceneGraph };
		static constexpr auto VTABLE{ VTABLE::BSSceneGraph };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSSceneGraph };

		virtual ~BSSceneGraph();

		//add
		virtual float GetFarDistance();
		virtual float GetNearDistance();
		virtual void SetViewDistanceBasedOnFrameRate(float distance);

		//members
		NiCamera* cam;						//140
		void* field_148;					//148 Something Ni
		BSCullingProcess* cullingProcess;	//150
		bool menu;							//158
		float camFOV;						//15C
	};
}
