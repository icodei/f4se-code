#pragma once

#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/Havok/Common/Base/Math/Vector/hkVector4.h"
#include "RE/Havok/Physics/Physics/Extensions/CharacterControl/StateMachine/hknpCharacterState.h"

namespace RE
{
	class hknpCharacterStateManager;

	/// The character context holds the current state of the state machine and is the interface that handles all state machine requests.
	class __declspec(novtable) hknpCharacterContext : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterContext };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterContext };

		virtual ~hknpCharacterContext();

		enum class CharacterType
		{
			HK_CHARACTER_PROXY = 0x0,
			HK_CHARACTER_RIGIDBODY = 0x1,
		};

		// members
		CharacterType characterType;                               // 10
		hknpCharacterStateManager* stateManager;                   // 18
		hknpCharacterState::hknpCharacterStateType currentState;   // 20
		hknpCharacterState::hknpCharacterStateType previousState;  // 24
		hkBool filterEnable;                                       // 28
		float maxLinearAcceleration;                               // 2C
		float maxLinearSpeed;                                      // 30
		float gain;                                                // 34
		hkVector4f previousSurfaceVelocity;                        // 40
		std::int32_t numUpdatesInCurrentState;                     // 50
	};
	static_assert(sizeof(hknpCharacterContext) == 0x60);
}
