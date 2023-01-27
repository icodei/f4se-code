#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/BSPortalGraph.h"
#include "f4se/NiTypes.h"

class BSMultiBoundRoom;
class SceneGraph;

class Main {
public:

	MEMBER_FN_PREFIX(Main);
	DEFINE_MEMBER_FN(GetCameraPortalGraphEntry, BSPortalGraphEntry*, 0x00D3CA50);

	BSPortalGraphEntry* GetCameraPortalGraphEntry();
};
extern RelocPtr<Main*>					appMain;
extern RelocPtr<NiPointer<SceneGraph>>	Main__spWorldSceneGraph;
extern RelocPtr<NiPointer<SceneGraph>>	Main__spMenuRoot;
extern RelocPtr<NiPointer<SceneGraph>>	Main__sp3DMenuRoot;

