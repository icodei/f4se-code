#pragma once

#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSCore/BSTTuple.h"
#include "RE/Bethesda/BSMain/BSPointerHandle.h"
#include "RE/Bethesda/BSTMessageQueue.h"

namespace RE
{
	class BSPackedTask;
	class NiCamera;
	class TESPageCache;
	class BSPortalGraphEntry;
	class SceneGraph;

	struct PositionPlayerEvent;

	class BSPackedTaskQueue
	{
	public:
		// members
		BSTCommonScrapHeapMessageQueue<BSPackedTask> queue;  // 00
		void (*UnpackFunc_t)(const BSPackedTask&);           // 28
	};
	static_assert(sizeof(BSPackedTaskQueue) == 0x30);

	class BSSaveDataSystemUtilityImage
	{
	public:
		// members
		std::uint32_t size;    // 00
		std::uint32_t width;   // 04
		std::uint32_t height;  // 08
		char* buffer;          // 10
	};
	static_assert(sizeof(BSSaveDataSystemUtilityImage) == 0x18);

	class Main :
		public BSTEventSink<PositionPlayerEvent>
	{
	public:
		virtual ~Main();  // 00

		// override
		virtual BSEventNotifyControl ProcessEvent(const PositionPlayerEvent& a_event, BSTEventSource<PositionPlayerEvent>* a_source) override;  // 01

		[[nodiscard]] static Main* GetSingleton()
		{
			REL::Relocation<Main**> singleton{ REL::ID(756304) };
			return *singleton;
		}

		[[nodiscard]] static BSPortalGraphEntry* GetCameraPortalGraphEntry()
		{
			using func_t = decltype(&Main::GetCameraPortalGraphEntry);
			REL::Relocation<func_t> func{ REL::ID(515799) };
			return func();
		}

		[[nodiscard]] static BSMultiBoundRoom* GetCameraRootMultiBound()
		{
			using func_t = decltype(&Main::GetCameraRootMultiBound);
			REL::Relocation<func_t> func{ REL::ID(1220834) };
			return func();
		}

		[[nodiscard]] static SceneGraph* GetWorldSceneGraph()
		{
			using func_t = decltype(&Main::GetWorldSceneGraph);
			REL::Relocation<func_t> func{ REL::ID(1376648), 0x30 };
			return func();
		}

		[[nodiscard]] static NiNode* WeatherRootNode()
		{
			using func_t = decltype(&Main::WeatherRootNode);
			REL::Relocation<func_t> func{ REL::ID(1246373), 0x4 };
			return func();
		}

		[[nodiscard]] static NiCamera* WorldRootCamera()
		{
			using func_t = decltype(&Main::WorldRootCamera);
			REL::Relocation<func_t> func{ REL::ID(384264) };
			return func();
		}

		[[nodiscard]] static NiNode* WorldRootNode()
		{
			using func_t = decltype(&Main::WorldRootNode);
			REL::Relocation<func_t> func{ REL::ID(407532), 0xC };
			return func();
		}

		// members
		BSTArray<BSTTuple<float, BSPointerHandle<Actor>>> sortedVisibleHighActors;  // 08
		std::uint32_t localMapRenderDelay;                                          // 20
		bool quitGame;                                                              // 24
		bool resetGame;                                                             // 25
		bool fullReset;                                                             // 26
		bool gameActive;                                                            // 27
		bool onIdle;                                                                // 28
		bool reloadContent;                                                         // 29
		bool freezeTime;                                                            // 2A
		bool freezeNextFrame;                                                       // 2B
		void* hwnd;                                                                 // 30
		void* instance;                                                             // 38
		std::uint32_t threadID;                                                     // 40
		ScrapHeap packedTaskHeap;                                                   // 48
		BSPackedTaskQueue taskQueue;                                                // D8
		ScrapHeap secondaryPackedTaskHeap;                                          // 108
		BSPackedTaskQueue secondaryTaskQueue;                                       // 198
		TESPageCache* pageCache;                                                    // 1C8
		bool inMenuMode;                                                            // 1D0
		bool inDialog;                                                              // 1D1
		bool renderingMenuBG;                                                       // 1D2
		bool signOutPending;                                                        // 1D3
		BSSaveDataSystemUtilityImage saveDataBackgroundImages[3];                   // 1D8
		BSSaveDataSystemUtilityImage saveDataIconImages[3];                         // 220
	};
	static_assert(sizeof(Main) == 0x268);

	BSTimer& GetAppTimer()
	{
		REL::Relocation<BSTimer*> appTimer{ REL::ID(1013228) };
		return *appTimer;
	}
}
