#pragma once
#include "RE/NetImmerse/NiMain/NiAVObject.h"
#include "RE/NetImmerse/NiMain/NiBound.h"
#include "RE/NetImmerse/NiMain/NiColor.h"

namespace RE
{
	class NiLight : public NiAVObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiLight };
		static constexpr auto VTABLE{ VTABLE::NiLight };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiLight };

		//members
		NiColor m_kAmb;
		NiColor m_kDiff;
		NiColor m_kSpec;
		float m_fDimmer;
		__declspec(align(16)) NiBound ModelBound;
		void* m_pvRendererData;
	};

}
