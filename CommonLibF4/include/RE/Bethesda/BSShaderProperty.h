#pragma once

#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSShaderMaterial.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPlane.h"
#include "RE/NetImmerse/NiShadeProperty.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTexture.h"

namespace RE
{
	class BSEffectShaderData;
	class BSFadeNode;
	class BSLight;
	class BSParticleShaderCubeEmitter;
	class BSRenderPass;
	class BSShaderAccumulator;

	struct __declspec(novtable) BSShaderProperty :
		public NiShadeProperty  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSShaderProperty };

		enum EShaderPropertyFlag
		{
			BSSP_SPECULAR = 0x0,
			BSSP_SKINNED = 0x1,
			BSSP_FLAG_TEMP_REFRACTION = 0x2,
			BSSP_VERTEX_ALPHA = 0x3,
			BSSP_GRAYSCALE_TO_PALETTE_COLOR = 0x4,
			BSSP_GRAYSCALE_TO_PALETTE_ALPHA = 0x5,
			BSSP_FALLOFF = 0x6,
			BSSP_ENVMAP = 0x7,
			BSSP_FLAG_RGB_FALLOFF = 0x8,
			BSSP_FLAG_CAST_SHADOWS = 0x9,
			BSSP_FLAG_FACE = 0xA,
			BSSP_FLAG_UI_MASK_RECTS = 0xB,
			BSSP_FLAG_MODELSPACENORMALS = 0xC,
			BSSP_FLAG_REFRACTION_CLAMP = 0xD,
			BSSP_FLAG_MULTI_TEXTURE_LANDSCAPE = 0xE,
			BSSP_FLAG_REFRACTION = 0xF,
			BSSP_FLAG_REFRACTION_FALLOFF = 0x10,
			BSSP_FLAG_EYEREFLECT = 0x11,
			BSSP_FLAG_HAIRTINT = 0x12,
			BSSP_FLAG_SCREENDOOR_ALPHA_FADE = 0x13,
			BSSP_FLAG_LOCALMAP_CLEAR = 0x14,
			BSSP_FLAG_SKIN_TINT = 0x15,
			BSSP_FLAG_OWN_EMIT = 0x16,
			BSSP_FLAG_PROJECTED_UV = 0x17,
			BSSP_FLAG_MULTIPLE_TEXTURES = 0x18,
			BSSP_FLAG_TESSELLATE = 0x19,
			BSSP_FLAG_DECAL = 0x1A,
			BSSP_FLAG_DYNAMIC_DECAL = 0x1B,
			BSSP_FLAG_CHARACTER_LIGHT = 0x1C,
			BSSP_FLAG_EXTERNAL_EMITTANCE = 0x1D,
			BSSP_FLAG_SOFT_EFFECT = 0x1E,
			BSSP_FLAG_ZBUFFER_TEST = 0x1F,
			BSSP_FLAG_ZBUFFER_WRITE = 0x20,
			BSSP_FLAG_LOD_LANDSCAPE = 0x21,
			BSSP_FLAG_LOD_OBJECTS = 0x22,
			BSSP_FLAG_NOFADE = 0x23,
			BSSP_FLAG_TWO_SIDED = 0x24,
			BSSP_FLAG_VERTEXCOLORS = 0x25,
			BSSP_FLAG_GLOWMAP = 0x26,
			BSSP_FLAG_TRANSFORM_CHANGED = 0x27,
			BSSP_FLAG_DISMEMBERMENT_MEATCUFF = 0x28,
			BSSP_FLAG_TINT = 0x29,
			TGSP_FLAG_VERTEX_LIGHTING = 0x2A,
			TGSP_FLAG_UNIFORM_SCALE = 0x2B,
			TGSP_FLAG_FIT_SLOPE = 0x2C,
			TGSP_FLAG_BILLBOARD = 0x2D,
			BSSP_FLAG_LOD_LAND_BLEND = 0x2E,
			BSSP_FLAG_DISMEMBERMENT = 0x2F,
			BSSP_FLAG_WIREFRAME = 0x30,
			BSSP_FLAG_WEAPON_BLOOD = 0x31,
			BSSP_FLAG_HIDE_ON_LOCAL_MAP = 0x32,
			BSSP_FLAG_PREMULT_ALPHA = 0x33,
			BSSP_FLAG_VATS_TARGET = 0x34,
			BSSP_FLAG_ANISOTROPIC_LIGHTING = 0x35,
			BSSP_FLAG_SKEW_SPECULAR_ALPHA = 0x36,
			BSSP_FLAG_MENU_SCREEN = 0x37,
			BSSP_FLAG_MULTI_LAYER_PARALLAX = 0x38,
			BSSP_FLAG_ALPHA_TEST = 0x39,
			BSSP_FLAG_INVERTED_FADE_PATTERN = 0x3A,
			BSSP_FLAG_VATS_TARGET_DRAW_ALL = 0x3B,
			BSSP_FLAG_PIPBOY_SCREEN = 0x3C,
			BSSP_FLAG_TREE_ANIM = 0x3D,
			BSSP_FLAG_EFFECT_LIGHTING = 0x3E,
			BSSP_FLAG_REFRACTION_WRITES_DEPTH = 0x3F,
			BSSP_FLAG_COUNT = 0x40,
		};

		enum PROPERTY_DIFFERENCES
		{
			PD_FLAGS = 0x38,
			PD_END = 0x39,
		};

		enum class TextureTypeEnum
		{
			TEXTYPE_DIFFUSE = 0x0,
			TEXTYPE_BASE = 0x0,
			TEXTYPE_NORMAL = 0x1,
			TEXTYPE_GLOSS = 0x1,
			TEXTYPE_GLOW = 0x2,
			TEXTYPE_HAIR_LAYER = 0x2,
			TEXTYPE_HEIGHT = 0x3,
			TEXTYPE_LOOKUP = 0x3,
			TEXTYPE_ENV = 0x4,
			TEXTYPE_WRINKLES = 0x5,
			TEXTYPE_MULTILAYER = 0x6,
			TEXTYPE_SMOOTHSPEC = 0x7,
			TEXTYPE_DISPLACEMENT = 0x8,
			TEXTYPE_NOISE = 0x9,
			TEXTYPE_COUNT = 0xA,
		};

		enum etAccumulationHint
		{
			BSSP_HINT_NORMAL = 0x0,
			BSSP_HINT_SORT = 0x1,
			BSSP_HINT_GROUP_OPAQUE_DECAL = 0x2,
			BSSP_HINT_GROUP_BLENDED_DECAL = 0x3,
			BSSP_HINT_GROUP_DEBUG_DECAL = 0x4,
			BSSP_HINT_GROUP_REFRACT = 0x5,
			BSSP_HINT_GROUP_1STPERSONNOREFRACT = 0x6,
			BSSP_HINT_GROUP_LODLAND = 0x7,
			BSSP_HINT_GROUP_LODOBJECTS = 0x8,
			BSSP_HINT_GROUP_FADING = 0x9,
			BSSP_HINT_SCREENDOOR_ALPHA = 0xA,
			BSSP_HINT_GROUP_LOW_ANISO = 0xB,
			BSSP_HINT_GROUP_MULTI_INDEX = 0xC,
			BSSP_HINT_GROUP_UNDERWATER_FOG = 0xD,
			BSSP_HINT_GROUP_SSLR = 0xE,
			BSSP_HINT_GROUP_SSLR_WATER_DISPLACEMENT = 0xF,
			BSSP_HINT_GROUP_ZONLY = 0x10,
			BSSP_HINT_GROUP_NO_SHADOW = 0x11,
			BSSP_HINT_GROUP_POSTZONLY = 0x12,
			BSSP_HINT_GROUP_SKYCLOUDS = 0x13,
			BSSP_HINT_GROUP_SKYCLOUDS_OBJECT = 0x14,
			BSSP_HINT_SUBINDEX_DISABLE = 0x15,
			BSSP_HINT_GROUP_SMOOTHALPHATEST = 0x16,
			BSSP_HINT_GROUP_SUNGLARE = 0x17,
			BSSP_HINT_BLOOD_SPLATTER = 0x18,
			BSSP_HINT_Z_PRE_PASS = 0x19,
			BSSP_HINT_ALPHA_TEST_Z_PRE_PASS = 0x1A,
			BSSP_HINT_GROUP_WATER_STENCIL_DISPLACEMENT = 0x1B,
			BSSP_HINT_GROUP_WATER_STENCIL = 0x1C,
			BSSP_HINT_GROUP_WATER_DEPTH = 0x1D,
		};

		class ForEachVisitor;

		class RenderPassArray
		{
		public:
			constexpr RenderPassArray() noexcept {}  // NOLINT(modernize-use-equals-default)

			// members
			BSRenderPass* passList{ nullptr };  // 0
		};
		static_assert(sizeof(RenderPassArray) == 0x8);

		// add
		virtual RenderPassArray* GetRenderPasses(BSGeometry* a_geom, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) = 0;  // 2B
		virtual RenderPassArray* GetRenderPasses_ShadowMapOrMask(BSGeometry*, std::uint32_t, BSShaderAccumulator*) { return nullptr; }     // 2C
		virtual RenderPassArray* GetRenderPasses_LocalMap(BSGeometry*, std::uint32_t, BSShaderAccumulator*) { return nullptr; }            // 2D
		virtual BSRenderPass* CreateVatsMaskRenderPass(BSGeometry*) { return nullptr; }                                                    // 2E
		virtual std::uint16_t GetNumberofPasses([[maybe_unused]] BSGeometry* a_geom) { return 1; }                                         // 2F
		virtual BSRenderPass* GetRenderDepthPass(BSGeometry*) { return nullptr; }                                                          // 30
		virtual bool CanMerge(const BSShaderProperty* a_prop);                                                                             // 31
		virtual void SetMaterialAlpha(float) { return; }                                                                                   // 32
		virtual float QMaterialAlpha() const { return 1.0F; }                                                                              // 33
		virtual const BSFixedString& GetRootName() const;                                                                                  // 34
		virtual std::int32_t ForEachTexture(ForEachVisitor&) { return 1; }                                                                 // 35
		virtual std::int32_t QShader() const { return 0; }                                                                                 // 36
		virtual void ClearUnusedMaterialValues() { return; }                                                                               // 37
		virtual BSShaderProperty* ClarifyShader(BSGeometry*, bool, bool) { return nullptr; }                                               // 38
		virtual NiTexture* GetBaseTexture() const { return nullptr; }                                                                      // 39
		virtual RenderPassArray* GetWaterFogPassList(BSGeometry*) { return nullptr; }                                                      // 3A
		virtual bool AcceptsEffectData() const { return false; }                                                                           // 3B
		virtual void PrecacheTextures() { return; }                                                                                        // 3C
		virtual std::uint32_t DetermineUtilityShaderDecl() const { return 0; }                                                             // 3D
		virtual std::uint32_t GetMaterialType() const { return 0; }                                                                        // 3E
		virtual void DoClearRenderPasses() { return; }                                                                                     // 3F

		// members
		float alpha;                                   // 28
		std::int32_t lastRenderPassState;              // 2C
		std::uint64_t flags;                           // 30
		RenderPassArray renderPassList;                // 38
		RenderPassArray debugRenderPassList;           // 40
		BSFadeNode* fadeNode;                          // 48
		BSEffectShaderData* effectData;                // 50
		BSShaderMaterial* material;                    // 58
		std::uint32_t lastAccumTime;                   // 60
		float lodFade;                                 // 64
		BSNonReentrantSpinLock clearRenderPassesLock;  // 68
	};
	static_assert(sizeof(BSShaderProperty) == 0x70);

	class BSShaderPropertyLightData
	{
	public:
		// members
		std::uint32_t lightListFence;    // 00
		std::uint32_t shadowAccumFlags;  // 04
		std::uint32_t lightListChanged;  // 08
		BSTArray<BSLight*> lightList;    // 10
	};
	static_assert(sizeof(BSShaderPropertyLightData) == 0x28);

	class BSEffectShaderProperty : public BSShaderProperty
	{
	public:
		static constexpr auto RTTI{ RTTI::BSEffectShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSEffectShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSEffectShaderProperty };

		NiTexture* GetBaseTexture()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetBaseTexture);
			REL::Relocation<func_t> func{ REL::ID(1334794) };
			return func(this);
		}

		BSEffectShaderMaterial* GetEffectShaderMaterial()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetEffectShaderMaterial);
			REL::Relocation<func_t> func{ REL::ID(1096263) };
			return func(this);
		}

		NiTexture* GetEnvMap()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetEnvMap);
			REL::Relocation<func_t> func{ REL::ID(364155), 0x90 };
			return func(this);
		}

		NiTexture* GetEnvMapMask()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetEnvMapMask);
			REL::Relocation<func_t> func{ REL::ID(364155), 0xA0 };
			return func(this);
		}

		NiTexture* GetGrayscaleTexture()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetGrayscaleTexture);
			REL::Relocation<func_t> func{ REL::ID(364155), 0xB0 };
			return func(this);
		}

		NiTexture* GetNormalMap()
		{
			using func_t = decltype(&BSEffectShaderProperty::GetNormalMap);
			REL::Relocation<func_t> func{ REL::ID(1321110), 0x10 };
			return func(this);
		}

		void SetBaseTexture(NiTexture* newTex)
		{
			BSEffectShaderMaterial* material;
			NiTexture* oldTex;

			material = (BSEffectShaderMaterial*)this->material;
			oldTex = material->spBaseTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				material->spBaseTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetEnvMap(NiTexture* newTex)
		{
			using func_t = decltype(&BSEffectShaderProperty::SetEnvMap);
			REL::Relocation<func_t> func{ REL::ID(855637), 0x3F };
			return func(this, newTex);
		}

		void SetEnvMapMask(NiTexture* newTex)
		{
			BSEffectShaderMaterial* material;
			NiTexture* oldTex;

			material = (BSEffectShaderMaterial*)this->material;
			oldTex = material->spEnvironmentMapMaskTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				material->spEnvironmentMapMaskTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetGrayscaleTexture(NiTexture* newTex)
		{
			BSEffectShaderMaterial* material;
			NiTexture* oldTex;

			material = (BSEffectShaderMaterial*)this->material;
			oldTex = material->spGrayscaleTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				material->spGrayscaleTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		void SetNormalMap(NiTexture* newTex)
		{
			BSEffectShaderMaterial* material;
			NiTexture* oldTex;

			material = (BSEffectShaderMaterial*)this->material;
			oldTex = material->spNormalTexture.get();
			if (oldTex != newTex) {
				if (newTex) {
					_InterlockedIncrement((volatile long*)&newTex->refCount);
				}
				material->spNormalTexture.reset(newTex);
				if (oldTex) {
					if (!_InterlockedDecrement((volatile long*)&oldTex->refCount)) {
						oldTex->DeleteThis();
					}
				}
			}
		}

		static NiObject* CreateObject()
		{
			using func_t = decltype(&BSEffectShaderProperty::CreateObject);
			REL::Relocation<func_t> func{ REL::ID(373342) };
			return func();
		}

		static BSEffectShaderProperty* Create()
		{
			return (BSEffectShaderProperty*)CreateObject();
		}

		//members
		BSParticleShaderCubeEmitter* pEnvCubeEmitter;  // 70
		NiColor* pExternalEmitColor;                   // 78
		std::uint32_t uBaseTextureIndex;               // 80
		float unk84;                                   // 84
	};
	static_assert(sizeof(BSEffectShaderProperty) == 0x88);

	class BSLightingShaderProperty : public BSShaderProperty
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLightingShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSLightingShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSLightingShaderProperty };

		virtual ~BSLightingShaderProperty();

		NiTexture* GetBaseTexture()
		{
			using func_t = decltype(&BSLightingShaderProperty::GetBaseTexture);
			REL::Relocation<func_t> func{ REL::ID(1242168) };
			return func(this);
		}

		BSLightingShaderMaterialBase* GetLightingShaderMaterial()
		{
			using func_t = decltype(&BSLightingShaderProperty::GetLightingShaderMaterial);
			REL::Relocation<func_t> func{ REL::ID(958611) };
			return func(this);
		}

		NiTexture* GetNormalTexture()
		{
			using func_t = decltype(&BSLightingShaderProperty::GetNormalTexture);
			REL::Relocation<func_t> func{ REL::ID(407460), 0x57 };
			return func(this);
		}

		static NiObject* CreateObject()
		{
			using func_t = decltype(&BSLightingShaderProperty::CreateObject);
			REL::Relocation<func_t> func{ REL::ID(1120904) };
			return func();
		}

		static BSLightingShaderProperty* Create()
		{
			return (BSLightingShaderProperty*)CreateObject();
		}

		//members
		NiColorA kProjectedUVColor;                   // 70
		NiColorA kProjectedUVParams;                  // 80
		RenderPassArray kDepthMapRenderPassListA[3];  // 90
		BSRenderPass* pDepthRenderPass;               // A8
		RenderPassArray kForwardPassList;             // B0
		NiColor* pEmissiveColor;                      // B8
		BSFixedString rootName;                       // C0
		float fEmitColorScale;                        // C8
		float fForcedDarkness;                        // CC
		float fSpecularLODFade;                       // D0
		float fEnvmapLODFade;                         // D4
		std::uint32_t uiBaseTechniqueID;              // D8
		std::uint32_t ClearCommandBufferCount;        // DC
		std::uint16_t usDebugTintIndex;               // E0
		std::uint16_t uiStencilRef;                   // E2
	};
	static_assert(sizeof(BSLightingShaderProperty) == 0xE8);

	class BSWaterShaderProperty : public BSShaderProperty
	{
	public:
		static constexpr auto RTTI{ RTTI::BSWaterShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSWaterShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSWaterShaderProperty };

		enum EWaterShaderPropertyFlag
		{
			BSWSP_DISPLACEMENT = 0x0,
			BSWSP_LOD = 0x1,
			BSWSP_DEPTH = 0x2,
			BSWSP_ACTOR_IN_WATER = 0x3,
			BSWSP_ACTOR_IN_WATER_IS_MOVING = 0x4,
			BSWSP_UNDERWATER = 0x5,
			BSWSP_REFLECTIONS = 0x6,
			BSWSP_REFRACTIONS = 0x7,
			BSWSP_VERTEX_UV = 0x8,
			BSWSP_VERTEX_ALPHA_DEPTH = 0x9,
			BSWSP_PROCEDURAL = 0xA,
			BSWSP_FOG = 0xB,
			BSWSP_UPDATE_CONSTANTS = 0xC,
			BSWSP_CUBEMAP = 0xD,
		};

		//members
		std::uint32_t uiWaterFlags;
		std::uint32_t iStencilMask;
		NiPlane kWaterPlane;
		RenderPassArray kSimpleRenderPassArray;
		RenderPassArray kRainOcclusionMapRenderPassList;
		BSShaderPropertyLightData kLightData;
	};
}
