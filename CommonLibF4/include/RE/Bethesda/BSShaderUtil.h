#pragma once
#include "RE/Bethesda/BSCulling.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSSceneGraph;
	class NiCamera;
	class NiAVObject;

	namespace BSShaderUtil
	{
		void SetSceneGraphCameraFOV(BSSceneGraph* a_scene, float a_FOV, bool a3, NiCamera* a_camera, bool includeLOD)
		{
			using func_t = decltype(&BSShaderUtil::SetSceneGraphCameraFOV);
			REL::Relocation<func_t> func{ REL::ID(1491349) };
			return func(a_scene, a_FOV, a3, a_camera, includeLOD);
		}

		void SetCameraFOV(NiCamera* a_camera, float a_FOV, float f_far, float f_near)
		{
			using func_t = decltype(&BSShaderUtil::SetCameraFOV);
			REL::Relocation<func_t> func{ REL::ID(1463640) };
			return func(a_camera, a_FOV, f_far, f_near);
		}

		void AccumulateScene(NiCamera* a_camera, NiAVObject* a_object, BSCullingProcess& a_cullingprocess, bool a1)
		{
			using func_t = decltype(&BSShaderUtil::AccumulateScene);
			REL::Relocation<func_t> func{ REL::ID(1551978) };
			return func(a_camera, a_object, a_cullingprocess, a1);
		}

		void AccumulateSceneArray(NiCamera* a_camera, BSTArray<NiPointer<NiAVObject>>* a_objects, BSCullingProcess& a_cullingprocess, bool a1)
		{
			using func_t = decltype(&BSShaderUtil::AccumulateSceneArray);
			REL::Relocation<func_t> func{ REL::ID(899120) };
			return func(a_camera, a_objects, a_cullingprocess, a1);
		}

		void RenderScene(NiCamera* a_camera, BSShaderAccumulator* a_accumulator, bool a1) {
			using func_t = decltype(&BSShaderUtil::RenderScene);
			REL::Relocation<func_t> func{ REL::ID(1310228) };
			return func(a_camera, a_accumulator, a1);
		}
	
	}
}
