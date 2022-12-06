namespace AlchemistJournal {
	class Journal {
	public:
		static Journal&	Get();

		void				Update();
		const std::string&	GetText() const;

	private:
		std::string	text;
	};
}