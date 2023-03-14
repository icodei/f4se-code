#include "RE/Bethesda/TESObjectREFRs.h"
#include "RE/NetImmerse/NiMain/NiAVObject.h"

namespace RE
{
	BIPOBJECT::~BIPOBJECT()
	{
		Dtor();
		stl::memzero(this);
	}
}
