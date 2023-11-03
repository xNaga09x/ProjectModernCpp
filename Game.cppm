export module game;

import user;
import <vector>;
import <string>;
import <algorithm>;
import <fstream>;

namespace game 
{
	export class Game 
	{
	public:
		Game();
		~Game();

		void setPlayerScoreDefault(float, user::User);
		void setScores(const std::vector<std::pair <uint32_t, float>>& scores);

		std::vector<user::User> getPlayers() const;
		std::vector<std::string> getUsedWords() const;
		std::vector<std::string> getWords() const;
		std::vector<std::pair <uint32_t, float>> getScores() const;

		void MediumTime();
		void sortPlayersByScore();
		std::string selectRandomWord(const std::vector<std::string> m_Words) const;
		void addUsedWord(const std::string&);
		void FileRead();
		int getCurrentRound(int);
		void GameOver(int);
	private:
		static const int noRounds = 4;
		std::vector<user::User> m_Players;
		std::vector<std::string> m_usedWords;
		std::vector<std::string> m_Words;
		std::vector<std::pair <uint32_t, float>> m_Scores;//playerID, scor
	};
}