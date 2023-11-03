module game;
import <Windows.h>;
import <iostream>;
import <fstream>;
import <random>;
using game::Game;

Game::Game()
{
}

Game::~Game()
{
}


void Game::setPlayerScoreDefault(float score, user::User entity)
{
	this->m_Scores.push_back({ entity.getId(), score });
}

void Game::setScores(const std::vector<std::pair<uint32_t, float>>& scores)
{
	m_Scores = scores;
}

std::vector<user::User> Game::getPlayers() const
{
	return m_Players;
}

std::vector<std::string> Game::getUsedWords() const
{
	return m_usedWords;
}

std::vector<std::string> Game::getWords() const
{
	return m_Words;
}

std::vector<std::pair <uint32_t, float>> Game::getScores() const
{
	return m_Scores;
}

void Game::MediumTime()
{

}

void Game::FileRead()
{
	std::ifstream file("GuessingWords.txt");
	std::string word;
	while (!file.eof())
	{
		file >> word;
		m_Words.push_back(word);
	}
	file.close();
}

int game::Game::getCurrentRound(int Round)
{
	return Round;
}


void game::Game::GameOver(int currentRound = 0)
{
	while (currentRound < 4)	
	{ 
		if (currentRound == 4)
		{
		} // Animatie sfarsit de Joc / GAME OVER interface .
		else std::cout << this->getCurrentRound(currentRound);
	}
}


void Game::sortPlayersByScore() {
	std::sort(m_Scores.begin(), m_Scores.end(), [](const auto& a, const auto& b) {
		return a.second > b.second; });
}

std::string Game::selectRandomWord(const std::vector<std::string> m_Words) const
{
	if (m_Words.empty()) {
		std::cerr << "m_Words vector is empty. Unable to select a random word." << std::endl;
		return "";
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<size_t> distribution(0, m_Words.size() - 1);
	size_t randomIndex = distribution(gen);

	return m_Words[randomIndex];
}

void Game::addUsedWord(const std::string& word) {
	m_usedWords.push_back(word);

}
