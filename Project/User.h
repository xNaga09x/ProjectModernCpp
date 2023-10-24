#pragma once
#include <string>
#include <vector>

class User
{
private:
public:
	uint32_t m_id;
	std::string m_name;
	std::vector<std::pair<int, int>>m_matchHistory;
	float m_historyAverage;
};

