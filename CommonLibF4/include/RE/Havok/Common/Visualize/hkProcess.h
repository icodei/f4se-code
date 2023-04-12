#pragma once
//#include "RE/Havok/Common/Visualize/Serialize/hkDisplaySerializeOStream.h"

namespace RE
{
	class hkDisplaySerializeIStream;
	class hkDebugDisplayHandler;
	class hkProcessHandler;

	class __declspec(novtable) hkProcess
	{
		enum ProcessType
		{
			HK_PROCESS_TYPE_UNKNOWN = -1,
			HK_PROCESS_TYPE_BEHAVIOR = 1,
		};

		hkProcess(hkBool selectable) :
			m_selectable(selectable) {}

		virtual ~hkProcess() {}

		virtual int getProcessTag() = 0;
		virtual ProcessType getType() const { return HK_PROCESS_TYPE_UNKNOWN; }
		virtual void getConsumableCommands(hkUint8*& commands, int& numCommands) { commands = HK_NULL; numCommands = 0; }
		virtual void consumeCommand([[maybe_unused]] hkUint8 command) {}
		virtual bool isOk() { return false; }

		//members
		hkBool m_selectable;
		hkDisplaySerializeIStream* m_inStream;
		hkDisplaySerializeOStream* m_outStream;
		hkDebugDisplayHandler* m_displayHandler;
		hkProcessHandler* m_processHandler;
	};
}
