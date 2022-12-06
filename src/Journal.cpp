#include "Journal.h"
#include "JournalData.h"
#include "Settings.h"

namespace AlchemistJournal
{
	namespace detail
	{
		std::string wstr_to_str(std::wstring const& wstr) {
			static std::map<std::wstring, std::string> cache;

			if (wstr.empty()) {
				return "";
			}

			if (cache.contains(wstr)) {
				return cache[wstr];
			}

			std::setlocale(LC_ALL, "en_US.utf8");
			auto wstr_ = wstr.c_str();
			std::mbstate_t state = std::mbstate_t();
			std::size_t size = std::wcsrtombs(nullptr, &wstr_, 0, &state);

			if (size == -1) {
				return "";
			}

			std::vector<char> buf(size + 1);
			std::wcsrtombs(&buf[0], &wstr_, buf.size(), &state);
			cache.insert({wstr, &buf[0]});
			return &buf[0];
		}

		std::string FormatEffectName(JournalData::Entry& a_entry) {
			return std::format("<u>{}</u>", a_entry.effect->fullName.c_str());
		}

		std::string FormatEffectDescription(JournalData::Entry& a_entry) {
			auto& settings = Settings::Get();
			std::string description{a_entry.effect->magicItemDescription.c_str()};
			description = std::regex_replace(description, std::regex("<((?!mag>|dur>).*?)>"), "$1");
			description = std::regex_replace(description, std::regex("<mag>"), std::format("<font color='#{:06x}'>M</font>", settings.fontColorMagnitude));
			description = std::regex_replace(description, std::regex("<dur>"), std::format("<font color='#{:06x}'>D</font>", settings.fontColorDuration));
			return description;
		}

		std::string FormatMagnitudeNumber(JournalData::Entry& a_entry) {
			auto& settings = Settings::Get();
			return std::format("<font color='#{:06x}'>{:g}</font>", settings.fontColorMagnitude, a_entry.magnitude);
		}

		std::string FormatMagnitudeDots(JournalData::Entry& a_entry) {
			auto& settings = Settings::Get();

			if (!settings.dotsMax) {
				return "";
			}

			auto n = a_entry.magnitudeMin != a_entry.magnitudeMax ? static_cast<std::uint32_t>(std::ceil((a_entry.magnitude - a_entry.magnitudeMin) / (a_entry.magnitudeMax - a_entry.magnitudeMin) * settings.dotsMax)) : settings.dotsMax;
			return std::format("<font color='#{:06x}'>{:s}</font>", settings.fontColorMagnitude, wstr_to_str(std::wstring(n == 0 ? 1 : n, settings.dotsChar)));
		}

		std::string FormatDurationNumber(JournalData::Entry& a_entry) {
			auto& settings = Settings::Get();
			return std::format("<font color='#{:06x}'>{:g}</font>", settings.fontColorDuration, a_entry.duration);
		}

		std::string FormatDurationDots(JournalData::Entry& a_entry) {
			auto& settings = Settings::Get();

			if (!settings.dotsMax) {
				return "";
			}
			
			auto n = a_entry.durationMin != a_entry.durationMax ? static_cast<std::uint32_t>(std::ceil((a_entry.duration - a_entry.durationMin) / (a_entry.durationMax - a_entry.durationMin) * settings.dotsMax)) : settings.dotsMax;
			return std::format("<font color='#{:06x}'>{:s}</font>", settings.fontColorDuration, wstr_to_str(std::wstring(n == 0 ? 1 : n, settings.dotsChar)));
		}

		std::string FormatIngredientText(JournalData::Entry& a_entry) {
			auto& settings = Settings::Get();
			auto text = std::format("~{}", a_entry.ingredient->fullName.c_str());

			if (settings.showMagnitude) {
				switch (settings.valueDisplayFormat) {
					case Settings::ValueDisplayFormat::Number: {
						text += "  ";
						text += FormatMagnitudeNumber(a_entry);
						break;
					}
					case Settings::ValueDisplayFormat::Dots: {
						text += "  ";
						text += FormatMagnitudeDots(a_entry);
						break;
					}
				}
			}

			if (settings.showDuration) {
				switch (settings.valueDisplayFormat) {
					case Settings::ValueDisplayFormat::Number: {
						text += "  ";
						text += FormatDurationNumber(a_entry);
						break;
					}
					case Settings::ValueDisplayFormat::Dots: {
						text += "  ";
						text += FormatDurationDots(a_entry);
						break;
					}
				}
			}

			return text;			
		}
	}

	Journal& Journal::Get() {
		static Journal journal;
		return journal;
	}

	void Journal::Update() {
		text.clear();

		auto& settings = Settings::Get();
		settings.Read();

		auto& data = JournalData::Get();
		data.Update();

		text += std::format("<font face='{:s}' size='{:d}' color='#{:06x}'>", settings.fontFace, settings.fontSize, settings.fontColor);

		auto filter = [](JournalData::Entry const& e) {
			return Settings::Get().showUnknown || e.known;
		};

		auto comp = [](JournalData::Entry const& e1, JournalData::Entry const& e2) {
			return e1.effect == e2.effect;
		};

		for(auto r: data.entries | std::views::filter(filter) | std::views::chunk_by(comp)) {
			text += detail::FormatEffectName(r.front());
			text += "\n\n";
			text += detail::FormatEffectDescription(r.front());
			text += "\n\n";

			for (auto& e: r) {
				text += detail::FormatIngredientText(e);
				text += '\n';
			}
			text += "[pagebreak]\n";
		}

		text += "</font>";
	}

	const std::string& Journal::GetText() const {
		return text;
	}
}