#pragma once

namespace RE
{
	/// Base class for all Havok classes that have virtual functions.
	/// In gcc2 for instance, if the virtual base class has data in it the vtable
	/// is placed after the data, whereas most other compilers always have the vtable
	/// at the start. Thus we have an empty virtual base class to force the vtable
	/// to always be at the start of the derived objects.
	/// All Havok managed objects inherit from a sub class of this, hkReferencedObject
	/// that stores the memory size and the reference count info (if used).
	class __declspec(novtable) hkBaseObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkBaseObject };
		static constexpr auto VTABLE{ VTABLE::hkBaseObject };

		virtual ~hkBaseObject() { return; }  // 00

		// add
		virtual void __first_virtual_table_function__() { return; }  // 01
	};
	static_assert(sizeof(hkBaseObject) == 0x8);
}
