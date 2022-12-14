#pragma once

#include "f4se/NiObjects.h"
#include "f4se/GameTypes.h"

struct ID3D11ShaderResourceView;
struct ID3D11Resource;

// 40
struct BSRenderData { //this might be BSGraphics::Texture
	ID3D11ShaderResourceView	* resourceView;	// 00
	ID3D11Resource				* resource;		// 08
	UInt64						unk10;			// 10
	UInt64						unk18;			// 18
	UInt64						unk20;			// 20
	UInt16						width;			// 28 //28-30 is BSGraphics::TextureHeader
	UInt16						height;			// 2A
	UInt8						unk2B;			// 2B
	UInt8						unk2C;			// 2C
	UInt16						unk2D;			// 2D
	UInt64						unk30;			// 30
	UInt64						unk38;			// 38
};

// 48
class NiTexture : public NiObject {
public:
	NiTexture() { CALL_MEMBER_FN(this, ctor)(); };
	//virtual ~NiTexture();
	
	//add
	//virtual BSTextureArray::Texture* IsBSTextureArray();

	//members
	BSFixedString	name;				// 10
	UInt32			flags;				// 18
	UInt32			unk1C;				// 1C
	NiTexture		* prevTexture;		// 20
	NiTexture		* nextTexture;		// 28
	UInt64			unk30;				// 30 //BSTSmartPointer<BSResource::Stream>	stream;
	BSRenderData	* rendererData;		// 38 //BSGraphics::Texture	rendererTexture
	UInt8			desiredDegradeLevel;// 40
	UInt8			savedDegradeLevel;  // 41
	bool			isDDX : 1;          // 42:0
	bool			isSRGB : 1;         // 42:1

	MEMBER_FN_PREFIX(NiTexture);
	DEFINE_MEMBER_FN(ctor, void, 0x01BA5670);
	DEFINE_MEMBER_FN(Create, NiTexture*, 0x01BA4B90, BSFixedString&, bool, bool);
	DEFINE_MEMBER_FN(CreateEmpty, NiTexture*, 0x01BA5220, BSFixedString&, bool, bool);
	
	NiTexture* Create(BSFixedString& name, bool a1, bool a2);
	NiTexture* CreateEmpty(BSFixedString& name, bool a2, bool a3);
};
STATIC_ASSERT(sizeof(NiTexture) == 0x48);

class BSTextureArray {
public:

	class Texture : public NiTexture {
	public:

	};

	class StaticTexture : public NiTexture {
	public:
		virtual ~StaticTexture();
	};

	// 78
	class StaticTextureIndexed : public StaticTexture {
	public:
		virtual ~StaticTextureIndexed();

		MEMBER_FN_PREFIX(StaticTextureIndexed);
		DEFINE_MEMBER_FN(ctor, StaticTextureIndexed*, 0x01CE68C0, UInt32 unk1, int unk2, bool unk3);

		UInt64	unk48[(0x78 - 0x48) >> 3];
	};
};

// 10
class BSTextureSet : public NiObject {
public:

	//add
	virtual BSFixedString GetTextureFilenameFS(UInt32 typeEnum);
	virtual const char * GetTextureFilename(UInt32 typeEnum);
	virtual void Unk_2A();
	virtual void GetTexture(UInt32 typeEnum, NiPointer<NiTexture> & texture, bool unk1);
	virtual void SetTextureFilename(UInt32 typeEnum, const char * path);
};

// 60
class BSShaderTextureSet : public BSTextureSet {
public:
	BSFixedString	textures[10];	// 10

	MEMBER_FN_PREFIX(BSShaderTextureSet);
	DEFINE_MEMBER_FN(Copy, BSShaderTextureSet*, 0x004C36B0);
};
STATIC_ASSERT(sizeof(BSShaderTextureSet) == 0x60);

//BSShaderTextureSet::CreateObject
typedef BSShaderTextureSet * (* _CreateBSShaderTextureSet)();
extern RelocAddr <_CreateBSShaderTextureSet> CreateBSShaderTextureSet;

//NiTexture::CreateEmpty
typedef NiTexture * (* _CreateTexture)(const BSFixedString & name, UInt8 unk1); // unk1 is true on diffuses?
extern RelocAddr <_CreateTexture> CreateTexture;

//BSShaderManager::GetTexture
typedef void (* _LoadTextureByPath)(const char * filePath, bool unk1, NiTexture *& texture, SInt32 unk2, UInt64 unk3, UInt64 unk4); // unk1=1, unk2=0, unk3=0, unk4=0 
extern RelocAddr <_LoadTextureByPath> LoadTextureByPath;