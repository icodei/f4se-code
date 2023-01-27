#include "f4se/GameMain.h"

BSPortalGraphEntry* Main::GetCameraPortalGraphEntry() {
	return CALL_MEMBER_FN(this, GetCameraPortalGraphEntry)();
}
RelocPtr<Main*>						appMain(0x05AA4278);
RelocPtr<NiPointer<SceneGraph>>		Main__spWorldSceneGraph(0x05AA4358);
RelocPtr<NiPointer<SceneGraph>>		Main__spMenuRoot(0x05AA4360);
RelocPtr<NiPointer<SceneGraph>>		Main__sp3DMenuRoot(0x05AA4368);