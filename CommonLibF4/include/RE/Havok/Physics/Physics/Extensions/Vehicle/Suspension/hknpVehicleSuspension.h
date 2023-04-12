#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"

namespace RE
{
	class hknpVehicleSuspension : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpVehicleSuspension };
		static constexpr auto VTABLE{ VTABLE::hknpVehicleSuspension };

		struct SuspensionWheelParameters
		{
		public:
			//members
			hkVector4f hardpointChassisSpace;
			hkVector4f directionChassisSpace;
			float length;
		};
		static_assert(sizeof(SuspensionWheelParameters) == 0x30);

		//members
		hkArray<SuspensionWheelParameters> wheelParams;
	};
	static_assert(sizeof(hknpVehicleSuspension) == 0x20);
}
