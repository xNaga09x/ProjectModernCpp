#include "User.h"
#include<regex>
#include<iostream>
User::User()
{
}


User::User(const uint32_t& id, const std::string name, const std::vector<std::pair<int, int>>& matchHistory, const float historyAverage)
	:m_id(id)
	,m_name(name)
	,m_matchHistory(matchHistory)
	,m_historyAverage(historyAverage)
{

}

int32_t User::getId() const
{
	return m_id;
}

std::string User::getName() const
{
	return m_name;
}

std::vector<std::pair<int, int>> User::getMatchHistory() const
{
	return m_matchHistory;
}

float User::getHistoryAverage() const
{
	return m_historyAverage;
}

void User::setId(const uint32_t id)
{
	m_id = id;
}

void User::setName(const std::string& name)
{
	m_name = name;
}

void User::setMatchHistory(const std::vector<std::pair<int, int>>& matchHistory)
{
	m_matchHistory;
}

void User::setHistoryAverage(float historyAverage)
{
	m_historyAverage = historyAverage;
}

bool User::validateName(const std::string& name)
{
	std::regex pattern("^(?=.*[a-zA-Z])(?=.*[0-9]).+$");
	if (std::regex_match(name, pattern))
	{
		return true;
	}
	else
	{
		std::cout << "The NameUser " << name << " is not valid!";
		return false;
	}
}
