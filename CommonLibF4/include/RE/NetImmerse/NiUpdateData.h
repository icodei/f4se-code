#pragma once

namespace RE
{
	class NiUpdateData
	{
	public:

		struct AutoFadeNodeDepth
		{
		public:
			//members
			NiUpdateData* rData;
		};

		//members
		float fTime;
		std::uint32_t RenderUseDepth;
		NiCamera* pCamera;
		std::uint32_t Flags;			//NiAVObject::UpdateFlags
		std::uint32_t RenderObjects;
		std::uint32_t FadeNodeDepth;
	};
}
