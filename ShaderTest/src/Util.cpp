#include "Util.h"
#include "HookUtil.h"

bool IsPlayerInFirstPerson() {
	if (!pcam) {
		return false;
	}
	return pcam->currentState == pcam->cameraStates[CameraState::kFirstPerson];
}

bool IsPlayerInThirdPerson() {
	if (!pcam) {
		return false;
	}
	return pcam->currentState == pcam->cameraStates[CameraState::k3rdPerson];
}

const NiAVObject* GetByNameFromPlayer3D(const BSFixedString& name) {
	BSFadeNode* player3D = pc ? pc->Get3D()->IsFadeNode() : nullptr;
	if (!player3D) {
		return nullptr;
	}
	NiAVObject* obj;
	obj = BSUtilities::GetObjectByName(player3D, name, true, true);
	if (!obj) {
		return nullptr;
	}
	return obj;
}

const NiAVObject* GetByNameFromPlayer3D(const char* name) {
	BSFadeNode* player3D = pc ? pc->Get3D()->IsFadeNode() : nullptr;
	if (!player3D) {
		return nullptr;
	}
	NiAVObject* obj;
	obj = BSUtilities::GetObjectByString(player3D, name, true, true);
	if (!obj) {
		return nullptr;
	}
	return obj;
}

/*;========================================================================================================================================================;*/

TESForm* GetFormFromIdentifier(const string& identifier) {
	auto delimiter = identifier.find('|');
	if (delimiter != string::npos) {
		string modName = identifier.substr(0, delimiter);
		string modForm = identifier.substr(delimiter + 1);

		TESDataHandler* g_dataHandler = TESDataHandler::GetSingleton();

		const TESFile* mod = (g_dataHandler)->LookupModByName(modName.c_str());
		uint8_t modIndex = mod->compileIndex;
		if (mod && modIndex != -1) {
			uint32_t formID = stoul(modForm, nullptr, 16) & 0xFFFFFF;
			uint32_t flags = HookUtil::GetOffset<uint32_t>(mod, 0x334);
			if (flags & (1 << 9)) {
				// ESL
				formID &= 0xFFF;
				formID |= 0xFE << 24;
				formID |= HookUtil::GetOffset<uint32_t>(mod, 0x372) << 12;  // ESL load order
			} else {
				formID |= (modIndex) << 24;
			}
			return TESForm::GetFormByID(formID);
		}
	}
	return nullptr;
}

//Gather the forms we need
bool GetForms() {
	bool toReturn = true;
	return toReturn;
}

char tempbuf[8192] = { 0 };
char* _MESSAGE(const char* fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vsnprintf(tempbuf, sizeof(tempbuf), fmt, args);
	va_end(args);
	spdlog::log(spdlog::level::info, tempbuf);

	return tempbuf;
}

void Dump(void* mem, unsigned int size) {
	char* p = static_cast<char*>(mem);
	unsigned char* up = (unsigned char*)p;
	std::stringstream stream;
	int row = 0;
	for (unsigned int i = 0; i < size; i++) {
		stream << std::setfill('0') << std::setw(2) << std::hex << (int)up[i] << " ";
		if (i % 8 == 7) {
			stream << "\t0x"
				   << std::setw(2) << std::hex << (int)up[i]
				   << std::setw(2) << (int)up[i - 1]
				   << std::setw(2) << (int)up[i - 2]
				   << std::setw(2) << (int)up[i - 3]
				   << std::setw(2) << (int)up[i - 4]
				   << std::setw(2) << (int)up[i - 5]
				   << std::setw(2) << (int)up[i - 6]
				   << std::setw(2) << (int)up[i - 7] << std::setfill('0');
			stream << "\t0x" << std::setw(2) << std::hex << row * 8 << std::setfill('0');
			_MESSAGE("%s", stream.str().c_str());
			stream.str(std::string());
			row++;
		}
	}
}

//Functions to write a simple line of text to logs

//Write info to log
void logInfo(string text) {
	logger::info(FMT_STRING("{:s}"), text);
}

void logWarn(string text) {
	logger::warn(FMT_STRING("{:s}"), text);
}

//Write error to log. Error is unexpected result but not a crash
void logError(string text) {
	logger::error(FMT_STRING("{:s}"), text);
}

//Write critical to log. Critical is something that will crash
void logCritical(string text) {
	logger::critical(FMT_STRING("{:s}"), text);
}
