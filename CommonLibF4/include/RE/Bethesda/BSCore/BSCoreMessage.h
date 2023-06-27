#pragma once

namespace RE
{
	namespace BSCoreMessage
	{
		enum MessageEventType : std::int32_t
		{
			MET_ASSERT = 0x0,
			MET_WARNING = 0x1,
			MET_PROGFLOW = 0x2,
			MET_INITFLOW = 0x3,
			MET_DEBUGSTRING = 0x4,
			MET_CRASHTRACE = 0x5,
			MET_USER1 = 0x6,
			MET_USER2 = 0x7,
			MET_ERROR = 0x8,
			MET_CMD = 0x9,
			MET_COUNT = 0xA,
		};

		struct Event
		{
			union ParamType
			{
				std::uint64_t ui;
				const void* p;
			};

			const MessageEventType eType;
			const char* pMessage;
			ParamType ParamA[3];
		};
	}
	
}
