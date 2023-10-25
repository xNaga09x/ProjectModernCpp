#pragma once
#include <string>
#include <vector>

class User
{
public:
	User();
	User(const uint32_t& id, const std::string name, const std::vector<std::pair<int, int>>& matchHistory, const float historyAverage);
	int32_t getId() const;
	std::string getName() const;
	std::vector<std::pair<int, int>> getMatchHistory() const;
	float getHistoryAverage() const;
	void setId(const uint32_t id);
	void setName(const std::string& name);
	void setMatchHistory(const std::vector<std::pair<int, int>>& matchHistory);
	void setHistoryAverage(float historyAverage);

private:
	uint32_t m_id;
	std::string m_name;
	std::vector<std::pair<int, int>>m_matchHistory;
	float m_historyAverage;
};

