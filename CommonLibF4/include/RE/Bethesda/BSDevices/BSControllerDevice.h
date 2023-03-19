#pragma once
#include "RE/Bethesda/BSDevices/BSInterfaceDevice.h"

namespace RE
{
	class BSControllerDevice : public BSInterfaceDevice
	{
	public:
		//members
		std::uint32_t uiUserPort;
	};
}
