#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <random>
Game::Game()
{
}

Game::~Game()
{
}


void Game::setPlayerScoreDefault(float score,user::User entity)
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

void Game::citireFisier(std::vector<std::string>& m_Words)
{
	std::ifstream file("GuessingWords.txt");
	std::string word;
	while(!file.eof())
	{
		file >> word;
		m_Words.push_back(word);
	}
	file.close();
}

void Game::sortPlayersByScore() {
	std::sort(m_Scores.begin(), m_Scores.end(), [](const auto& a, const auto& b) {
		return a.second > b.second; });
}

//std::string Game::selectRandomWord(const std::vector<std::string> m_Words) const
//{
//}

void Game::addUsedWord(const std::string& word) {
	m_usedWords.push_back(word);
	
}
