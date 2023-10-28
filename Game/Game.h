#pragma once
//#include "User.h"
#include<vector>
#include<string>
#include<algorithm>
class Game
{
private:
	static const int noRounds = 4;
	std::vector<User> m_Players;
	std::vector<std::string> m_usedWords;
	std::vector<std::string> m_Words;
	std::vector<std::pair <int32_t, float>> m_Scores;//playerID, scor
public:
	Game();
	void setPlayerScoreDefault(float score=0);
	void MediumTime();
	void sortPlayersByScore();
	void addUsedWord(const std::string&);
};

