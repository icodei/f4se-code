#include "INIInfo.h"
#include "Util.h"

INIInfo& INIInfo::getInstance() {
	static INIInfo instance;
	return instance;
}

void INIInfo::initINIConfigs() {
	INIInfo& INI = INIInfo::getInstance();
	INI.path = "Data\\MCM\\Config\\EWS\\settings.ini";
	if (std::filesystem::exists("Data\\MCM\\Settings\\EWS.ini")) {
		INI.path = "Data\\MCM\\Settings\\EWS.ini";
	}
	logger::info(FMT_STRING("Loading config from {}"), INI.path.c_str());
	
}

void INIInfo::LoadINIConfigs() {
	INIInfo& INI = INIInfo::getInstance();
	SI_Error result = INI.ini.LoadFile(INI.path.c_str());
	if (result >= 0) {
		hotKey = std::stof(INI.ini.GetValue("Reloading", "SpeedReloadHotKey", "0x11"));
	} else {
		logError("Failed to load config.");
	}
}
