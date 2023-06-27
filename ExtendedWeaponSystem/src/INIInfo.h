#pragma once
#include "Global.h"

#include <SimpleIni.h>

struct INIInfo {
private:
	INIInfo(){};

public:
	INIInfo(INIInfo const&) = delete;
	void operator=(INIInfo const&) = delete;

	//static functions
	static INIInfo& getInstance();
	static void initINIConfigs();
	static void LoadINIConfigs();

	//members
	CSimpleIniA ini;
	std::string path;
};
