#include "JournalData.h"
#include "Settings.h"

namespace AlchemistJournal
{
	JournalData& JournalData::Get() {
		static JournalData data;
		return data;
	}

	void JournalData::Update() {
		entries.clear();

		auto ingredients = RE::TESDataHandler::GetSingleton()->GetFormArray<RE::IngredientItem>();

		for(auto& ingredient: ingredients) {
			if (!ingredient) {
				continue;
			}

			for (std::uint32_t i{0}; auto& effect: ingredient->effects) {
				if (!effect || !effect->baseEffect) {
					continue;
				}

				entries.push_back({
					.ingredient = ingredient,
					.effect = effect->baseEffect,
					.magnitude = effect->effectItem.magnitude,
					.duration = static_cast<float>(effect->effectItem.duration),
					.known = (ingredient->gamedata.knownEffectFlags & (1 << i)) != 0
				});

				++i;
			}
		}

		CalcMinMaxValues();
		Sort();
	}

	void JournalData::Sort()
	{
		std::ranges::sort(entries, [](auto const& e1, auto const& e2) {
			auto& settings = Settings::Get();

			if (auto res = strcmp(e1.effect->fullName.c_str(), e2.effect->fullName.c_str())) {
				return res < 0;
			}

			switch(settings.ingredientsSorting) {
				case Settings::IngredientsSorting::Name: {
					return strcmp(e1.ingredient->fullName.c_str(), e2.ingredient->fullName.c_str()) < 0;
				}
				case Settings::IngredientsSorting::MagnitudeAsc: {
					return e1.magnitude < e2.magnitude;
				}
				case Settings::IngredientsSorting::MagnitudeDesc: {
					return e1.magnitude > e2.magnitude;
				}
				case Settings::IngredientsSorting::DurationAsc: {
					return e1.duration < e2.duration;
				}
				case Settings::IngredientsSorting::DurationDesc: {
					return e1.duration > e2.duration;
				}
			}

			return false;
		});
	}

	void JournalData::CalcMinMaxValues() {
		std::ranges::sort(entries, {}, &Entry::effect);

		auto comp = [](Entry const& e1, Entry const& e2) {
			return e1.effect == e2.effect;
		};

		for (auto r: entries | std::views::chunk_by(comp)) {
			auto magnitudeMin = std::ranges::min(r, {}, &Entry::magnitude).magnitude;
			auto magnitudeMax = std::ranges::max(r, {}, &Entry::magnitude).magnitude;

			for (auto& e: r) {
				e.magnitudeMin = magnitudeMin;
				e.magnitudeMax = magnitudeMax;
			}

			auto durationMin = std::ranges::min(r, {}, &Entry::duration).duration;
			auto durationMax = std::ranges::max(r, {}, &Entry::duration).duration;

			for (auto& e: r) {
				e.durationMin = durationMin;
				e.durationMax = durationMax;
			}
		}
	}
}