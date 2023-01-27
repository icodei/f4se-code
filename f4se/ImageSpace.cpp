#include "f4se/ImageSpace.h"


void ImageSpaceShaderParam::ResizeConstantGroup(SInt32 a1, SInt32 a2) {
	CALL_MEMBER_FN(this, ResizeConstantGroup)(a1, a2);
}

void ImageSpaceShaderParam::SetPixelConstant(SInt32 a1, float a2, float a3, float a4, float a5) {
	CALL_MEMBER_FN(this, SetPixelConstant)(a1, a2, a3, a4, a5);
}

RelocPtr <ImageSpaceShaderParam>	BSImagespaceShader_DefaultParam(0x06733340);
RelocPtr <ImageSpaceShaderParam*>	BSImagespaceShader_pCurrentParam(0x06733330);