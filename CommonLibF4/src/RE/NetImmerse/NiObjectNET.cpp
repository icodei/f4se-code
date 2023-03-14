#include "RE/NetImmerse/NiObjectNET.h"
#include "RE/NetImmerse/NiMain/NiTimeController.h"

namespace RE
{
	NiObjectNET::NiObjectNET() { stl::emplace_vtable(this); }

	NiObjectNET::~NiObjectNET() {}  // NOLINT(modernize-use-equals-default)
}
