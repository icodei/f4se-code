#pragma once
#include "RE/Bethesda/BSCompoundFrustum.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundRoom;
	class BSMultiBoundNode;
	class NiAVObject;
	class NiNode;

	class BSPortalGraph : public NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSPortalGraph };
		static constexpr auto VTABLE{ VTABLE::BSPortalGraph };

		//members
		BSTArray<void*> QOccluderList;  //NiTPointerList<BSOcclusionShape *>
		BSTArray<void*> QPortalList;    //NiTPointerList<BSPortal *>
		BSTArray<NiPointer<BSMultiBoundRoom>> QRooms;
		BSTArray<NiPointer<NiAVObject>> QAlwaysRenderArray;
		NiNode* QPortalNodeRoot;
		BSTArray<void*> unk78;
		BSTArray<void*> unk90;
		BSTArray<NiPointer<NiNode>> QUnboundNodes;
		std::uint32_t QWorldID;
	};

	class BSPortalGraphEntry : public NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSPortalGraphEntry };
		static constexpr auto VTABLE{ VTABLE::BSPortalGraphEntry };

		//members
		BSPortalGraph* QPortalGraph;
		BSTArray<NiPointer<BSMultiBoundRoom>> QRoomAccumList;
		BSMultiBoundRoom* QRoomRoot;
		std::uint8_t gap38[12];
		std::uint32_t field_44;
		std::uint32_t field_48;
		std::uint32_t field_4C;
		std::uint32_t field_50;
		std::uint8_t gap54[12];
		std::uint64_t field_60;
		BSCompoundFrustum QUnboundCompoundFrustum;
		bool QVisibleUnboundSpace;
		std::uint32_t field_13C;
		std::uint16_t field_140;
		std::uint32_t field_144;
		std::uint32_t field_148;
	};
}
