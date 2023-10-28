#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>

Game::Game()
{
}

void Game::setPlayerScoreDefault(int score)
{
	this->m_Scores.push_back(getID(), score); // getID din User.h
}

void Game::sortPlayersByScore() {
	std::sort(m_Scores.begin(), m_Scores.end(), [](const auto& a, const auto& b) {
		return a.second > b.second; });
}

void Game::addUsedWord(const std::string& word) {
	m_usedWords.push_back(word);
}

