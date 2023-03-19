#include "RE/Bethesda/BSShader/ImageSpaceManager.h"

namespace RE
{
	REL::Relocation<ImageSpaceManager**> ImageSpaceManager__pInstance{ REL::ID(161743) };
	REL::Relocation<int*> ImageSpaceManager__iActiveEffectsCount{ REL::ID(1524657) };
	REL::Relocation<ImageSpaceBaseData*> ImageSpaceManager__kInitBaseData{ REL::ID(380891) };
	REL::Relocation<BSReadWriteLock*> ImageSpaceManager__kBaseDataLock{ REL::ID(1212084) };
	REL::Relocation<ImageSpaceManager::ImageSpaceEffectEnum*> ImageSpaceManager__iLastEffect{ REL::ID(646887) };
	REL::Relocation<int*> ImageSpaceManager__iSwapTarget{ REL::ID(1547604) };
	REL::Relocation<int*> ImageSpaceManager__iSaveTarget{ REL::ID(865881) };
}
