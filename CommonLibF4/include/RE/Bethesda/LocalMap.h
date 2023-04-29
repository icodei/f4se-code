#pragma once
#include "RE/Bethesda/BSMain/BSCullingProcess.h"
#include "RE/Bethesda/BSShader/ImageSpaceShaderParam.h"
#include "RE/Bethesda/PipboyManager.h"
#include "RE/Bethesda/TESCamera.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSShaderAccumulator;
	class NiAVObject;

	namespace LocalMapCameraUpdate
	{
		struct Event
		{
		public:
		};
	};

	namespace LocalMapPostRendered
	{
		struct Event
		{
		public:
			NiPoint3 unk00;  //00
			NiPoint3 unk0C;  //0C
			NiPoint3 unk18;  //18
		};
	}

	namespace LocalMapRendered
	{
		struct Event
		{
		public:
		};
	}

	class LocalMapSnapshotCommand : public PipboyCommand
	{
	public:
		static constexpr auto RTTI{ RTTI::LocalMapSnapshotCommand };
		static constexpr auto VTABLE{ VTABLE::LocalMapSnapshotCommand };
	};

	class LocalMapCamera : public TESCamera
	{
	public:
		static constexpr auto RTTI{ RTTI::LocalMapCamera };
		static constexpr auto VTABLE{ VTABLE::LocalMapCamera };

		class DefaultState : public TESCameraState
		{
		public:
			static constexpr auto RTTI{ RTTI::LocalMapCamera__DefaultState };
			static constexpr auto VTABLE{ VTABLE::LocalMapCamera__DefaultState };

			//members
			NiPoint3 initialPosition;
			NiPoint3 translation;
			float zoom;
			float minFrustumHalfWidth;
			float minFrustumHalfHeight;
			std::uint32_t pad44;
		};

		//members
		NiPoint3 maxExtent;
		NiPoint3 minExtent;
		BSTSmartPointer<LocalMapCamera::DefaultState> defaultState;
		NiPointer<NiCamera> camera;
		float zRotation;
		std::uint32_t pad64;
	};

	class LocalMapRenderer
	{
	public:
		//members
		BSCullingProcess pCullingProcess;
		LocalMapCamera MapCamera;
		NiPointer<BSShaderAccumulator> spAccumulator;
		ImageSpaceShaderParam params;
		int renderTarget;
		int renderMode;
		NiAVObject* fogOfWarOverlay;
	};
	static_assert(sizeof(LocalMapRenderer) == 0x2B0);
}
