#pragma once

namespace RE
{
	class NiAVObject;
	class BSGeometry;

	namespace BSVisit
	{
		enum BSVisitControl : std::int32_t
		{
			Continue = 0x0,
			Stop = 0x1,
			SkipChildren = 0x2,
		};

		template <class T>
		class TraverseSceneGraphAVObjects
		{
		public:
			/*
			list[0] = LF_ONEMETHOD, public, VANILLA, index = 0x000233DA, name = 'operator()'
			list[1] = LF_ONEMETHOD, private, STATIC, index = 0x000233DB, name = '<helper_func_cdecl>'
			list[2] = LF_ONEMETHOD, public, VANILLA, index = 0x000233DE, name = 'operator enum BSVisit::BSVisitControl (__cdecl *)(class NiAVObject *)'
			list[3] = LF_ONEMETHOD, private, STATIC, index = 0x000233DF, name = '<helper_func_stdcall>'
			list[4] = LF_ONEMETHOD, public, VANILLA, index = 0x000233E2, name = 'operator enum BSVisit::BSVisitControl (__stdcall *)(class NiAVObject *)'
			list[5] = LF_ONEMETHOD, private, STATIC, index = 0x000233E3, name = '<helper_func_fastcall>'
			list[6] = LF_ONEMETHOD, public, VANILLA, index = 0x000233E6, name = 'operator enum BSVisit::BSVisitControl (__fastcall *)(class NiAVObject *)'
			*/

			BSVisitControl operator()(NiAVObject* apAVObject, T visitor);
		};

		template <class T>
		class TraverseScenegraphNodes
		{
		public:
			BSVisitControl operator()(NiAVObject* ap3D, T visitor);
		};

		BSVisitControl VisitSceneGraphAVObjects(NiAVObject* apAVObject, BSVisit::BSVisitControl (&visitor)(NiAVObject*))
		{
			using func_t = decltype(&VisitSceneGraphAVObjects);
			REL::Relocation<func_t> func{ REL::ID(1449576) };
			return func(apAVObject, visitor);
		}

		BSVisitControl VisitScenegraphGeometries_AVObject(NiAVObject* apAVObject, BSVisit::BSVisitControl (&visitor)(NiAVObject*))
		{
			using func_t = decltype(&VisitScenegraphGeometries_AVObject);
			REL::Relocation<func_t> func{ REL::ID(298633) };
			return func(apAVObject, visitor);
		}

		BSVisitControl VisitScenegraphGeometries_Geometry(NiAVObject* apAVObject, BSVisit::BSVisitControl (&visitor)(BSGeometry*))
		{
			using func_t = decltype(&VisitScenegraphGeometries_Geometry);
			REL::Relocation<func_t> func{ REL::ID(240214) };
			return func(apAVObject, visitor);
		}

		BSVisitControl VisitScenegraphNodes(NiAVObject* ap3D, BSVisit::BSVisitControl (&visitor)(NiAVObject*))
		{
			using func_t = decltype(&VisitScenegraphNodes);
			REL::Relocation<func_t> func{ REL::ID(659184) };
			return func(ap3D, visitor);
		}
	}

	extern template class BSVisit::TraverseSceneGraphAVObjects<BSVisit::BSVisitControl(NiAVObject*)>;
}
