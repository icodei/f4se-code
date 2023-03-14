#pragma once

#include <xmmintrin.h>

#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiTransform.h"
#include "RE/Netimmerse/NiMain/NiObject.h"

namespace RE
{
	class NiNode;
	class NiAVObject;

	class BSSkin
	{
	public:
		// 28
		class BoneData : public NiObject
		{
		public:
			struct BoneTransforms
			{
				NiPoint3 boundingSphere;  // 00
				float radius;             // 0C
				NiTransform transform;    // 10
			};

			BSTArray<BoneTransforms> transforms;  // 10
			void* unk20;                          // 20
		};

		// C0
		class Instance : public NiObject
		{
		public:
			BSTArray<NiNode*> bones;                 // 10
			BSTArray<NiTransform*> worldTransforms;  // 28 - These are pointers to the corresponding bone's worldTransforms
			BoneData* boneData;                      // 40
			NiAVObject* rootNode;                    // 48
			void* unk50;                             // 50
			std::uint64_t unk58;                     // 58
			__m128 unk60;                            // 60
			__m128 unk70;                            // 64
			__m128 unk80;                            // 68
			__m128 unk90;                            // 90
			void* unkA0;                             // A0
			void* unkA8;                             // A8
			std::uint64_t unkB0;                     // B0
			std::uint32_t unkB8;                     // B8
			std::int32_t unkBC;                      // BC
		};
	};
}
