#pragma once
#include "RE/Havok/Common/Base/Container/String/hkStringPtr.h"

namespace RE
{
	/// All payloads of hkbEvents derive from this class.
	class hkbEventPayload : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbEventPayload };

	protected:
		hkbEventPayload() {}
	};

	/// An event payload that contains an hkReal.
	class hkbRealEventPayload : public hkbEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbRealEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbRealEventPayload };

		hkbRealEventPayload() :
			m_data(0.0f) {}

	public:
		/// An hkReal that is the payload data.
		hkReal m_data;  //+hk.Description("The hkReal contents of the payload.")
	};

	/// An event payload that contains an integer.
	class hkbIntEventPayload : public hkbEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbIntEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbIntEventPayload };

		hkbIntEventPayload() :
			m_data(0) {}

	public:
		/// An hkInt32 that is the payload data.
		hkInt32 m_data;  //+hk.Description("The integer contents of the payload.")
	};

	/// An event payload that contains a string.
	class hkbStringEventPayload : public hkbEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbStringEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbStringEventPayload };

		hkbStringEventPayload() {}

	public:
		/// The string contents of the payload (unmanaged memory).
		hkStringPtr m_data;  //+hk.Description("The string contents of the payload.")
	};

	/// An event payload that has a name.
	class hkbNamedEventPayload : public hkbEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbNamedEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbNamedEventPayload };

		hkbNamedEventPayload() {}

	public:
		/// The name of the payload (unmanaged memory).
		hkStringPtr m_name;  //+hk.Description("The name of the payload.")
	};

	/// An event payload that has a name and an hkReal.
	class hkbNamedRealEventPayload : public hkbNamedEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbNamedRealEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbNamedRealEventPayload };

		hkbNamedRealEventPayload() :
			m_data(0.0f) {}

	public:
		/// An hkReal that is the payload data.
		hkReal m_data;  //+hk.Description("The hkReal contents of the payload.")
	};

	/// An event payload that has a name and an integer.
	class hkbNamedIntEventPayload : public hkbNamedEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbNamedIntEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbNamedIntEventPayload };

		hkbNamedIntEventPayload() :
			m_data(0) {}

	public:
		/// An hkInt32 that is the payload data.
		hkInt32 m_data;  //+hk.Description("The integer contents of the payload.")
	};

	/// An event payload that has a name and a string.
	class hkbNamedStringEventPayload : public hkbNamedEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbNamedStringEventPayload };
		static constexpr auto VTABLE{ VTABLE::hkbNamedStringEventPayload };

		hkbNamedStringEventPayload() {}

	public:
		/// The string contents of the payload (unmanaged memory).
		hkStringPtr m_data;  //+hk.Description("The string contents of the payload.")
	};

	/// An event payload that contains a list of event payloads.
	class hkbEventPayloadList : public hkbEventPayload
	{
	public:
		static constexpr auto RTTI{ RTTI::hkbEventPayloadList };
		static constexpr auto VTABLE{ VTABLE::hkbEventPayloadList };

		hkbEventPayloadList() {}

		~hkbEventPayloadList();

	public:
		/// The nested payloads (reference counted).
		hkArray<hkbEventPayload*> m_payloads;  //+hk.Description("The nested payloads.")
	};
}
