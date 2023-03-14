#pragma once
#include "RE/NetImmerse/NiMain/NiRefObject.h"

#include <DirectXMath.h>

namespace RE
{
	class NiLight;

	class BSLight : public NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLight };
		static constexpr auto VTABLE{ VTABLE::BSLight };

		virtual ~BSLight();

		//add
		virtual void SetLight(NiLight* aLight);
		virtual bool GetIsShadowLight();
		virtual void GetProjection(std::uint32_t, DirectX::XMFLOAT4X4A& outValue);

		//members
		std::byte gap[(0x190 - 0x10)];
	};
	static_assert(sizeof(BSLight) == 0x190);
}
