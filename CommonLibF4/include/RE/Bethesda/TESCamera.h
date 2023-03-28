#pragma once

#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTPoint.h"
#include "RE/Bethesda/BSCore/BSTPoint2.h"
#include "RE/Bethesda/BSCore/BSTPoint3.h"
#include "RE/Bethesda/BSCore/BSTSingleton.h"
#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSMain/BSPointerHandle.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/Havok/Common/Base/Types/Physics/hkRefPtr.h"
#include "RE/NetImmerse/NiMain/NiPoint2.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiQuaternion.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class UserEventEnabledEvent;
	class TESCameraState;
	class TESCamera;
	class OtherEventEnabledEvent;
	class NiNode;
	class NiAVObject;
	class hknpShape;
	class hknpBSWorld;
	class BGSSaveFormBuffer;
	class BGSLoadFormBuffer;
	struct IdleInputEvent;

	struct CameraStates
	{
		enum CameraState : unsigned
		{
			kFirstPerson,
			kAutoVanity,
			kVATS,
			kFree,
			kIronSights,
			kPCTransition,
			kTween,
			kAnimated,
			k3rdPerson,
			kFurniture,
			kMount,
			kBleedout,
			kDialogue,

			kTotal
		};
	};
	using CameraState = CameraStates::CameraState;

	class TESCameraState :
		public BSInputEventUser,      // 00
		public BSIntrusiveRefCounted  // 10

	{
	public:
		static constexpr auto RTTI{ RTTI::TESCameraState };
		static constexpr auto VTABLE{ VTABLE::TESCameraState };

		TESCameraState() = delete;
		TESCameraState(TESCamera& cam, std::uint32_t ID) { ctor(cam, ID); }

		virtual ~TESCameraState() {}  // 00

		// add
		virtual void Begin() { return; }                                                                // 09
		virtual void End() { return; }                                                                  // 0A
		virtual void Update([[maybe_unused]] BSTSmartPointer<TESCameraState>& a_nextState) { return; }  // 0B
		virtual void GetRotation([[maybe_unused]] NiQuaternion& a_rotation) const { return; }           // 0C
		virtual void GetTranslation([[maybe_unused]] NiPoint3& a_translation) const { return; }         // 0D
		virtual void SaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) { return; }         // 0E
		virtual void LoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }         // 0F
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }           // 10

		// members
		TESCamera* camera;  // 18
		std::uint32_t id;   // 20

		F4_HEAP_REDEFINE_NEW(TESCameraState);

	private:
		TESCameraState* ctor(TESCamera& cam, std::uint32_t ID)
		{
			using func_t = decltype(&TESCameraState::ctor);
			REL::Relocation<func_t> func{ REL::ID(1277606), 0x3 };
			return func(this, cam, ID);
		}
	};
	static_assert(offsetof(TESCameraState, camera) == 0x18);
	static_assert(offsetof(TESCameraState, id) == 0x20);
	static_assert(sizeof(TESCameraState) == 0x28);

	class __declspec(novtable) TESCamera
	{
	public:
		static constexpr auto RTTI{ RTTI::TESCamera };
		static constexpr auto VTABLE{ VTABLE::TESCamera };

		TESCamera() { ctor(); }

		virtual ~TESCamera() {}  // 00

		// add
		virtual void SetCameraRoot(NiNode* a_cameraRoot) { cameraRoot = a_cameraRoot; }  // 01
		virtual void SetEnabled(bool a_enabled) { enabled = a_enabled; }                 // 02
		virtual void Update() { return; }                                                // 03

		// members
		BSTPoint2<float> rotationInput;                // 08
		BSTPoint3<float> translationInput;             // 10
		float zoomInput;                               // 1C
		NiPointer<NiNode> cameraRoot;                  // 20
		BSTSmartPointer<TESCameraState> currentState;  // 28
		bool enabled;                                  // 30

		F4_HEAP_REDEFINE_NEW(TESCamera);

	private:
		TESCamera* ctor() {
			using func_t = decltype(&TESCamera::ctor);
			REL::Relocation<func_t> func{ REL::ID(807071) };
			return func(this);
		}
	};
	static_assert(sizeof(TESCamera) == 0x38);

	class __declspec(novtable) ThirdPersonState :
		public TESCameraState  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::ThirdPersonState };
		static constexpr auto VTABLE{ VTABLE::ThirdPersonState };
		static constexpr auto STATE{ CameraStates::k3rdPerson };

		// add
		virtual void ProcessWeaponDrawnChange(bool a_drawn);                           // 11
		virtual bool GetFreeRotationMode() const;                                      // 12
		virtual void SetFreeRotationMode(bool a_cameraEnable, bool a_modifyRotation);  // 13
		virtual void UpdateRotation();                                                 // 14
		virtual void HandleLookInput(const NiPoint2& a_input);                         // 15

		// members
		NiQuaternion rotation;               // 028
		NiQuaternion animationRotation;      // 038
		NiPoint3 translation;                // 048
		NiPoint3 preCollisionTranslation;    // 054
		NiPoint3 targetShoulderOffset;       // 060
		NiPoint3 currentShoulderOffset;      // 06C
		NiPoint3 animationTranslation;       // 078
		NiPoint3 lastTranslation;            // 084
		NiPoint3 rootOffset;                 // 090
		NiPoint3 sideOffsetCollisionBlend;   // 09C
		NiPoint3 nearestHit;                 // 0A8
		NiPoint3 nearestHitDir;              // 0B4
		NiPoint2 freeRotation;               // 0C0
		BSFixedString animatedBoneName;      // 0C8
		NiAVObject* thirdPersonCameraObj;    // 0D0
		NiNode* thirdPersonFOVControl;       // 0D8
		NiPointer<NiAVObject> animatedBone;  // 0E0
		float targetZoomOffset;              // 0E8
		float currentZoomOffset;             // 0EC
		float targetYaw;                     // 0F0
		float currentYaw;                    // 0F4
		float cameraHeightAdjust;            // 0F8
		float savedZoomOffset;               // 0FC
		float pitchZoomOffset;               // 100
		float zoomChange;                    // 104
		NiPoint2 startTogglePOVFreeRot;      // 108
		float collisionRecoveryFactor;       // 110
		float savedCollisionPercent;         // 114
		float animationBlend;                // 118
		float animationBlendDirection;       // 11C
		float searchDistanceBlend;           // 120
		float searchLastCameraYaw;           // 124
		bool freeRotationEnabled;            // 128
		bool zoomingInto1st;                 // 129
		bool show3rdPersonModel;             // 12A
		bool preserveRotation;               // 12B
		bool animatorMode;                   // 12C
		bool applyOffsets;                   // 12D
		bool togglePOVPressRegistered;       // 12E
		bool wasUsingScreenSpaceLastFrame;   // 12F
		bool ironSights;                     // 130
	};
	static_assert(sizeof(ThirdPersonState) == 0x138);

	class __declspec(novtable) PlayerCamera :
		public TESCamera,                             // 000
		public BSInputEventReceiver,                  // 038
		public BSTEventSink<IdleInputEvent>,          // 048
		public BSTEventSink<UserEventEnabledEvent>,   // 050
		public BSTEventSink<OtherEventEnabledEvent>,  // 058
		public BSTSingletonSDM<PlayerCamera>          // 060
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerCamera };
		static constexpr auto VTABLE{ VTABLE::PlayerCamera };

		[[nodiscard]] static PlayerCamera* GetSingleton()
		{
			REL::Relocation<PlayerCamera**> singleton{ REL::ID(1171980) };
			return *singleton;
		}

		[[nodiscard]] BSTSmartPointer<TESCameraState> GetState(CameraState a_state) const
		{
			return cameraStates[a_state];
		}

		template <class T>
		[[nodiscard]] BSTSmartPointer<T> GetState() const  //
			requires(std::derived_from<T, TESCameraState>)
		{
			return BSTSmartPointer{ static_cast<T*>(cameraStates[T::STATE].get()) };
		}

		// members
		ActorHandle cameraTarget;                                                               // 064
		BSTSmallArray<BSTSmartPointer<TESCameraState>, CameraStates::kTotal> tempReturnStates;  // 068
		BSTSmartPointer<TESCameraState> cameraStates[CameraStates::kTotal];                     // 0E0
		hknpBodyId cameraBodyID;                                                                // 148
		hkRefPtr<hknpShape> cameraShape;                                                        // 150
		hkRefPtr<hknpBSWorld> physicsWorld;                                                     // 158
		ActorHandle savedCollidedActor;                                                         // 160
		ObjectRefHandle collisionIgnoredReference;                                              // 164
		float worldFOV;                                                                         // 168
		float firstPersonFOV;                                                                   // 16C
		float fovAdjustCurrent;                                                                 // 170
		float fovAdjustTarget;                                                                  // 174
		float fovAdjustPerSec;                                                                  // 178
		float fovAnimatorAdjust;                                                                // 17C
		float collisionDistPercent;                                                             // 180
		float curPlayerVisible;                                                                 // 184
		NiPoint3 bufferedCameraPos;                                                             // 188
		float heading;                                                                          // 194
		float timeInPitchZero;                                                                  // 198
		float originalPitchToZero;                                                              // 19C
		std::uint32_t furnitureCollisionGroup;                                                  // 1A0
		bool allowAutoVanityMode;                                                               // 1A4
		bool bowZoomedIn;                                                                       // 1A5
		bool freeRotationReady;                                                                 // 1A6
		bool cameraPosBuffered;                                                                 // 1A7
		bool zeroOutPitch;                                                                      // 1A8
		bool adjustFOV;                                                                         // 1A9
		bool trailerCameraMode;                                                                 // 1AA
		bool pipboyMode;                                                                        // 1AB
		bool savedFadeOutCloseActors;                                                           // 1AC
	};
	static_assert(sizeof(PlayerCamera) == 0x1B0);
}
