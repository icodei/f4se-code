#pragma once
#include "RE/Bethesda/BSMain/BSCullingProcess.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSSceneGraph;
	class NiCamera;
	class NiAVObject;

	class BSShaderUtil
	{
	private:
		BSShaderUtil();
		~BSShaderUtil();
	public:
		static void SetMaterialAlpha();	//TODO
		static void RecursiveSetPropertyWireframe();	//TODO
		static void RecursiveClearWorldBoundChange();	//TODO
		static void InitSDM();	//TODO
		static void KillSDM();	//TODO

		static void AccumulateScene(NiCamera* a_camera, NiAVObject* a_object, BSCullingProcess& a_cullingprocess, bool a1)
		{
			using func_t = decltype(&BSShaderUtil::AccumulateScene);
			REL::Relocation<func_t> func{ REL::ID(1551978) };
			return func(a_camera, a_object, a_cullingprocess, a1);
		}

		static void AccumulateSceneArray(NiCamera* a_camera, BSTArray<NiPointer<NiAVObject>>* a_objects, BSCullingProcess& a_cullingprocess, bool a1)
		{
			using func_t = decltype(&BSShaderUtil::AccumulateSceneArray);
			REL::Relocation<func_t> func{ REL::ID(899120) };
			return func(a_camera, a_objects, a_cullingprocess, a1);
		}

		static void RenderScene(NiCamera* a_camera, BSShaderAccumulator* a_accumulator, bool a1)
		{
			using func_t = decltype(&BSShaderUtil::RenderScene);
			REL::Relocation<func_t> func{ REL::ID(1310228) };
			return func(a_camera, a_accumulator, a1);
		}

		static void RenderSceneDeffered();	//TODO
		static void RenderScenePreResolveDepth();	//TODO
		static void RenderScenePostResolveDepth();	//TODO

		static void SetSceneGraphCameraFOV(BSSceneGraph* a_scene, float a_FOV, bool a3, NiCamera* a_camera, bool includeLOD)
		{
			using func_t = decltype(&BSShaderUtil::SetSceneGraphCameraFOV);
			REL::Relocation<func_t> func{ REL::ID(1491349) };
			return func(a_scene, a_FOV, a3, a_camera, includeLOD);
		}

		static void SetCameraFOV(NiCamera* a_camera, float a_FOV, float f_far, float f_near)
		{
			using func_t = decltype(&BSShaderUtil::SetCameraFOV);
			REL::Relocation<func_t> func{ REL::ID(1463640) };
			return func(a_camera, a_FOV, f_far, f_near);
		}
	};
	static_assert(std::is_empty_v<BSShaderUtil>);
}
