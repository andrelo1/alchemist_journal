#include "BookMenu.h"
#include "Journal.h"
#include "Offsets.h"

namespace AlchemistJournal
{
	namespace
	{
		std::uintptr_t SetBookTextAddr{0};
	}

	void BookMenu::SetBookText() {
		using func_t = decltype(&BookMenu::SetBookText);
		REL::Relocation<func_t> func{SetBookTextAddr};
		func(this);
	}

	void BookMenu::SetBookTextHook() {
		REL::Relocation<RE::BSString*> openedBookText{Offset::OpenedBookText};

		if (*openedBookText != "#AlchemistJournal") {
			SetBookText();
			return;
		}

		if (!book) {
			return;
		}

		auto& journal = Journal::Get();
		journal.Update();

		RE::FxResponseArgs<2> args;
		args.Add(journal.GetText().c_str());
		args.Add(isNote);
		RE::FxDelegate::Invoke(book.get(), "SetBookText", args);
	}

	void BookMenu::Init() {
		SetBookTextAddr = Offset::BookMenu::SetBookText.address();
		auto SetBookTextHookAddr = &BookMenu::SetBookTextHook;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(reinterpret_cast<PVOID*>(&SetBookTextAddr), reinterpret_cast<PVOID&>(SetBookTextHookAddr));

		if (DetourTransactionCommit() != NO_ERROR) {
			spdlog::error("failed to attach detour");
		}
	}
}