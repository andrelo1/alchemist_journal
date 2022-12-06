#pragma once

namespace AlchemistJournal
{
	class BookMenu: public RE::BookMenu
	{
	public:
		void	SetBookText();
		void	SetBookTextHook();

		static void	Init();
	};
}