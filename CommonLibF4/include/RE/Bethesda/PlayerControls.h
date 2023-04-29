#pragma once

#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTSingleton.h"
#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSInputEventUser.h"
#include "RE/Bethesda/BSMain/BSPointerHandle.h"
#include "RE/Bethesda/BSSpring.h"
#include "RE/Bethesda/IMovementInterface.h"
#include "RE/NetImmerse/NiMain/NiPoint2.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"

namespace RE
{
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class QuickContainerStateEvent;
	class UserEventEnabledEvent;

	struct TESFurnitureEvent;

	class __declspec(novtable) ActionInput
	{
	public:
		static constexpr auto RTTI{ RTTI::ActionInput };
		static constexpr auto VTABLE{ VTABLE::ActionInput };

		enum class ACTIONPRIORITY
		{
			kImperative,
			kQueue,
			kTry
		};

		struct Data
		{
		public:
			union
			{
				float f;
				std::int32_t i;
				std::uint32_t ui;
			};  //00
		};

		virtual ~ActionInput();  // 00

		// members
		NiPointer<TESObjectREFR> ref;                              // 08
		NiPointer<TESObjectREFR> targetRef;                        // 10
		BGSAction* action;                                         // 18
		stl::enumeration<ACTIONPRIORITY, std::uint32_t> priority;  // 20
		Data ActionData;                                           // 24
	};
	static_assert(sizeof(ActionInput) == 0x28);

	class ActionOutput
	{
	public:
		static constexpr auto RTTI{ RTTI::ActionOutput };

		//member
		BSFixedString animEvent;
		BSFixedString targetAnimEvent;
		std::uint32_t result;
		TESIdleForm* sequence;
		TESIdleForm* animObjIdle;
		std::uint32_t sequenceIndex;
	};

