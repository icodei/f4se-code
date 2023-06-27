#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSMain/BSCullingProcess.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSSceneGraph;
	class NiCamera;
	class NiAVObject;
	class BSGeometryListCullingProcess;

	class BSShaderUtil
	{
	private:
		BSShaderUtil() {}
		~BSShaderUtil() {}

	public:
		static constexpr auto MAX_ARRAY_SIZE{ 0x200 };

		static void SetMaterialAlpha(NiAVObject*, float, bool) {}        //TODO
		static void RecursiveSetPropertyWireframe(NiAVObject*, bool) {}  //TODO
		static void RecursiveClearWorldBoundChange() {}                  //TODO
		static void InitSDM() {}                                         //TODO
		static void KillSDM() {}                                         //TODO

		static void SetShadowFlags(NiAVObject*) {}                                                                         //TODO
		static bool GetMultiBoundVisibleAgainstActiveOccluders(NiPoint3 const&, NiCullingProcess&, BSMultiBound*) {}       //TODO
		static bool GetMultiBoundVisibleAgainstActiveOccluders(NiPoint3 const&, NiCullingProcess&, BSMultiBoundShape*) {}  //TODO
		static NiColorA GetMultiBoundDebugColor(NiCullingProcess&, BSMultiBound*) {}                                       //TODO

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

		static void CullCollectedObjects(BSGeometryListCullingProcess&, BSCullingProcess&) {}  //TODO

		static void RenderScene(NiCamera* a_camera, BSShaderAccumulator* a_accumulator, bool a1)
		{
			using func_t = decltype(&BSShaderUtil::RenderScene);
			REL::Relocation<func_t> func{ REL::ID(1310228) };
			return func(a_camera, a_accumulator, a1);
		}

		static void RenderSceneDeffered(NiCamera*, BSShaderAccumulator*, NiCullingProcess&, ShadowSceneNode*, std::int32_t, std::int32_t, bool, bool) {}  //TODO
		static void RenderScenePreResolveDepth(NiCamera*, BSShaderAccumulator*, bool) {}                                                                  //TODO
		static void RenderScenePostResolveDepth(NiCamera*, BSShaderAccumulator*) {}                                                                       //TODO

		static void EnableBloodDecalGeometry(NiAVObject*, bool) {}        //TODO
		static NiAVObject* FindBloodDecalGeometry(NiAVObject*) {}         //TODO
		static void SetWeaponBloodAmount(NiAVObject*, float) {}           //TODO
		static void SetEditorAlphaTestRef(NiAVObject*, std::uint16_t) {}  //TODO
		static std::int16_t GetEditorAlphaTestRef(NiAVObject*) {}         //TODO

		static void SetTexturesCanDegrade(NiAVObject* a_object, bool a_degrade)
		{
			using func_t = decltype(&BSShaderUtil::SetTexturesCanDegrade);
			REL::Relocation<func_t> func{ REL::ID(1432487) };
			return func(a_object, a_degrade);
		}

		static void GenerateModelSpaceFromWorldSpaceVector(NiPoint3A const&, NiMatrix3 const&, NiPoint3A&) {}                        //TODO
		static DirectX::XMMATRIX GenerateWorldSpaceProjectionFromWorldSpaceVector(NiPoint3 const&, NiTransform const&) {}            //TODO
		static void GenerateWorldSpaceProjectionFromWorldSpaceVector(NiPoint3 const&, NiTransform const&, DirectX::XMFLOAT4X4A&) {}  //TODO
		static bool IsCulled(NiAVObject*) {}                                                                                         //TODO
		static NiNode* GenerateSphere(float, NiColorA, NiColorA, std::int32_t, std::int32_t) {}                                      //TODO
		static BSGeometry* GenerateEllipsoid(NiPoint3 const&) {}                                                                     //TODO
		static BSGeometry* GenerateHemisphere(float, NiColorA) {}                                                                    //TODO
		static BSGeometry* GenerateCone(float, float, float, std::uint16_t, NiColorA, bool) {}                                       //TODO
		static BSGeometry* GenerateBox(float, float, float, NiColorA, bool) {}                                                       //TODO
		static BSGeometry* GenerateUnscaledBox() {}                                                                                  //TODO
		static void MakePlanesForMinMaxBox(NiFrustumPlanes&, NiPoint3, NiPoint3, NiTransform&) {}                                    //TODO
		static void RecursiveSetModelSpaceProjection(NiAVObject*) {}                                                                 //TODO
		static void RecursiveSetProjectedData(NiAVObject*, NiColorA const&, NiColorA const&) {}                                      //TODO
		static void RecursiveSetProjectedUVParams(NiAVObject*, NiColorA const&) {}                                                   //TODO
		static void RecursiveSetProjectedUVColor(NiAVObject*, NiColorA const&) {}                                                    //TODO
		static void InvalidateRenderPasses(NiAVObject*) {}                                                                           //TODO

		static void ClearRenderPasses(NiAVObject* a_object)
		{
			using func_t = decltype(&BSShaderUtil::ClearRenderPasses);
			REL::Relocation<func_t> func{ REL::ID(613616) };
			return func(a_object);
		}

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

		static void GetD3DFromNi(DirectX::XMFLOAT4X4&, NiTransform const&) {}                                         //TODO
		static void GetD3DFromNi(DirectX::XMFLOAT4X4&, NiMatrix3 const&, NiPoint3 const&, float) {}                   //TODO
		static void GetD3DFromNiNoAdjust(DirectX::XMFLOAT4X4&, NiTransform const&) {}                                 //TODO
		static void GetD3DFromNiNoAdjust(DirectX::XMFLOAT4X4&, NiMatrix3 const&, NiPoint3 const&, float) {}           //TODO
		static void GetD3DTransposeFromNi(DirectX::XMFLOAT4X4&, NiTransform const&) {}                                //TODO
		static void GetD3DTransposeFromNi(DirectX::XMFLOAT4X4&, NiMatrix3 const&, NiPoint3 const&, float) {}          //TODO
		static void GetD3DTransposeFromNiNoAdjust(DirectX::XMFLOAT4X4&, NiTransform const&) {}                        //TODO
		static void GetD3DTransposeFromNiNoAdjust(DirectX::XMFLOAT4X4&, NiMatrix3 const&, NiPoint3 const&, float) {}  //TODO
		static void CombineObjects(NiNode*, BSScrapArray<BSTriShape*>&, std::uint32_t, bool, std::uint32_t) {}        //TODO
		static void CombineSortedObjects(NiNode*, BSTriShape**, std::uint32_t, bool) {}                               //TODO
		static void CombineObjectsTint(BSTriShape**, std::uint32_t, bool) {}                                          //TODO
		static void TintGeometry(BSGeometry*, NiColorA const&, bool) {}                                               //TODO
		static void UndoTintGeometry(BSGeometry*) {}                                                                  //TODO
		static void AddNoLightingPropertyRecurse(NiAVObject*) {}                                                      //TODO
		static void PrepareObjectWithNoLightingRecurse(NiAVObject*) {}                                                //TODO

	};
	static_assert(std::is_empty_v<BSShaderUtil>);
}
