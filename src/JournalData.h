#pragma once

namespace AlchemistJournal
{
	struct JournalData
	{
		struct Entry
		{
			RE::IngredientItem*	ingredient{nullptr};
			RE::EffectSetting*	effect{nullptr};
			float				magnitude{0.0f};
			float				magnitudeMin{0.0f};
			float				magnitudeMax{0.0f};
			float				duration{0.0f};
			float				durationMin{0.0f};
			float				durationMax{0.0f};
			bool				known{false};
		};

		static JournalData&	Get();

		void	Update();
		void	Sort();

		std::vector<Entry>	entries;

	private:
		void	CalcMinMaxValues();
	};
}