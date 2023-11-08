#pragma once
#include <iostream>
#include <vector>
#include <regex>

class User
{
public:
	User();
	User(const uint32_t& id, const std::string name, const std::vector<std::pair<uint32_t, int>>& matchHistory, const float historyAverage);

	int32_t getId() const;
	std::string getName() const;
	std::vector<std::pair<uint32_t, int>> getMatchHistory() const;
	float getHistoryAverage() const;

	void setId(const uint32_t& id);
	void setName(const std::string& name);
	void setMatchHistory(const std::vector<std::pair<uint32_t, int>>& matchHistory);
	void setHistoryAverage(const std::vector<std::pair<uint32_t, int>>& matchHistory);

	bool validateName(const std::string& name);

	User& operator=(const User& other);//copy assigmnent
	User(User&& other) noexcept;//move constructor
	User& operator=(User&& other) noexcept;//move assigment operator
private:
	uint32_t m_id;
	std::string m_name;
	std::vector<std::pair<uint32_t, int>>m_matchHistory;
	float m_historyAverage;
};

