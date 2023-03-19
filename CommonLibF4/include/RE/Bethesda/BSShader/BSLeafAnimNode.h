#pragma once
#include "RE/Bethesda/BSShader/BSFadeNode.h"

namespace RE
{
	class BSLeafAnimNode : public BSFadeNode
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLeafAnimNode };
		static constexpr auto VTABLE{ VTABLE::BSLeafAnimNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSLeafAnimNode };

		//members
		float fSqrDistanceToCamera;
		float fLeafAmplitudeRefr;
		float fLeafFrequency;
		float fRunningTime;
		float fPreviousTimer;
	};
}
