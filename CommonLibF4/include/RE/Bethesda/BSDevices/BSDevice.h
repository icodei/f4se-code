#pragma once

namespace RE
{
	class BSDevice
	{
		//add
		virtual void Init();
		virtual void CheckConnection([[maybe_unused]] void* a_device);

		//members
		bool bConnected;
		std::uint32_t uiVendorId;
		std::uint32_t uiProductId;
	};
}
