#pragma once

#include "f4se_common/Relocation.h"
#include "f4se/GameEvents.h"
#include "f4se/GameInput.h"
#include "f4se/NiTypes.h"

class NiNode;
class TESCamera;
class TESCameraState;
class BGSSaveFormBuffer;

// 24
class TESCameraState : public BSIntrusiveRefCounted, public BSInputEventUser {
public:
	TESCameraState() { CALL_MEMBER_FN(this, ctor)(*camera, stateID); };
	TESCameraState(TESCamera& cam, UInt32 ID) { CALL_MEMBER_FN(this, ctor)(cam, ID); };
	//~TESCameraState() { CALL_MEMBER_FN(this, dtor)(); };

	virtual ~TESCameraState() {  };
	
	//add
	virtual void Begin() {  };
	virtual void End() {  };
	virtual void Update(TESCameraState* arg) {  };
	virtual void GetRotation(NiQuaternion* out) {  };
	virtual void GetPosition(NiPoint3* out) {  };
	virtual void SaveGame(BGSSaveFormBuffer* save) {  };
	virtual void LoadGame(BGSSaveFormBuffer* save) {  };
	virtual void Revert(BGSSaveFormBuffer* save) {  };

	TESCamera	*camera;	// 18
	UInt32		stateID;	// 20
	UInt32		pad24;		// 24

	MEMBER_FN_PREFIX(TESCameraState);
	DEFINE_MEMBER_FN(ctor, void, 0x001DF5B0, TESCamera&, UInt32);
	DEFINE_MEMBER_FN(dtor, void, 0x001DF7E0);
};
STATIC_ASSERT(sizeof(TESCameraState) == 0x28);

// 138
class ThirdPersonState : public TESCameraState {
public:
	virtual ~ThirdPersonState();

	virtual void UpdateMode(bool weaponDrawn);
	virtual bool Unk_12();
	virtual void Unk_13();
	virtual void Unk_14();
	virtual void Unk_15();
};

// 38
class TESCamera {
public:
	TESCamera() { CALL_MEMBER_FN(this, ctor)(); };
	//~TESCamera() { CALL_MEMBER_FN(this, dtor)(); };
	virtual ~TESCamera() { CALL_MEMBER_FN(this, dtor)(); };

	virtual void SetCameraNode(NiNode* node) {  };
	virtual void SetEnabled(bool enabled) {  }; // Sets 0x30
	virtual void Update() {  };

	//members
	BSTPoint2<float>	rotationInput;		// 08
	BSTPoint3<float>	translationInput;	// 10
	float				zoomInput;			// 1C
	NiNode				* cameraNode;		// 20
	TESCameraState		* cameraState;		// 28
	bool				enabled;			// 30
	UInt8				unk31;				// 31
	UInt16				unk32;				// 32
	UInt32				unk34;				// 34

	MEMBER_FN_PREFIX(TESCamera);
	DEFINE_MEMBER_FN(ctor, void, 0x0082E640);
	DEFINE_MEMBER_FN(dtor, void, 0x0082E6B0);
	DEFINE_MEMBER_FN(AddRotationInput, void, 0x0082E710, float, float);
	DEFINE_MEMBER_FN(AddTranslationInput, void, 0x0082E730, float, float, float);
	DEFINE_MEMBER_FN(AddZoomInput, void, 0x0082E760, float);
	DEFINE_MEMBER_FN(GetCameraRoot, bool, 0x0082E7C0, NiPointer<NiNode>&);
	DEFINE_MEMBER_FN(SetCameraEnabled, void, 0x0082E810, bool);
	DEFINE_MEMBER_FN(SetCameraRoot, void, 0x0082E780, NiNode*);
	DEFINE_MEMBER_FN(SetCameraState, void, 0x0082E930, TESCameraState* cameraState);

	void AddRotationInput(float a1, float a2);
	void AddTranslationInput(float x, float y, float z);
	void AddZoomInput(float zoom);
	bool GetCameraRoot(NiPointer<NiNode>& out);
	void SetCameraEnabled(bool enabled);
	void SetCameraRoot(NiNode* newRoot);
	void SetCameraState(TESCameraState* cameraState);
};

class PlayerCamera : public TESCamera
{
public:
	virtual ~PlayerCamera();

	enum
	{
		kCameraState_FirstPerson = 0,
		kCameraState_AutoVanity,
		kCameraState_VATS,
		kCameraState_Free,
		kCameraState_IronSights,
		kCameraState_Transition,
		kCameraState_TweenMenu,
		kCameraState_ThirdPerson1,
		kCameraState_ThirdPerson2,
		kCameraState_Furniture,
		kCameraState_Horse,
		kCameraState_Bleedout,
		kCameraState_Dialogue,
		kNumCameraStates
	};

	BSInputEventReceiver				inputEventReceiver;				// 38
	BSTEventSink<void>					idleInputSink;					// 48
	BSTEventSink<UserEventEnabledEvent>	userEventEnabledSink;			// 50
	BSTEventSink<void>					otherEventEnabledSink;			// 58

	UInt32	unk60;	// 60
	UInt32	unk64;	// 64 - Handle
	UInt32	unk68;	// 68
	UInt32	unk6C;	// 6C

	UInt64	unk70[(0xE0 - 0x70) >> 3];

	TESCameraState * cameraStates[kNumCameraStates];	// E0
	UInt64			unk148;								// 148
	UInt64			unk150;								// 150 - hknpSphereShape
	UInt64			unk158;								// 158 - hknpBSWorld
	UInt32			unk160;								// 160
	UInt32			unk164;								// 164 - Handle
	float			fDefaultWorldFov;					// 168 - fDefaultWorldFOV:Display
	float			fDefault1stPersonFOV;				// 16C - fDefault1stPersonFOV:Display
	UInt64			unk170;								// 170
	UInt64			unk178;								// 178
	float			unk180;								// 180
	float			unk184;								// 184
	float			unk188;								// 188
	float			unk18C;								// 18C
	float			unk190;								// 190
	float			unk194;								// 194
	float			unk198;								// 198
	float			unk19C;								// 19C
	SInt32			unk1A0;								// 1A0
	UInt8			unk1A4;								// 1A4
	UInt8			unk1A5;								// 1A5
	UInt8			unk1A6;								// 1A6
	UInt8			unk1A7;								// 1A7
	UInt8			unk1A8;								// 1A8
	UInt8			unk1A9;								// 1A9

	SInt32 GetCameraStateId(TESCameraState * state);
};
STATIC_ASSERT(offsetof(PlayerCamera, cameraStates) == 0xE0);
STATIC_ASSERT(offsetof(PlayerCamera, unk148) == 0x148);

extern RelocPtr <PlayerCamera *> g_playerCamera;
