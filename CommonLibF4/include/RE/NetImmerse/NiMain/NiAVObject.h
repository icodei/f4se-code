#pragma once

#include "RE/NetImmerse/NiMain/NiBound.h"
#include "RE/NetImmerse/NiMain/NiFlags.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiTransform.h"
#include "RE/NetImmerse/NiObjectNET.h"

namespace RE
{
	class NiAlphaProperty;
	class NiCollisionObject;
	class NiCullingProcess;
	class NiNode;
	class NiUpdateData;
	class PerformOpFunc;

	class __declspec(novtable) NiAVObject :
		public NiObjectNET  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAVObject };
		static constexpr auto VTABLE{ VTABLE::NiAVObject };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAVObject };

		enum UpdateFlags : std::int32_t
		{
			UPDATE_FLAG_NONE,
			UPDATE_FLAG_PARENT_IS_CULLED,
		};

		enum : std::uint64_t
		{
			NONE = 0,
			APP_CULLED_MASK = 1 << 0,                 //Hidden
			SELECTIVE_UPDATE_MASK = 1 << 1,           //SelectiveUpdate
			SELECTIVE_XFORMS_MASK = 1 << 2,           //SelectiveUpdateTransforms
			SELECTIVE_CONTROLLER_MASK = 1 << 3,       //SelectiveUpdateController
			SELECTIVE_RIGID_MASK = 1 << 4,            //SelectiveUpdateRigid
			DISPLAY_OBJECT_MASK = 1 << 5,             //DisplayObject
			DISABLE_SORTING = 1 << 6,                 //DisableSorting
			SELECTIVE_XFORMS_OVERRIDE_MASK = 1 << 7,  //SelectiveUpdateTransformsOverride
			kUNK = 1 << 8,                            //
			SAVE_EXTERNAL_GEOMDATA = 1 << 9,          //SaveExternalGeometryData
			NO_DECALS = 1 << 10,                      //NoDecals
			ALWAYS_DRAW = 1 << 11,                    //AlwaysDraw
			MESH_LOD = 1 << 12,                       //MeshLOD
			FIXED_BOUND = 1 << 13,                    //FixedBound
			TOP_FADENODE = 1 << 14,                   //TopFadeNode
			IGNORE_FADE = 1 << 15,                    //IgnoreFade
			NO_ANIMSYNC_X = 1 << 16,                  //NoAnimSyncX
			NO_ANIMSYNC_Y = 1 << 17,                  //NoAnimSyncY
			NO_ANIMSYNC_Z = 1 << 18,                  //NoAnimSyncZ
			NO_ANIMSYNC_S = 1 << 19,                  //NoAnimSyncS
			NO_DISMEMBER = 1 << 20,                   //NoDismember
			NO_DISMEMBER_VALIDITY = 1 << 21,          //NoDismemberValidity
			kRenderUse = 1 << 22,                     //RenderUse
			MATERIALS_APPLIED = 1 << 23,              //MaterialsApplied
			SAVE_FLAG_MASK = 16777215,                //
			HIGH_DETAIL = 1 << 24,                    //HighDetail
			FORCE_UPDATE = 1 << 25,                   //ForceUpdate
			PREPROCESSED_NODE = 1 << 26,              //PreProcessedNode
			OBJECT_PREPARED_MASK = 1 << 27,
			MANDATORY_UPDATE = 1 << 28,
			SCENEGRAPH_CHANGE = 1 << 29,
			WORLD_BOUND_CHANGE = 1 << 30,
			MESHLOD_LEVEL_CHANGE = 1 << 31,

			MESHLOD_USE_BOUND_SCALE = 4294967296,         //1 << 32
			NEEDS_LIGHTING_UPDATE = 8589934592,           //1 << 33
			NEEDS_CUSTOM_RENDER = 17179869184,            //1 << 34
			INSTANCED = 34359738368,                      //1 << 35
			LOD_FADING_OUT = 68719476736,                 //1 << 36
			FADED_IN = 137438953472,                      //1 << 37
			FORCE_FADEOUT = 274877906944,                 //1 << 38
			NOT_VISIBLE = 549755813888,                   //1 << 39
			NOT_SHADOW_CASTER = 1099511627776,            //1 << 40
			NEEDS_RENDERER_DATA = 2199023255552,          //1 << 41
			ACCUMULATED = 4398046511104,                  //1 << 42
			ALREADY_TRAVERSED = 8796093022208,            //1 << 43
			PICK_OFF = 17592186044416,                    //1 << 44
			TRANS_IS_IDENTITY = 35184372088832,           //1 << 45
			HAS_PROPERTY_CONTROLLER = 70368744177664,     //1 << 46
			LOCKED_CHILDREN = 140737488355328,            //1 << 47
			NO_OCCLUSION = 281474976710656,               //1 << 48
			HAS_MOVING_SOUND = 562949953421312,           //1 << 49
			FIRST_PERSON_HIRES = 1125899906842624,        //1 << 50
			DEFERRED_ATTACHES = 1125899906842624,         //1 << 50
			FORCE_NO_LIGHTING_UPDATE = 2251799813685248,  //1 << 51
		};

		NiAVObject();
		virtual ~NiAVObject();  // NOLINT(modernize-use-override) 00

		// add
		virtual void UpdateControllers([[maybe_unused]] NiUpdateData& a_data) { return; }                                                                                              // 28
		virtual void PerformOp([[maybe_unused]] PerformOpFunc& a_operation) { return; }                                                                                                // 29
		virtual void AttachProperty([[maybe_unused]] NiAlphaProperty* a_prop) { return; }                                                                                              // 2A
		virtual void SetMaterialNeedsUpdate(bool) { return; }                                                                                                                          // 2B
		virtual void SetDefaultMaterialNeedsUpdateFlag(bool) { return; }                                                                                                               // 2C
		virtual void SetAppCulled([[maybe_unused]] bool a_appCulled) { return; }                                                                                                       // 2D
		virtual NiAVObject* GetObjectByName(const BSFixedString& a_name) { return name == a_name ? this : nullptr; }                                                                   // 2E
		virtual void SetSelectiveUpdateFlags([[maybe_unused]] bool& a_selectiveUpdate, [[maybe_unused]] bool a_selectiveUpdateTransforms, [[maybe_unused]] bool& a_rigid) { return; }  // 2F
		virtual void UpdateDownwardPass([[maybe_unused]] NiUpdateData& a_data, [[maybe_unused]] std::uint32_t a_flags) { return; }                                                     // 30
		virtual void UpdateSelectedDownwardPass([[maybe_unused]] NiUpdateData& a_data, [[maybe_unused]] std::uint32_t a_flags) { return; }                                             // 31
		virtual void UpdateRigidDownwardPass([[maybe_unused]] NiUpdateData& a_data, [[maybe_unused]] std::uint32_t a_flags) { return; }                                                // 32
		virtual void UpdateWorldBound() { return; }                                                                                                                                    // 33
		virtual void UpdateWorldData([[maybe_unused]] NiUpdateData* a_data) { return; }                                                                                                // 34
		virtual void UpdateTransformAndBounds([[maybe_unused]] NiUpdateData& a_data) { return; }                                                                                       // 35
		virtual void UpdateTransforms(NiUpdateData& a_data) { UpdateWorldData(std::addressof(a_data)); }                                                                               // 36
		virtual void PreAttachUpdate([[maybe_unused]] NiNode* a_eventualParent, [[maybe_unused]] NiUpdateData& a_data) { return; }                                                     // 37
		virtual void PostAttachUpdate() { return; }                                                                                                                                    // 38
		virtual void OnVisible([[maybe_unused]] NiCullingProcess& a_culler) { return; }                                                                                                // 39

		F4_HEAP_REDEFINE_ALIGNED_NEW(NiAVObject);

		[[nodiscard]] bool GetAppCulled() const noexcept { return flags.GetBit(APP_CULLED_MASK); }
		[[nodiscard]] std::uint64_t GetFlags() const noexcept { return flags.flags; }
		[[nodiscard]] bool ShadowCaster() const noexcept { return !flags.GetBit(NOT_SHADOW_CASTER); }

		void Update(NiUpdateData& a_data)
		{
			using func_t = decltype(&NiAVObject::Update);
			REL::Relocation<func_t> func{ REL::ID(121052) };
			return func(this, a_data);
		}

		// members
		NiNode* parent{ nullptr };                     // 027
		NiTransform local;                             // 030
		NiTransform world;                             // 070
		NiBound worldBound;                            // 0B0
		NiTransform previousWorld;                     // 0C0
		NiPointer<NiCollisionObject> collisionObject;  // 100
		NiTFlags<std::uint64_t, NiAVObject> flags;     // 108
		std::uintptr_t userData{ 0 };                  // 110
		float fadeAmount{ 1.0F };                      // 118
		std::int8_t multType{ 0 };                     // 11C
		std::int8_t meshLODFadingLevel{ 0 };           // 11D
		std::int8_t currentMeshLODLevel{ 0 };          // 11E
		std::int8_t previousMeshLODLevel{ 0 };         // 11F
	};
	static_assert(sizeof(NiAVObject) == 0x120);
}
