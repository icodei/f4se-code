#include "ShaderInfo.h"

ShaderInfo& ShaderInfo::getInstance() {
	static ShaderInfo instance;
	return instance;
}

void ShaderInfo::EraseAllShaderInfo() {
	ShaderInfo& Info = ShaderInfo::getInstance();

	if (!Info.shaderList.empty()) {
		Info.shaderList.clear();
	}
}

void ShaderInfo::FillAllShaderInfo() {
}

void ShaderInfo::PrintAllShaderInfo(unordered_map<const char*, uintptr_t> const& map) {
	auto print = []() {};
	std::for_each(map.begin(), map.end(), [](std::pair<const char*, uintptr_t> p) {
		ShaderInfo::PrintShaderInfo(p.first, (BSReloadShaderI*)p.second);
	});
}

void ShaderInfo::EraseShaderInfo(const char* a_name) {
	ShaderInfo& Shader = ShaderInfo::getInstance();
	Shader.shaderList.erase(a_name);
}

void ShaderInfo::FillShaderInfo(const char* a_name, BSReloadShaderI* a_shader, bool a_print) {
	ShaderInfo& Shader = ShaderInfo::getInstance();
	Shader.shaderList.insert(std::pair<const char*, uintptr_t>(a_name, (uintptr_t)a_shader));
	if (a_print) {
		ShaderInfo::PrintShaderName(a_name, a_shader);
	}
}

void ShaderInfo::PrintShaderInfo(const char* a_name, BSReloadShaderI* a_shader) {
	ShaderInfo& Info = ShaderInfo::getInstance();
	char buffer[2120];

	std::fstream stream;
	const std::filesystem::path basepath = "Data/ShaderDump/";
	std::filesystem::path filepath = "";

	uint32_t techniqueID = NULL;
	string techniqueName = ""s;

	BSShader* shader = (BSShader*)a_shader;

	if (IsCompute(a_name)) {
		logger::info(fmt::format(FMT_STRING(";{0:─^{1}};"), fmt::format(FMT_STRING(" Compute Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
		BSComputeShader* compute = (BSComputeShader*)a_shader;
		if (!&compute->ComputeShaderMap || compute->ComputeShaderMap.empty()) {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " NO COMPUTE SHADERS "sv, 120));
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " COMPUTE SHADERS "sv, 120));
			for (auto it = shader->computeShaders.begin(); it != shader->computeShaders.end(); it++) {
				BSGraphics::ComputeShader* cs = (*it);
				if (cs) {
					techniqueID = cs->id;
					techniqueName.clear();
					logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), "COMPUTE", techniqueID).c_str(), 120));
					stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, nullptr, ".cs"), std::ios::out | std::ios::binary);
					if (stream) {
						stream.write((char*)cs->GetByteCodeBuffer(), cs->byteCodeSize);
					}
				}
			}
		}
	} else {
		if (IsImagespace(a_name)) {
			BSImagespaceShader* BSISShader = (BSImagespaceShader*)shader;
			if (BSISShader->isComputeShader) {
				logger::info(fmt::format(FMT_STRING(";{0:─^{1}};"), fmt::format(FMT_STRING(" Compute Imagespace Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
			} else {
				logger::info(fmt::format(FMT_STRING(";{0:─^{1}};"), fmt::format(FMT_STRING(" Imagespace Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
			}
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:─^{1}};"), fmt::format(FMT_STRING(" Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
		}
		if (!&shader->vertexShaders || shader->vertexShaders.empty()) {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " NO VERTEX SHADERS "sv, 120));
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " VERTEX SHADERS "sv, 120));
			for (auto it = shader->vertexShaders.begin(); it != shader->vertexShaders.end(); it++) {
				BSGraphics::VertexShader* vs = (*it);
				if (vs) {
					techniqueID = vs->id;
					techniqueName.clear();
					shader->GetTechniqueName(techniqueID, buffer, sizeof(buffer));
					techniqueName.assign(buffer).shrink_to_fit();
					if (!techniqueName.empty()) {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), techniqueName, techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, techniqueName.c_str(), ".vs"), std::ios::out | std::ios::binary);
					} else {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), "Unspecified", techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, nullptr, ".vs"), std::ios::out | std::ios::binary);
					}
					if (stream) {
						stream.write((char*)vs->GetByteCodeBuffer(), vs->byteCodeSize);
					}
				}
			}
		}

		if (!&shader->hullShaders || shader->hullShaders.empty()) {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " NO HULL SHADERS "sv, 120));
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " HULL SHADERS "sv, 120));
			for (auto it = shader->hullShaders.begin(); it != shader->hullShaders.end(); it++) {
				BSGraphics::HullShader* hs = (*it);
				if (hs) {
					techniqueID = hs->id;
					techniqueName.clear();
					shader->GetTechniqueName(techniqueID, buffer, sizeof(buffer));
					techniqueName.assign(buffer).shrink_to_fit();
					if (!techniqueName.empty()) {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), techniqueName, techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, techniqueName.c_str(), ".hs"), std::ios::out | std::ios::binary);
					} else {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), "Unspecified", techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, nullptr, ".hs"), std::ios::out | std::ios::binary);
					}
					if (stream) {
						stream.write((char*)hs->GetByteCodeBuffer(), hs->byteCodeSize);
					}
				}
			}
		}

		if (!&shader->domainShaders || shader->domainShaders.empty()) {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " NO DOMAIN SHADERS "sv, 120));
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " DOMAIN SHADERS "sv, 120));
			for (auto it = shader->domainShaders.begin(); it != shader->domainShaders.end(); it++) {
				BSGraphics::DomainShader* ds = (*it);
				if (ds) {
					techniqueID = ds->id;
					techniqueName.clear();
					shader->GetTechniqueName(techniqueID, buffer, sizeof(buffer));
					techniqueName.assign(buffer).shrink_to_fit();
					if (!techniqueName.empty()) {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), techniqueName, techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, techniqueName.c_str(), ".ds"), std::ios::out | std::ios::binary);
					} else {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), "Unspecified", techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, nullptr, ".ds"), std::ios::out | std::ios::binary);
					}
					if (stream) {
						stream.write((char*)ds->GetByteCodeBuffer(), ds->byteCodeSize);
					}
				}
			}
		}

		if (!&shader->pixelShaders || shader->pixelShaders.empty()) {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " NO PIXEL SHADERS "sv, 120));
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " PIXEL SHADERS "sv, 120));
			for (auto it = shader->pixelShaders.begin(); it != shader->pixelShaders.end(); it++) {
				BSGraphics::PixelShader* ps = (*it);
				if (ps) {
					techniqueID = ps->id;
					techniqueName.clear();
					shader->GetTechniqueName(techniqueID, buffer, sizeof(buffer));
					techniqueName.assign(buffer).shrink_to_fit();
					if (!techniqueName.empty()) {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), techniqueName, techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, techniqueName.c_str(), ".ps"), std::ios::out | std::ios::binary);
					} else {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), "Unspecified", techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, nullptr, ".ps"), std::ios::out | std::ios::binary);
					}
					if (stream) {
						stream.write((char*)ps->GetByteCodeBuffer(), ps);
					}
				}
			}
		}

		if (!&shader->computeShaders || shader->computeShaders.empty()) {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " NO COMPUTE SHADERS "sv, 120));
		} else {
			logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), " COMPUTE SHADERS "sv, 120));
			for (auto it = shader->computeShaders.begin(); it != shader->computeShaders.end(); it++) {
				BSGraphics::ComputeShader* cs = (*it);
				if (cs) {
					techniqueID = cs->id;
					techniqueName.clear();
					shader->GetTechniqueName(techniqueID, buffer, sizeof(buffer));
					techniqueName.assign(buffer).shrink_to_fit();
					if (!techniqueName.empty()) {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), techniqueName, techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, techniqueName.c_str(), ".cs"), std::ios::out | std::ios::binary);
					} else {
						logger::info(fmt::format(FMT_STRING(";{0:=^{1}};"), fmt::format(FMT_STRING(" Technique Name: {:s} | ID: {} "), "Unspecified", techniqueID).c_str(), 120));
						stream.open(ShaderInfo::PrepareFilePath(a_name, techniqueID, nullptr, ".cs"), std::ios::out | std::ios::binary);
					}
					if (stream) {
						stream.write((char*)cs->GetByteCodeBuffer(), cs->byteCodeSize);
					}
				}
			}
		}
	}
}

