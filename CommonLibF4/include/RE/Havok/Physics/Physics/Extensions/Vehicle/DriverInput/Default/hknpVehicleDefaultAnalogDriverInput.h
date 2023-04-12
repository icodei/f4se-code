#pragma once
#include "RE/Havok/Physics/Physics/Extensions/Vehicle/DriverInput/hknpVehicleDriverInput.h"

namespace RE
{
	class hknpVehicleDefaultAnalogDriverInput : public hknpVehicleDriverInput
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleDefaultAnalogDriverInput };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleDefaultAnalogDriverInput };

		//members
		float slopeChangePointX;
		float initialSlope;
		float deadZone;
		bool autoReverse;
	};
	static_assert(sizeof(hknpVehicleDefaultAnalogDriverInput) == 0x20);
}
