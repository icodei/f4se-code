#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"

namespace RE
{
	class hknpVehicleDriverInput : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleDriverInput };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleDriverInput };

	};
	static_assert(sizeof(hknpVehicleDriverInput) == 0x10);

	class hknpVehicleDriverInputStatus : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleDriverInputStatus };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleDriverInputStatus };

	};
	static_assert(sizeof(hknpVehicleDriverInputStatus) == 0x10);

	class __declspec(align(16)) hknpVehicleDriverInputAnalogStatus : public hknpVehicleDriverInputStatus
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleDriverInputAnalogStatus };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleDriverInputAnalogStatus };

		//members
		float positionX;
		float positionY;
		bool handbrakeButtonPressed;
		bool reverseButtonPressed;
	};
	static_assert(sizeof(hknpVehicleDriverInputAnalogStatus) == 0x20);
}
