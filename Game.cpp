module game;
import <Windows.h>;
import <iostream>;
import <fstream>;
import <random>;

using gartic::Game;

Game::Game()
{
}

Game::~Game()
{
}


void Game::setPlayerScoreDefault(float score, gartic::User entity)
{
	this->m_Scores.push_back({ entity.getId(), score });
}

void Game::setScores(const std::vector<std::pair<uint32_t, float>>& scores)
{
	m_Scores = scores;
}

std::vector<gartic::User> Game::getPlayers() const
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

int Game::getCurrentRound(int Round)
{
	return Round;
}


void Game::GameOver(int currentRound = 0)
{
	while (currentRound < 4)	
	{ 
		if (currentRound == 4)
		{
			std::cout << "trebuie pus ceva cod aici ca sa compileze!";
		} // Animatie sfarsit de Joc / GAME OVER interface .
		else std::cout << this->getCurrentRound(currentRound);
	}
}

Game& Game::operator=(const Game& other)
{
	if (this == &other)
	{
		return *this;
	}
	m_Players = other.m_Players;
	m_usedWords = other.m_usedWords;
	m_Words = other.m_Words;
	m_Scores = other.m_Scores;
	return *this;
}

Game::Game(Game&& other) noexcept
{
	m_Players = std::move(other.m_Players);
	m_usedWords = std::move(other.m_usedWords);
	m_Words = std::move(other.m_Words);
	m_Scores = std::move(other.m_Scores);
}

Game& Game::operator=(Game&& other) noexcept
{
	if (this == &other) {
		return *this;
	}
	m_Players = std::move(other.m_Players);
	m_usedWords = std::move(other.m_usedWords);
	m_Words = std::move(other.m_Words);
	m_Scores = std::move(other.m_Scores);
	return *this;

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
