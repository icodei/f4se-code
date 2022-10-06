#include "Global.h"


RelocAddr<uintptr_t> PlayerAnimGraphEvent_ReceiveEvent_Target(0x2D442D8 + 0x8);
_PlayerAnimGraphEvent_ReceiveEvent PlayerAnimationEvent_Original;


EventResult PlayerAnimGraphEvent_ReceiveEvent_Hook(void* arg1, BSAnimationGraphEvent* evn, void* dispatcher) {
	
	if (eventLogEnabled) {
		std::string sName = (evn->name).c_str();
		std::string sArgs = (evn->args).c_str();
		std::string sOut = "Error";
		
		if (evn->args.QLength() > 0) {
			sOut = sName + "." + sArgs;
			
		}
		else {
			sOut = sName;
		}
		log("Player Anim Event: " + sOut);
	}

	return PlayerAnimationEvent_Original(arg1, evn, dispatcher);
}

bool Install() { //Called at GameLoaded
	bool toReturn = true;
	log("Hooks Install");

	PlayerAnimationEvent_Original = *(_PlayerAnimGraphEvent_ReceiveEvent*)(PlayerAnimGraphEvent_ReceiveEvent_Target.GetUIntPtr());
	SafeWrite64(PlayerAnimGraphEvent_ReceiveEvent_Target, (uintptr_t)PlayerAnimGraphEvent_ReceiveEvent_Hook);

	return toReturn;
}
