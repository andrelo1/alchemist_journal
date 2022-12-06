#pragma once

namespace AlchemistJournal
{
	struct Settings
	{
		enum IngredientsSorting
		{
			Name,
			MagnitudeAsc,
			MagnitudeDesc,
			DurationAsc,
			DurationDesc
		};

		enum ValueDisplayFormat
		{
			Number,
			Dots
		};

		static Settings&	Get();

		void	Read();
		void	Write();

		IngredientsSorting	ingredientsSorting{IngredientsSorting::Name};
		bool				showMagnitude{false};
		bool				showDuration{false};
		bool				showUnknown{false};
		ValueDisplayFormat	valueDisplayFormat{ValueDisplayFormat::Number};
		wchar_t				dotsChar{L'\xb7'};
		std::uint32_t		dotsMax{5};
		std::string			fontFace{"$EverywhereMediumFont"};
		std::uint32_t		fontSize{20};
		std::uint32_t		fontColor{0x000000};
		std::uint32_t		fontColorMagnitude{0x914821};
		std::uint32_t		fontColorDuration{0x344A00};
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Settings, ingredientsSorting, showMagnitude, showDuration, showUnknown, valueDisplayFormat, dotsChar, dotsMax, fontFace, fontSize, fontColor, fontColorMagnitude, fontColorDuration)
}