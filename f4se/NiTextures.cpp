#include "f4se/NiTextures.h"

NiTexture* NiTexture::CreateEmpty(BSFixedString& name, bool a2, bool a3) {
	return CALL_MEMBER_FN(this, CreateEmpty)(name, a2, a3);
}

RelocAddr <_CreateTexture> CreateTexture(0x01BA5220);

RelocAddr <_CreateBSShaderTextureSet> CreateBSShaderTextureSet(0x027BD1D0);

RelocAddr <_LoadTextureByPath> LoadTextureByPath(0x027D61F0);