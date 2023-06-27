#pragma once
#include "Global.h"

bool IsPlayerInFirstPerson();
bool IsPlayerInThirdPerson();

const NiAVObject* GetByNameFromPlayer3D(const BSFixedString& name);
const NiAVObject* GetByNameFromPlayer3D(const char* name);

/*;========================================================================================================================================================;*/

TESForm* GetFormFromIdentifier(const string& identifier);
bool GetForms();

char* _MESSAGE(const char* fmt, ...);
void Dump(void* mem, unsigned int size);

template <typename K, typename V>
void print_map(unordered_map<K, V> const& map) {
	auto print_key_value = [](const auto& key, const auto& value) {
		if (!value) {
			logger::warn(FMT_STRING("Hook: {:s} IsHooked: {:s}"), key, value);
		} else {
			logger::info(FMT_STRING("Hook: {:s} IsHooked: {:s}"), key, value);
		}
	};
	for (const std::pair<K, V>& n : map) {
		print_key_value(n.first, n.second);
	}
	
	//std::for_each(map.begin(), map.end(), [](std::pair<K, V> p) {
	//	logger::info(FMT_STRING("Hook: {:s} IsHooked: {%t}"), p.first, p.second);
	//});
}

//Functions to write a simple line of text to logs
void logInfo(string text);
void logInfo(string text);
void logWarn(string text);
void logError(string text);
void logCritical(string text);
