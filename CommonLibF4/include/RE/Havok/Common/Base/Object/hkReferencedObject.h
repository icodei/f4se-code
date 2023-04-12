#pragma once

#include "RE/Havok/Common/Base/Object/hkBaseObject.h"

namespace RE
{
	class hkClass;

	/// Base for all classes in the Havok SDK.
	/// All core SDK objects that can be owned by multiple owners inherit from this class -
	/// rigid bodies, constraints, and actions are all hkReferencedObjects
	/// and any object that is memory managed by Havok also inherits from it.
	class __declspec(novtable) hkReferencedObject : public hkBaseObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkReferencedObject };
		static constexpr auto VTABLE{ VTABLE::hkReferencedObject };

		hkReferencedObject();
		hkReferencedObject(const hkReferencedObject& originalObject);

		void operator=([[maybe_unused]] const hkReferencedObject& originalObject) {}

		virtual ~hkReferencedObject() {}

		// add
		virtual const hkClass* GetClassType() const { return nullptr; }   // 02
		virtual void DeleteThisReferencedObject() const { delete this; }  // 03

		// members
		hkUint32 memSizeAndRefCount;  // 08
		std::uint32_t pad0C;          // 0C
	};
	static_assert(sizeof(hkReferencedObject) == 0x10);
}
