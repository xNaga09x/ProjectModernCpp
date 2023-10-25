#include "User.h"

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