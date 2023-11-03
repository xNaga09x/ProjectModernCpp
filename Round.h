#pragma once
import "Game.h";
import user;

class Round:
	public Game
{
private:
	int m_noRounds;
	//static const int m_noSubrounds = Players.size();
	//constructori

public:

	Round();
	Round(int m_noRounds);
};

