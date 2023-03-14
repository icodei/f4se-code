#pragma once
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSCullingGroup;
	class BSCullingProcess;
	class BSGeometry;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiCamera;

	class DrawWorld
	{
	public:
		using Additional1stPersonFunc_t = void (*)(BSTArray<NiPointer<NiAVObject>>&);
		using CompanionLocalMapRenderFn_t = void (*)(void);
		using Interface3DRenderFn_t = void (*)(std::uint32_t);
		using LensFlareRenderFn_t = void (*)(NiCamera&);
		using OcclusionMapRenderFn_t = void (*)(void);
		using VATSEffectRenderFunc_t = void (*)(NiCamera*);
	};

	//...
	//NOTES - DrawWorld::Begin asaigns this SSN with BSShaderManager::State.pShadowSceneNode[0]
	REL::Relocation<ShadowSceneNode*> DrawWorld__pShadowSceneNode{ REL::ID(879298) };	//1467231B0 
	//...
	REL::Relocation<NiAVObject*> DrawWorld__p1stPerson{ REL::ID(1491228) };  //146723200
	REL::Relocation<NiAVObject*> DrawWorld__pInterior{ REL::ID(127974) };    //146723208
	//...
	REL::Relocation<NiAVObject*> DrawWorld__pScreenSplatterRoot{ REL::ID(1225102) };   //146723230
	REL::Relocation<NiCamera*> DrawWorld__pCamera{ REL::ID(1444212) };                 //146723238
	REL::Relocation<NiCamera*> DrawWorld__pVisCamera{ REL::ID(81406) };                //146723240
	REL::Relocation<NiCamera*> DrawWorld__pScreenSplatterCamera{ REL::ID(300623) };    //146723248
	REL::Relocation<BSCullingProcess*> DrawWorld__pCullingProcess{ REL::ID(520184) };  //146723250
	//...
	REL::Relocation<DrawWorld::VATSEffectRenderFunc_t*> DrawWorld__VATSEffectRenderFunc{ REL::ID(693228) };  //146723290
	REL::Relocation<DrawWorld::Interface3DRenderFn_t*> DrawWorld__Interface3DRenderFn{ REL::ID(912279) };    //146723298
	//...
	REL::Relocation<DrawWorld::CompanionLocalMapRenderFn_t*> DrawWorld__CompanionLocalMapRenderFn{ REL::ID(1350784) };  //1467232A8
	REL::Relocation<DrawWorld::Additional1stPersonFunc_t*> DrawWorld__Additional1stPersonFunc{ REL::ID(1570634) };      //1467232B0
	REL::Relocation<DrawWorld::LensFlareRenderFn_t*> DrawWorld__LensFlareRenderFn{ REL::ID(207644) };                   //1467232B8
	REL::Relocation<DrawWorld::OcclusionMapRenderFn_t*> DrawWorld__OcclusionMapRenderFn{ REL::ID(426737) };             //1467232C0
	//...
	REL::Relocation<NiPointer<BSGeometry>> DrawWorld__spUnitBox{ REL::ID(161040) };        //1467232F0
	REL::Relocation<NiPointer<NiCamera>> DrawWorld__sp1stPersonCamera{ REL::ID(380177) };  //1467232F8
	//...
	REL::Relocation<NiPointer<BSShaderAccumulator>> DrawWorld__spDrawPersonAccum{ REL::ID(1211381) };     //146723350
	REL::Relocation<NiPointer<BSShaderAccumulator>> DrawWorld__spDraw1stPersonAccum{ REL::ID(1430301) };  //146723358
	//...
	REL::Relocation<BSCullingGroup> DrawWorld__k1stPersonCullingGroup{ REL::ID(731482) };  //1467236A0
	//...
	REL::Relocation<BSTArray<NiPointer<NiAVObject>>> DrawWorld__Additional1stPersonGeom{ REL::ID(736815) };  //1467239C8
}
