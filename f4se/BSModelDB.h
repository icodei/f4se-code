#pragma once

#include "f4se_common/Utilities.h"
#include "f4se/GameStreams.h"
#include "f4se/NiTypes.h"
#include "f4se/NiNodes.h"
#include "f4se/NiObjects.h"

//class NiAVObject;

class BSModelDB {
public:
	struct ModelData
	{
		UInt64	unk00;			// 00

		enum
		{
			kFlag_Unk1			= (1 << 0),
			kFlag_Dynamic		= (1 << 1),
			kFlag_PostProcess	= (1 << 3),
			kFlag_Unk2			= (1 << 4),
			kFlag_Unk3			= (1 << 5)
		};

		UInt8	modelFlags;		// 08
		// ...
	};

	class BSModelProcessor
	{
	public:
		virtual ~BSModelProcessor() { };

		virtual void Process(ModelData * modelData, const char * modelName, NiAVObject ** root, UInt32 * typeOut) { };
	};

	class TESProcessor : public BSModelProcessor
	{
	public:
		TESProcessor() { }
		virtual ~TESProcessor() { CALL_MEMBER_FN(this, dtor)(); };

		virtual void Process(ModelData * modelData, const char * modelName, NiAVObject ** root, UInt32 * typeOut) override { CALL_MEMBER_FN(this, Impl_Process)(modelData, modelName, root, typeOut); }

		MEMBER_FN_PREFIX(TESProcessor);
		// ??_7BSModelProcessor@BSModelDB@@6B@
		DEFINE_MEMBER_FN(dtor, void, 0x02C57BC8);
		DEFINE_MEMBER_FN(Impl_Process, void, 0x00137E50, ModelData * modelData, const char * modelName, NiAVObject ** root, UInt32 * typeOut);
	};

	enum ENUM_LOD_MULT : UInt32 {
	};
	
	class DBTraits {
	public:
		class ArgsType {
		public:

			ENUM_LOD_MULT LODmult;
			unsigned int texLoadLevel;
			UInt8 flags;
			int unk3;		
		};
		
	};

	MEMBER_FN_PREFIX(BSModelDB);
	DEFINE_MEMBER_FN(Demand, void, 0x01C8E0C0, char * filePath, NiPointer<NiNode> & a2, DBTraits::ArgsType& a3);


	BSResource::ErrorCode Demand(char* filePath, NiPointer<NiNode>& a2, DBTraits::ArgsType& a3);
};

//extern template class BSResource::EntryDB<BSModelDB>;

extern RelocPtr <BSModelDB::BSModelProcessor*> g_TESProcessor;
