#pragma once

namespace RE
{
	namespace BSResource
	{
		enum class ErrorCode : std::uint32_t
		{
			kNone = 0,
			kNotExist = 1,
			kInvalidPath = 2,
			kFileError = 3,
			kInvalidType = 4,
			kMemoryError = 5,
			kBusy = 6,
			kInvalidParam = 7,
			kUnsupported = 8
		};

		enum class SeekMode
		{
			kSet = 0,
			kCurrent = 1,
			kEnd = 2
		};

	}
}
