#pragma once
#include "RE/Bethesda/BSCore/BSTSingleton.h"

namespace RE
{
	class BSTextureDB
	{
	public:

		class DBTraits
		{
		public:
			enum
			{
				ReleaseQueueDepth = 0x40,
				ArgsPoolSize = 0x400,
			};
			class ArgsType
			{
				unsigned int uiLoadLevel;
				bool bIsCubeMap;
				bool bReplicateCubeMap;
				bool bIsDDX;
				bool bIsSRGB;
				bool AllowDegrade;
			};
		};
		struct TextureIDs : BSTSingletonImplicit<TextureIDs>
		{
			const BSResource::ID DDSID;
			const BSResource::ID DDXID;
			const BSResource::ID BTXID;
			const BSResource::ID EmptyID;
		};
	};
}
