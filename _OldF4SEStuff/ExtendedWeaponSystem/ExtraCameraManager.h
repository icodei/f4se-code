#pragma once
#include "Global.h"

extern std::unordered_map<const char*, NiCamera*> s_extraCamerasMap;

//UInt32 s_texturePixelSize = 0x110;
//UInt32 s_projectPixelSize = 0x100;

//uses stuff from JiP for reference
class ExtraCameraManager {
public:

	//functions
	static bool AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName = 0);
	static void GenerateExtraCameraTexture(TESObjectCELL* cell, NiCamera* camera, NiTexture* outTexture);
	static bool ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, UInt32 pixelSize = 0x100);

};
STATIC_ASSERT(std::is_empty_v<ExtraCameraManager>);
