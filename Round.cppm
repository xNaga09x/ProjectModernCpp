export module round;
import game;

namespace round 
{
	export class Round :public game::Game {
	private:
		int m_noRounds;
		//static const int m_noSubrounds = Players.size();
		//constructori

	public:

		Round();
		Round(int m_noRounds);
	};
}