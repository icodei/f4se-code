#include "RE/NetImmerse/NiMain/NiPoint3.h"

namespace RE
{
	const NiPoint3 NiPoint3::ZERO(0.0F);
	const NiPoint3 NiPoint3::UNIT_X(1.0F, 0.0F, 0.0F);
	const NiPoint3 NiPoint3::UNIT_Y(0.0F, 1.0F, 0.0F);
	const NiPoint3 NiPoint3::UNIT_Z(0.0F, 0.0F, 1.0F);
	const NiPoint3 NiPoint3::UNIT_ALL(1.0F);
	const NiPoint3 NiPoint3::INFINITY_POINT3(std::numeric_limits<float>::max());
}
