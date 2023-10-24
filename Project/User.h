#pragma once
#include <string>
#include <vector>

class User
{
public:
	User();
	User(const uint32_t& id, const std::string name, const std::vector<std::pair<int, int>>& matchHistory, const float historyAverage);
private:
	uint32_t m_id;
	std::string m_name;
	std::vector<std::pair<int, int>>m_matchHistory;
	float m_historyAverage;
};

