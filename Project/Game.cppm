export module game;
import user;
import <vector>;
import <string>;
import <algorithm>;
import <iostream>;
import <fstream>;
import <random>;


namespace gartic
{
	export class Game 
	{
	public:
		Game();
		~Game();

		const std::vector<User>& GetPlayers() const;
		const std::vector<std::string>& GetUsedWords() const;
		const std::vector<std::string>& GetWords() const;
		const std::vector<std::pair <uint32_t, float>>& GetScores() const;

		std::string selectRandomWord(const std::vector<std::string> m_Words) const;
		void SetPlayerScoreDefault(float, User);
		void SetScores(const std::vector<std::pair <uint32_t, float>>& scores);
		void MediumTime();
		void SortPlayersByScore();
		void verifyGuessed();// AICI TREBUIE SA VERIFICI DACA A GHICIT user-ul cuvantul si s-a oprit cronometrul pentru el + adaugare scor, + calculateScore
		void AddUsedWord(const std::string&);
		void FileRead();
		int GetCurrentRound(int);
		void GameOver(int);
		double CalculateScoreGuesser(double);
		double CalculateScorePainter(double);

		std::string GetGuessedWord() const;

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