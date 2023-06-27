#pragma once

namespace RE
{
	namespace BSResource
	{
		struct FileID
		{
		public:

			//members
			std::uint32_t uiFile;	// 0
			std::uint32_t uiExt;	// 4
		};
		static_assert(sizeof(FileID) == 0x8);

		struct ID : public FileID
		{
		public:

			//members
			std::uint32_t uiDir;	// 8
		};
		static_assert(sizeof(ID) == 0xC);
	}
}
