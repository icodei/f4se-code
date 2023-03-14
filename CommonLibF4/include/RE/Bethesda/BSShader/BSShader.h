#pragma once

#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSShader/BSShaderTechniqueIDMap.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiPoint2.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiRefObject.h"
#include "RE/NetImmerse/NiMain/IRendererResourceManager.h"

namespace RE
{
	class BSDynamicLines;
	class BSDynamicTriShape;
	class BSGeometryData;
	class BSIStream;
	class BSLines;
	class BSMeshLODTriShape;
	class BSMultiStreamInstanceTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class NiAVObject;
	class NiDefaultAVObjectPalette;
	class NiNode;
	class NiPick;
	class NiShadeProperty;
	class NiStream;
	class NiTexture;

	struct __declspec(novtable) BSReloadShaderI
	{
	public:
		static constexpr auto RTTI{ RTTI::BSReloadShaderI };
		static constexpr auto VTABLE{ VTABLE::BSReloadShaderI };

		// add
		virtual void ReloadShaders(BSIStream* a_stream) = 0;  // 00
	};
	static_assert(sizeof(BSReloadShaderI) == 0x8);

	class __declspec(novtable) BSShader :
		public NiRefObject,     // 000
		public BSReloadShaderI  // 010
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShader };
		static constexpr auto VTABLE{ VTABLE::BSShader };

		// add
		virtual bool SetupTechnique(std::uint32_t a_currentPass) = 0;                                            // 02
		virtual void RestoreTechnique(std::uint32_t a_currentPass) = 0;                                          // 03
		virtual void SetupMaterial([[maybe_unused]] const BSShaderMaterial* a_material) { return; }              // 04
		virtual void RestoreMaterial([[maybe_unused]] const BSShaderMaterial* a_material) { return; }            // 05
		virtual void SetupMaterialSecondary([[maybe_unused]] const BSShaderMaterial* a_material) { return; }     // 06
		virtual void SetupGeometry(BSRenderPass* a_currentPass) = 0;                                             // 07
		virtual void RestoreGeometry(BSRenderPass* a_currentPass) = 0;                                           // 08
		virtual void GetTechniqueName(std::uint32_t a_techniqueID, char* a_buffer, std::uint32_t a_bufferSize);  // 09
		virtual void RecreateRendererData() { return; }                                                          // 0A
		virtual void ReloadShaders(bool a_clear);                                                                // 0B
		virtual std::uint32_t GetBonesVertexConstant() const { return 0; }                                       // 0C

		// members
		std::int32_t shaderType;                                                     // 018
		BSShaderTechniqueIDMap::MapType<BSGraphics::VertexShader*> vertexShaders;    // 020
		BSShaderTechniqueIDMap::MapType<BSGraphics::HullShader*> hullShaders;        // 050
		BSShaderTechniqueIDMap::MapType<BSGraphics::DomainShader*> domainShaders;    // 080
		BSShaderTechniqueIDMap::MapType<BSGraphics::PixelShader*> pixelShaders;      // 0B0
		BSShaderTechniqueIDMap::MapType<BSGraphics::ComputeShader*> computeShaders;  // 0E0
		const char* fxpFilename;                                                     // 110
	};
	static_assert(sizeof(BSShader) == 0x118);

	class BSShaderResourceManager : public IRendererResourceManager
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShaderResourceManager };
		static constexpr auto VTABLE{ VTABLE::BSShaderResourceManager };

		virtual ~BSShaderResourceManager();

		//add
		virtual BSTriShape* CreateTriShape(std::uint32_t, std::uint16_t*, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, NiPoint3*, NiPoint3*, NiPoint3*, NiColorA*, NiColorA*, std::uint8_t*, NiColorA*, NiColorA*, float*, bool);
		virtual BSTriShape* CreateTriShape(std::uint32_t, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, std::uint16_t*);
		virtual BSTriShape* CreateTriShape(NiStream&, std::uint64_t, std::uint32_t, std::uint32_t, char*&);
		virtual void* CreateTriShapeRendererData(void*, std::uint64_t, std::uint16_t*, std::uint32_t);
		virtual BSSubIndexTriShape* CreateSubIndexTriShape(std::uint32_t, std::uint32_t, std::uint16_t*, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, NiPoint3*, NiPoint3*, NiPoint3*, NiColorA*, NiColorA*, std::uint8_t*, NiColorA*, NiColorA*, float*);
		virtual void IncRefTriShape(void* geomData);
		virtual void DecRefTriShape(void* geomData);
		virtual BSDynamicTriShape* CreateDynamicTriShape(std::uint32_t, std::uint32_t, std::uint16_t*, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, NiPoint3*, NiPoint3*, NiPoint3*, NiColorA*, NiColorA*, std::uint8_t*, NiColorA*, NiColorA*, float*);
		virtual BSDynamicTriShape* CreateDynamicTriShape(std::uint32_t, std::uint32_t, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, std::uint16_t*);
		virtual void IncRefDynamicTriShape(void*);
		virtual void DecRefDynamicTriShape(void*);
		virtual void ConvertBSTriShapeToBSDynamicTriShape(NiNode*, NiDefaultAVObjectPalette*);
		virtual void ApplyMaterials(NiAVObject*);
		virtual void SetTriShapeStreamDynamicFlags(std::uint32_t);
		virtual void* CreateParticleShape();
		virtual void IncRefParticleShape(void*);
		virtual void DecRefParticleShape(void*);
		virtual BSLines* CreateLineShape(std::uint32_t, std::uint16_t*, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, NiPoint3*, NiPoint3*, NiPoint3*, NiColorA*, NiColorA*, std::uint8_t*, NiColorA*, NiColorA*, float*);
		virtual BSDynamicLines* CreateDynamicLineShape(std::uint32_t, std::uint32_t, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, std::uint16_t*);
		virtual void* CreateDynamicLineShape(NiStream&, std::uint64_t, std::uint32_t, std::uint32_t);
		virtual BSDynamicLines* CreateDynamicLineShape(std::uint32_t, std::uint32_t, std::uint16_t*, std::uint32_t, NiPoint3*, NiPoint2*, NiColorA*, NiPoint3*, NiPoint3*, NiPoint3*, NiColorA*, NiColorA*, std::uint8_t*, NiColorA*, NiColorA*, float*);
		virtual void IncRefLines(void*);
		virtual void DecRefLines(void*);
		virtual void IncRefDynamicLines(void*);
		virtual void DecRefDynamicLines(void*);
		virtual void LoadTexture(NiTexture*);
		virtual void CreateStreamingTexture(NiTexture*, void*, void*);
		virtual bool ReadStreamingTextureData(NiTexture*, void*);
		virtual bool CreateStreamingTextureArraySlice(NiTexture*, void*, void*, std::uint32_t);
		virtual bool ReadStreamingTextureDataToArraySlice(NiTexture*, void*, std::uint32_t);
		virtual void FinishStreamingTexture(NiTexture*);
		virtual void IncRefTexture(BSGraphics::Texture*);
		virtual void DecRefTexture(BSGraphics::Texture*);
		virtual void GetTextureWidthHeight(NiTexture*, std::uint32_t&, std::uint32_t&);
		virtual std::uint32_t GetTextureFormat(NiTexture*);
		virtual bool UpdateTextureToDesiredMipLevel(NiTexture*, std::uint32_t&);
		virtual void LoadUpgradeTextureData(NiTexture*);
		virtual bool UpdateStreamingTextureToDesiredMipLevel(NiTexture*, std::uint32_t&, void*, void*);
		virtual void FinishStreamingTextureUpgade(NiTexture*);
		virtual void* CreateVertexBuffer(std::uint32_t&, void*, std::uint32_t, std::uint64_t);
		virtual void DecRefVertexBuffer(void*);
		virtual NiShadeProperty* CreateDefaultEffectShaderProperty(bool, bool);
		virtual BSMeshLODTriShape* CreateMeshLODTriShape(std::uint32_t*, std::uint32_t, std::uint64_t, std::uint32_t, std::uint32_t, void*);
		virtual BSMeshLODTriShape* CreateMeshLODTriShape(BSTriShape*, std::uint32_t*, std::uint32_t);
		virtual std::uint32_t UpdateIndexBufferForInstancing(BSMultiStreamInstanceTriShape*, std::uint32_t);
		virtual bool FindIntersectionsTriShapeFastPath(NiPoint3&, NiPoint3&, NiPick&, BSTriShape*);
		virtual void CreateTangentSpace(std::uint32_t, std::uint16_t*, std::uint32_t, NiPoint3*, NiPoint2*, NiPoint3*, NiPoint3*, NiPoint3*);
		virtual float GetShaderFrameCount();
		virtual float GetShaderTimerDelta();
		virtual void GetFadeNodeSettings(IRendererResourceManager::FadeNodeSettings&);
		virtual void GetCameraVectors(NiPoint3&, NiPoint3&, NiPoint3&);

		static BSShaderResourceManager &GetInstance()
		{
			REL::Relocation<BSShaderResourceManager*> singleton{ REL::ID(1416967) };
			return *singleton;
		}
	};
	static_assert(sizeof(BSShaderResourceManager) == 0x8);
}