void ShaderInfo::PrintShaderName(const char* a_name, BSReloadShaderI* a_shader) {
	ShaderInfo& Info = ShaderInfo::getInstance();

	BSShader* shader = (BSShader*)a_shader;

	if (IsCompute(a_name)) {
		logger::info(fmt::format(FMT_STRING(";{0: ^{1}};"), fmt::format(FMT_STRING(" Compute Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
	} else {
		if (IsImagespace(a_name)) {
			BSImagespaceShader* BSISShader = (BSImagespaceShader*)shader;
			if (BSISShader->isComputeShader) {
				logger::info(fmt::format(FMT_STRING(";{0: ^{1}};"), fmt::format(FMT_STRING(" Compute Imagespace Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
			} else {
				logger::info(fmt::format(FMT_STRING(";{0: ^{1}};"), fmt::format(FMT_STRING(" Imagespace Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
			}
		} else {
			logger::info(fmt::format(FMT_STRING(";{0: ^{1}};"), fmt::format(FMT_STRING(" Shader: {:s} | Address: {:p} "), a_name, fmt::ptr(a_shader)).c_str(), 120));
		}
	}
}

bool ShaderInfo::IsCompute(const char* a_name) {
	static std::list<string> computeshaders = {
		"DFTiledLighting"s,
		"DFDecalsCS"s,
		"MeshCombinerCompute"s,
		"VertexBufferCopyCS"s,
		"IndexBufferOffsetCS"s,
		"MergeInstancedVertexBufferCopyCS"s,
		"DismemberCS"s,
		"SkinnedDecalCS"s,
		"SDSM"s,
	};

	for (string s : computeshaders) {
		if (s == a_name) {
			return true;
		}
	}
	return false;
}

bool ShaderInfo::IsImagespace(const char* a_name) {
	string name = a_name;
	if (((name[0] == "I"s.front()) && (name[1] == "S"s.front()))) {
		return true;
	} else {
		return false;
	}
}

const char* ShaderInfo::PrepareFilePath(const char* a_name, uint32_t a_techniqueID, const char* a_techniqueName, const char* a_extension, const std::filesystem::path a_basepath) {
	std::filesystem::path filepath = "";
	filepath = a_basepath;
	filepath /= a_name;
	if (!a_techniqueName) {
		filepath += "/";
	} else {
		filepath /= (a_techniqueName);
	}
	filepath += "_";
	filepath += std::to_string(a_techniqueID);
	filepath += a_extension;
	return filepath.string().c_str();
}
