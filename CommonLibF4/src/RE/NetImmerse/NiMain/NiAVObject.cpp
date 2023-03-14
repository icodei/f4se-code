#include "RE/NetImmerse/NiMain/NiAVObject.h"
#include "RE/NetImmerse/NiMain/NiCollisionObject.h"

namespace RE
{
	NiAVObject::NiAVObject()
	{
		stl::emplace_vtable(this);
		local.MakeIdentity();
		world.MakeIdentity();
		previousWorld.MakeIdentity();
		flags.flags = 0xE;
	}

	NiAVObject::~NiAVObject() {}  // NOLINT(modernize-use-equals-default)
}
