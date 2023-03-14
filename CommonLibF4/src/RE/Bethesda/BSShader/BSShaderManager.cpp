#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	REL::Relocation<BSShaderManager::SHADERERRORFUNC**> BSShaderManager__pShaderErrorCallback{ REL::ID(197682) };               //146721A60
	REL::Relocation<BSShaderManager::GARBAGECOLLECTORADDFUNC**> BSShaderManager__pGarbageCollectorCallback{ REL::ID(416649) };  //146721A68
	REL::Relocation<float**> BSShaderManager__actorVegetationCollisionsS{ REL::ID(636411) };                                    //146721A70	//[4][4]
	REL::Relocation<BSShaderAccumulator**> BSShaderManager__pCurrentShaderAccumulator{ REL::ID(809145) };                       //146721AB0
	REL::Relocation<BSShaderManager::etRenderMode*> BSShaderManager__usRenderMode{ REL::ID(1028217) };                          //146721AB8
	REL::Relocation<bool*> BSShaderManager__bInitialized{ REL::ID(346773) };                                                    //146721ABC
	REL::Relocation<bool*> BSShaderManager__bImageSpaceEffects{ REL::ID(572286) };                                              //146721ABD
	REL::Relocation<bool*> BSShaderManager__bTransparencyMultisampling{ REL::ID(572286), 0x1 };                                 //146721ABE
	REL::Relocation<bool*> BSShaderManager__bAnisoMinFiltering{ REL::ID(572286), 0x2 };                                         //146721ABF
	REL::Relocation<BSShaderManager::FPTIMERFUNC**> BSShaderManager__pTimerFunction{ REL::ID(1247963) };                        //146721AC0
	REL::Relocation<std::uint16_t*> BSShaderManager__usRenderFlags{ REL::ID(1247963), 0x8 };                                    //146721AC8
																																//...
	REL::Relocation<std::uint32_t*> BSShaderManager__uiStencilRenderTarget{ REL::ID(1247963), 0x10 };                           //146721AD0
	REL::Relocation<float*> BSShaderManager__fWindAngle{ REL::ID(1004883) };                                                    //146721AD4
	REL::Relocation<float*> BSShaderManager__fWindMinSpeed{ REL::ID(323518) };                                                  //146721AD8
	REL::Relocation<BSShaderManager::etShadowMode*> BSShaderManager__eShadowMode{ REL::ID(323518), 0x4 };                       //146721ADC
	REL::Relocation<NiCamera**> BSShaderManager__spCamera{ REL::ID(543218) };                                                   //146721AE0
																																//...
	REL::Relocation<float**> BSShaderManager__CloudParameters{ REL::ID(981533), 0x8 };                                          //146721AF8	//[4]
																																//...
	REL::Relocation<BSShaderManager*> BSShaderManager__Instance{ REL::ID(16321) };                                              //146721B39
	REL::Relocation<BSPerformanceTimer*> TimerImageSpace{ REL::ID(16321), 0x1 };                                                //146721B3A
	REL::Relocation<BSTArray<NiPointer<BSInstanceGroup>>*> BSShaderManager__InstanceGroups{ REL::ID(10442) };                   //146721B40
	REL::Relocation<BSTArray<BSShaderTextureSet*>*> BSShaderManager__DismembermentTextureArray{ REL::ID(669336) };              //146721B58
	REL::Relocation<BSShaderManager::State*> BSShaderManager__State{ REL::ID(1327069) };                                        //146721B70
	REL::Relocation<NiPointer<BSShader>**> BSShaderManager__pspShader{ REL::ID(487858) };                                       //146721F60	//[12]
	REL::Relocation<NiPointer<NiCamera>*> BSShaderManager__spMainCamera{ REL::ID(175576) };                                     //146721FC8
	REL::Relocation<DirectX::XMMATRIX*> BSShaderManager__xmPipBoyWorldView{ REL::ID(394640) };                                  //146721FD0
	REL::Relocation<NiColor*> BSShaderManager__kBackgroundColor{ REL::ID(567603) };                                             //146722010
	REL::Relocation<NiColorA*> BSShaderManager__fpInterfaceTint{ REL::ID(1006044) };                                            //146722020
	REL::Relocation<NiColor**> BSShaderManager__DirectionalAmbientColorsA{ REL::ID(1444949) };                                  //146722030	//[2][3]
	REL::Relocation<NiColor**> BSShaderManager__LocalDirectionalAmbientColorsA{ REL::ID(474137) };                              //146722080	//[2][3]
	REL::Relocation<NiColorA*> BSShaderManager__pHairTint{ REL::ID(647156), 0x8 };                                              //1467220C8
	REL::Relocation<bool*> BSShaderManager__binstancing{ REL::ID(1304977) };                                                    //1467220D8
}
