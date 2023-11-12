export module game;
import user;
import <vector>;
import <string>;
import <algorithm>;


namespace gartic
{
	export class Game 
	{
	public:
		Game();
		~Game();


		std::vector<User> getPlayers() const;
		std::vector<std::string> getUsedWords() const;
		std::vector<std::string> getWords() const;
		std::vector<std::pair <uint32_t, float>> getScores() const;

		std::string selectRandomWord(const std::vector<std::string> m_Words) const;
		void setPlayerScoreDefault(float, User);
		void setScores(const std::vector<std::pair <uint32_t, float>>& scores);
		void MediumTime();
		void sortPlayersByScore();
		void verifyGuessed();// AICI TREBUIE SA VERIFICI DACA A GHICIT user-ul cuvantul si s-a oprit cronometrul pentru el + adaugare scor, + calculateScore
		void addUsedWord(const std::string&);
		void FileRead();
		int getCurrentRound(int);
		void GameOver(int);
		double calculateScoreGuesser(double);
		double calculateScorePainter(double);

		std::string getGuessedWord() const;

		Game& operator=(const Game& other);//copy assigment
		Game(Game&& other) noexcept;//move constructor
		Game& operator=(Game&& other) noexcept;//move assigment
	private:
		static const int noRounds = 4;
		std::vector<User> m_Players;
		std::vector<std::string> m_usedWords;
		std::vector<std::string> m_Words;
		std::vector<std::pair <uint32_t, float>> m_Scores;//playerID, scor
	};
}