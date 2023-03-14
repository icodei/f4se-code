#pragma once
#include "Global.h"

//uses stuff from JiP for reference
class ExtraCameraManager {
public:

	//functions
	static bool AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName = 0);
	static void GenerateExtraCameraTexture(TESObjectCELL* cell, NiCamera* camera, NiTexture* outTexture);
	static bool ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, std::uint32_t pixelSize = 0x100);

	static unordered_map<const char*, NiCamera*> s_extraCamerasMap;

};
static_assert(is_empty_v<ExtraCameraManager>);
