#pragma once

#include "RE/Bethesda/InputEvent.h"
#include "RE/Bethesda/BSCore/MemoryManager.h"

namespace RE
{
	class alignas(0x08) BSInputEventUser
	{
	public:
		static constexpr auto RTTI{ RTTI::BSInputEventUser };
		static constexpr auto VTABLE{ VTABLE::BSInputEventUser };

		virtual ~BSInputEventUser() = default;  // 00

		// add
		virtual bool ShouldHandleEvent(const InputEvent*) { return false; }           // 01
		virtual void HandleKinectEvent(const KinectEvent*) { return; }                // 02
		virtual void HandleDeviceConnectEvent(const DeviceConnectEvent*) { return; }  // 03
		virtual void HandleThumbstickEvent(const ThumbstickEvent*) { return; }        // 04
		virtual void HandleCursorMoveEvent(const CursorMoveEvent*) { return; }        // 05
		virtual void HandleMouseMoveEvent(const MouseMoveEvent*) { return; }          // 06
		virtual void HandleCharacterEvent(const CharacterEvent*) { return; }          // 07
		virtual void HandleButtonEvent(const ButtonEvent*) { return; }                // 08

		F4_HEAP_REDEFINE_NEW(BSInputEventUser);

		// members
		bool inputEventHandlingEnabled{ true };  // 08
	};
	static_assert(sizeof(BSInputEventUser) == 0x10);

	struct __declspec(novtable) DisconnectHandler :
		public BSInputEventUser
	{
	public:
		static constexpr auto RTTI{ RTTI::DisconnectHandler };
		static constexpr auto VTABLE{ VTABLE::DisconnectHandler };
	};
	static_assert(sizeof(DisconnectHandler) == 0x10);
}
