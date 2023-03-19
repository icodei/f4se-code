#pragma once
#include "RE/Bethesda/BSCompoundFrustum.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiTList.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundRoom;
	class BSMultiBoundNode;
	class NiAVObject;
	class NiNode;
	class BSOcclusionShape;
	class BSPortal;

	class BSPortalGraph : public NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSPortalGraph };
		static constexpr auto VTABLE{ VTABLE::BSPortalGraph };

		//members
		NiTPointerList<BSOcclusionShape*> OccluderList;
		NiTPointerList<BSPortal*> PortalList;
		BSTArray<NiPointer<BSMultiBoundRoom>> Rooms;
		BSTArray<NiPointer<NiAVObject>> AlwaysRenderArray;
		NiNode* PortalNodeRoot;
		BSTArray<void*> unk78;
		BSTArray<void*> unk90;
		BSTArray<NiPointer<NiNode>> UnboundNodes;
		std::uint32_t WorldID;
	};

	class BSPortalGraphEntry : public NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSPortalGraphEntry };
		static constexpr auto VTABLE{ VTABLE::BSPortalGraphEntry };

		//members
		BSPortalGraph* PortalGraph;
		BSTArray<NiPointer<BSMultiBoundRoom>> RoomAccumList;
		BSMultiBoundRoom* RoomRoot;
		std::uint8_t gap38[12];
		std::uint32_t field_44;
		std::uint32_t field_48;
		std::uint32_t field_4C;
		std::uint32_t field_50;
		std::uint8_t gap54[12];
		std::uint64_t field_60;
		BSCompoundFrustum UnboundCompoundFrustum;
		bool VisibleUnboundSpace;
		std::uint32_t field_13C;
		std::uint16_t field_140;
		std::uint32_t field_144;
		std::uint32_t field_148;
	};
}
