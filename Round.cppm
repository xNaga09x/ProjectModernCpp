export module round;
import game;


namespace round 
{
	export class Round :public game::Game 
	{
	private:
		int m_noRounds;
		//static const int m_noSubrounds = Players.size();
		//constructori

	public:

		Round();
		Round(int m_noRounds);
		Round(const Round& other);
		int getNoRounds() const;
		void setNoRounds(int noRounds);
		Round(Round&& other) noexcept;
		Round& operator=(Round&& other) noexcept;
		Round& operator=(const Round& other);
	};
}