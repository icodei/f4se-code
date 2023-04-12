#pragma once
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"

namespace RE
{
	class hknpActionManager;
	class hknpWorld;
	struct hknpBodyId;

	class __declspec(align(8)) hknpAction : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpAction };
		static constexpr auto VTABLE{ VTABLE::hknpAction };

		enum Result
		{
			RESULT_OK,
			RESULT_REMOVE
		};

		virtual ~hknpAction();

		//add
		virtual void getBodies(hknpBodyId*&, int&);
		virtual void removeBody(hknpBodyId);
		virtual Result applyAction(hknpWorld*, float);
		virtual void onActionAdded(hknpActionManager*);
		virtual void onActionRemoved(hknpActionManager*);
		virtual void onWorldShifted(hkVector4f&);

		//members
		unsigned long userData;
	};
	static_assert(sizeof(hknpAction) == 0x18);

	class hknpUnaryAction : public hknpAction
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpUnaryAction };
		static constexpr auto VTABLE{ VTABLE::hknpUnaryAction };

		//members
		std::uint32_t bodyId;
	};
	static_assert(sizeof(hknpUnaryAction) == 0x20);
}
