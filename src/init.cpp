#include "init.h"
#include "Settings.h"
#include "BookMenu.h"
#include "SettingsPapyrus.h"

namespace AlchemistJournal
{
	void Init() {
		Settings::Get().Read();
		BookMenu::Init();
		SettingsPapyrus::Register();
	}
}