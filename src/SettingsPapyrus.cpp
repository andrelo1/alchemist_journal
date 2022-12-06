#include "SettingsPapyrus.h"
#include "Settings.h"

namespace AlchemistJournal::SettingsPapyrus
{
	void Read(RE::StaticFunctionTag*) {
		Settings::Get().Read();
	}

	void Write(RE::StaticFunctionTag*) {
		Settings::Get().Write();
	}

	std::int32_t GetIngredientsSorting(RE::StaticFunctionTag*) {
		return Settings::Get().ingredientsSorting;
	}

	void SetIngredientsSorting(RE::StaticFunctionTag*, std::int32_t a_sorting) {
		Settings::Get().ingredientsSorting = static_cast<Settings::IngredientsSorting>(a_sorting);
	}

	bool GetShowMagnitude(RE::StaticFunctionTag*) {
		return Settings::Get().showMagnitude;
	}

	void SetShowMagnitude(RE::StaticFunctionTag*, bool a_show) {
		Settings::Get().showMagnitude = a_show;
	}

	bool GetShowDuration(RE::StaticFunctionTag*) {
		return Settings::Get().showDuration;
	}

	void SetShowDuration(RE::StaticFunctionTag*, bool a_show) {
		Settings::Get().showDuration = a_show;
	}

	bool GetShowUnknown(RE::StaticFunctionTag*) {
		return Settings::Get().showUnknown;
	}

	void SetShowUnknown(RE::StaticFunctionTag*, bool a_show) {
		Settings::Get().showUnknown = a_show;
	}

	std::int32_t GetValueDisplayFormat(RE::StaticFunctionTag*) {
		return Settings::Get().valueDisplayFormat;
	}

	void SetValueDisplayFormat(RE::StaticFunctionTag*, std::int32_t a_format) {
		Settings::Get().valueDisplayFormat = static_cast<Settings::ValueDisplayFormat>(a_format);
	}

	std::string GetFontFace(RE::StaticFunctionTag*) {
		return Settings::Get().fontFace;
	}

	void SetFontFace(RE::StaticFunctionTag*, std::string a_face) {
		Settings::Get().fontFace = a_face;
	}

	std::int32_t GetFontSize(RE::StaticFunctionTag*) {
		return Settings::Get().fontSize;
	}

	void SetFontSize(RE::StaticFunctionTag*, std::int32_t a_size) {
		Settings::Get().fontSize = a_size;
	}

	std::int32_t GetFontColor(RE::StaticFunctionTag*) {
		return Settings::Get().fontColor;
	}

	void SetFontColor(RE::StaticFunctionTag*, std::int32_t a_color) {
		Settings::Get().fontColor = a_color;
	}

	std::int32_t GetFontColorMagnitude(RE::StaticFunctionTag*) {
		return Settings::Get().fontColorMagnitude;
	}

	void SetFontColorMagnitude(RE::StaticFunctionTag*, std::int32_t a_color) {
		Settings::Get().fontColorMagnitude = a_color;
	}

	std::int32_t GetFontColorDuration(RE::StaticFunctionTag*) {
		return Settings::Get().fontColorDuration;
	}

	void SetFontColorDuration(RE::StaticFunctionTag*, std::int32_t a_color) {
		Settings::Get().fontColorDuration = a_color;
	}

	void Register() {
		SKSE::GetPapyrusInterface()->Register([](RE::BSScript::IVirtualMachine* a_vm) {
			a_vm->RegisterFunction("Read", "ALCJRN_Settings", Read);
			a_vm->RegisterFunction("Write", "ALCJRN_Settings", Write);
			a_vm->RegisterFunction("GetIngredientsSorting", "ALCJRN_Settings", GetIngredientsSorting);
			a_vm->RegisterFunction("SetIngredientsSorting", "ALCJRN_Settings", SetIngredientsSorting);
			a_vm->RegisterFunction("GetShowMagnitude", "ALCJRN_Settings", GetShowMagnitude);
			a_vm->RegisterFunction("SetShowMagnitude", "ALCJRN_Settings", SetShowMagnitude);
			a_vm->RegisterFunction("GetShowDuration", "ALCJRN_Settings", GetShowDuration);
			a_vm->RegisterFunction("SetShowDuration", "ALCJRN_Settings", SetShowDuration);
			a_vm->RegisterFunction("GetShowUnknown", "ALCJRN_Settings", GetShowUnknown);
			a_vm->RegisterFunction("SetShowUnknown", "ALCJRN_Settings", SetShowUnknown);
			a_vm->RegisterFunction("GetValueDisplayFormat", "ALCJRN_Settings", GetValueDisplayFormat);
			a_vm->RegisterFunction("SetValueDisplayFormat", "ALCJRN_Settings", SetValueDisplayFormat);
			a_vm->RegisterFunction("GetFontFace", "ALCJRN_Settings", GetFontFace);
			a_vm->RegisterFunction("SetFontFace", "ALCJRN_Settings", SetFontFace);
			a_vm->RegisterFunction("GetFontSize", "ALCJRN_Settings", GetFontSize);
			a_vm->RegisterFunction("SetFontSize", "ALCJRN_Settings", SetFontSize);
			a_vm->RegisterFunction("GetFontColor", "ALCJRN_Settings", GetFontColor);
			a_vm->RegisterFunction("SetFontColor", "ALCJRN_Settings", SetFontColor);
			a_vm->RegisterFunction("GetFontColorMagnitude", "ALCJRN_Settings", GetFontColorMagnitude);
			a_vm->RegisterFunction("SetFontColorMagnitude", "ALCJRN_Settings", SetFontColorMagnitude);
			a_vm->RegisterFunction("GetFontColorDuration", "ALCJRN_Settings", GetFontColorDuration);
			a_vm->RegisterFunction("SetFontColorDuration", "ALCJRN_Settings", SetFontColorDuration);

			return true;
		});
	}
}