	class BGSActionData :
		public ActionInput,
		public ActionOutput
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSActionData };
		static constexpr auto VTABLE{ VTABLE::BGSActionData };
	};

	class TESActionData :
		public BGSActionData
	{
	public:
		static constexpr auto RTTI{ RTTI::TESActionData };
		static constexpr auto VTABLE{ VTABLE::TESActionData };
	};

	struct PlayerControlsData
	{
	public:
		// members
		NiPoint2 moveInputVec{ NiPoint2::ZERO };              // 00
		NiPoint2 lookInputVec{ NiPoint2::ZERO };              // 08
		NiPoint2 lookInputVecNormalized{ NiPoint2::ZERO };    // 10
		NiPoint2 prevMoveVec{ NiPoint2::ZERO };               // 18
		NiPoint2 prevLookVec{ NiPoint2::ZERO };               // 20
		BSSpring::SpringState<NiPoint3> rotationSpeedSpring
		{
			rotationSpeedSpring.position = NiPoint3::ZERO,
			rotationSpeedSpring.velocity = NiPoint3::ZERO,
			rotationSpeedSpring.springConstant = 0.0F
		};                                                    // 28
		bool autoMove{ false };                               // 44
		bool running{ false };                                // 45
		bool togglePOV{ false };                              // 46
		bool vanityModeEnabled{ false };                      // 47
		bool checkHeldStates{ false };                        // 48
		bool setupHeldStatesForRelease{ false };              // 49
	};
	static_assert(sizeof(PlayerControlsData) == 0x4C);

	class PlayerInputHandler : public BSInputEventUser
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerInputHandler };
		static constexpr auto VTABLE{ VTABLE::PlayerInputHandler };

		PlayerInputHandler() = delete;
		PlayerInputHandler(PlayerControlsData& a_data) :
			data(a_data) { ctor(a_data); }

		virtual ~PlayerInputHandler() {}  // 00

		// add
		virtual void PerFrameUpdate() { return; };  // 09

		// members
		PlayerControlsData& data;        // 10
		bool inQuickContainer{ false };  // 18

	private:
		PlayerInputHandler* ctor(PlayerControlsData& a_data)
		{
			using func_t = decltype(&PlayerInputHandler::ctor);
			REL::Relocation<func_t> func{ REL::ID(1240396), 0xC0 };
			return func(this, a_data);
		}
	};
	static_assert(sizeof(PlayerInputHandler) == 0x20);

	class HeldStateHandler : public PlayerInputHandler
	{
	public:
		static constexpr auto RTTI{ RTTI::HeldStateHandler };
		static constexpr auto VTABLE{ VTABLE::HeldStateHandler };

		HeldStateHandler() = delete;
		HeldStateHandler(PlayerControlsData& a_data) : PlayerInputHandler(a_data) { ctor(a_data); }

		virtual ~HeldStateHandler() {}  // 00

		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event) { heldStateActive = a_event && (a_event->value != 0.0F || a_event->heldDownSecs < 0.0F); }  // 10
		virtual void SetHeldStateActive(bool a_flag) { heldStateActive = a_flag; }                                                                                 // 11

		// members
		bool heldStateActive{ false };      // 20
		bool triggerReleaseEvent{ false };  // 21

	private:
		HeldStateHandler* ctor(PlayerControlsData& a_data)
		{
			using func_t = decltype(&HeldStateHandler::ctor);
			REL::Relocation<func_t> func{ REL::ID(908502), 0xD0 };
			return func(this, a_data);
		}
	};
	static_assert(sizeof(HeldStateHandler) == 0x28);

	struct ActivateHandler;

	struct AttackBlockHandler : public HeldStateHandler
	{
	public:
		static constexpr auto RTTI{ RTTI::AttackBlockHandler };
		static constexpr auto VTABLE{ VTABLE::AttackBlockHandler };

		AttackBlockHandler() = delete;
		AttackBlockHandler(PlayerControlsData& a_data) :
			HeldStateHandler(a_data) { ctor(a_data); }

		virtual ~AttackBlockHandler(){}  // 00

		//members
		std::uint32_t heldTimeMs;
		std::uint32_t unk1C;
		BSFixedString controlID;
		std::uint8_t attackType;
		std::uint8_t pad29;
		std::uint16_t pad2A;
		std::uint8_t attackCount;
		float initialPowerAttackDelay;
		std::uint32_t pad34;
		float subsequentPowerAttackDelay;
		bool ignore;
		bool unk41;
		bool heldLeft;
		bool heldRight;
		float fAttackQueueThresholdSec;
		std::int64_t gap58;
		float rightAttackHeldSeconds;
		float rightAttackLastHeldSeconds;
		float gap68;
		float field_6C;
		bool field_70;
		char field_71;
		bool leftAttackHeld;
		bool rightAttackHeld;
		bool field_74;
		bool field_75;
		bool field_76;
		bool field_77;
		bool throwingWeapon;

	private:
		AttackBlockHandler* ctor(PlayerControlsData& a_data)
		{
			using func_t = decltype(&AttackBlockHandler::ctor);
			REL::Relocation<func_t> func{ REL::ID(908502) };
			return func(this, a_data);
		}
	};
	static_assert(sizeof(AttackBlockHandler) == 0x80);

	struct AutoMoveHandler;
	struct GrabRotationHandler;
	struct JumpHandler;
	struct LookHandler;
	struct MeleeThrowHandler;
	struct MovementHandler;
	struct ReadyWeaponHandler;
	struct RunHandler;
	struct SneakHandler;
	struct SprintHandler;

	struct TogglePOVHandler;
	struct ToggleRunHandler;

	class __declspec(novtable) PlayerControls :
		BSInputEventReceiver,                    // 000
		BSTEventSink<MenuOpenCloseEvent>,        // 010
		BSTEventSink<MenuModeChangeEvent>,       // 018
		BSTEventSink<TESFurnitureEvent>,         // 020
		BSTEventSink<UserEventEnabledEvent>,     // 028
		IMovementPlayerControls,                 // 030
		BSTEventSink<QuickContainerStateEvent>,  // 038
		BSTSingletonSDM<PlayerControls>          // 040
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerControls };
		static constexpr auto VTABLE{ VTABLE::PlayerControls };

		static PlayerControls* GetSingleton()
		{
			REL::Relocation<PlayerControls**> singleton{ REL::ID(544871) };
			return *singleton;
		}

		bool DoAction(DEFAULT_OBJECT a_action, ActionInput::ACTIONPRIORITY a_priority)
		{
			using func_t = decltype(&PlayerControls::DoAction);
			REL::Relocation<func_t> func{ REL::ID(818081) };
			return func(this, a_action, a_priority);
		}

		void RegisterHandler(PlayerInputHandler* a_handler) { DoRegisterHandler(a_handler, false); }
		void RegisterHandler(HeldStateHandler* a_handler) { DoRegisterHandler(a_handler, true); }

		// members
		PlayerControlsData data;                        // 044
		BSTArray<PlayerInputHandler*> handlers;         // 090
		BSTArray<HeldStateHandler*> heldStateHandlers;  // 0A8
		std::uint32_t topGraphPoint[3];                 // 0C0
		float graphPoints[3][10][2];                    // 0CC
		BSTArray<ActorHandle> actionInterestedActors;   // 1C0
		BSSpinLock actorArraySpinLock;                  // 1D8
		MovementHandler* movementHandler;               // 1E0
		LookHandler* lookHandler;                       // 1E8
		SprintHandler* sprintHandler;                   // 1F0
		ReadyWeaponHandler* readyWeaponHandler;         // 1F8
		AutoMoveHandler* autoMoveHandler;               // 200
		ToggleRunHandler* toggleRunHandler;             // 208
		ActivateHandler* activateHandler;               // 210
		JumpHandler* jumpHandler;                       // 218
		AttackBlockHandler* attackHandler;              // 220
		RunHandler* runHandler;                         // 228
		SneakHandler* sneakHandler;                     // 230
		TogglePOVHandler* togglePOVHandler;             // 238
		MeleeThrowHandler* meleeThrowHandler;           // 240
		GrabRotationHandler* grabRotationHandler;       // 248
		bool notifyingHandlers;                         // 250
		bool blockPlayerInput;                          // 251
		float cameraAutoRotationX;                      // 254
		float cameraAutoRotationY;                      // 258

	private:
		void DoRegisterHandler(PlayerInputHandler* a_handler, bool a_isHeldStateHandler)
		{
			using func_t = decltype(&PlayerControls::DoRegisterHandler);
			REL::Relocation<func_t> func{ REL::ID(177801) };
			return func(this, a_handler, a_isHeldStateHandler);
		}
	};
	static_assert(sizeof(PlayerControls) == 0x260);
}
