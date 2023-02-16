#include "f4se/ImageSpaceManager.h"

ImageSpaceEffect* ImageSpaceManager::GetEffect(ImageSpaceEffectEnum a_enum) {
	return CALL_MEMBER_FN(this, GetEffect)(a_enum);
}

void ImageSpaceManager::RenderEffect_1(ImageSpaceEffectEnum a_enum, SInt32 a2, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_1)(a_enum, a2, a_param);
}

void ImageSpaceManager::RenderEffect_2(ImageSpaceEffect* a_effect, SInt32 a2, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_2)(a_effect, a2, a3, a_param);
}

void ImageSpaceManager::RenderEffect_3(ImageSpaceEffect* a_effect, SInt32 a2, SInt32 a3, SInt32 a4, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_3)(a_effect, a2, a3, a4, a_param);
}

void ImageSpaceManager::RenderEffectHelper_2(ImageSpaceEffectEnum a_enum, SInt32 a2, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffectHelper_2)(a_enum, a2, a3, a_param);
}

void ImageSpaceManager::RenderEffect_Tex_1(ImageSpaceEffect* a_effect, NiTexture* a_tex, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_Tex_1)(a_effect, a_tex, a3, a_param);
}

void ImageSpaceManager::RenderEffect_Tex_2(ImageSpaceEffectEnum a_enum, NiTexture* a_tex, NiTexture* a_tex2, SInt32 a4, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_Tex_2)(a_enum, a_tex, a_tex2, a4, a_param);
}

void ImageSpaceManager::RenderEffectHelper_Tex_1(ImageSpaceEffectEnum a_enum, NiTexture* a_tex, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffectHelper_Tex_1)(a_enum, a_tex, a3, a_param);
}

NiPointer<BSTriShape>& ImageSpaceManager::SelectScreenShape(ImageSpaceEffect* a_effect) {
	return CALL_MEMBER_FN(this, SelectScreenShape)(a_effect);
}

RelocPtr <ImageSpaceManager*>	ImageSpaceManager_pInstance(0x067220E8);