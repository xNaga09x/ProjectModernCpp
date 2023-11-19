module user;
import <format>;

using gartic::User;


User::User()
{
}

User::User(const uint32_t& id, const std::string name, const std::vector<std::pair<uint32_t, int>>& matchHistory, const float historyAverage)
	: m_id(id)
	, m_name(name)
	, m_matchHistory(matchHistory)
	, m_historyAverage(historyAverage)

{
}

User::User(const uint32_t& id, const std::string name, const float historyAverage)
	: m_id(id), 
	m_name(name), 
	m_historyAverage(historyAverage)
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

std::vector<std::pair<uint32_t, int>> User::getMatchHistory() const
{
	return m_matchHistory;
}

float User::getHistoryAverage() const
{
	return m_historyAverage;
}

bool gartic::User::getGuessed() const
{
	return this->m_guessed;
}

void gartic::User::setGuessed()
{
	this->m_guessed = true;
}

void User::setId(const uint32_t& id)
{
	m_id = id;
}

void User::setName(const std::string& name)
{
	m_name = name;
}

void User::setMatchHistory(const std::vector<std::pair<uint32_t, int>>& matchHistory)
{
	m_matchHistory = matchHistory;
}

void gartic::User::setHistoryAverage(const float& historyAverage)
{
	//if (historyAverage < 0.0f) {
	//	calculateHistoryAverage();
	//}
	//else {
	//	m_historyAverage = historyAverage;
	//}
	m_historyAverage = historyAverage;
}

void gartic::User::calculateHistoryAverage()
{
		int size = int(this->getMatchHistory().size());
	float sum = 0;
	for (std::pair<uint32_t, int> match : getMatchHistory())
		sum += match.second;
	m_historyAverage = sum / size;
}



//void User::setHistoryAverage(const std::vector<std::pair<uint32_t, int>>& matchHistory)
//{
//	int size = int(this->getMatchHistory().size());
//	float sum = 0;
//	for (std::pair<uint32_t, int> match : getMatchHistory())
//		sum += match.second;
//	m_historyAverage = sum / size;
//}

bool User::validateName(const std::string& name)
{
	std::regex pattern("^(?=.*[a-zA-Z])(?=.*[0-9]).+$");
	if (std::regex_match(name, pattern))
	{
		return true;
	}
	else
	{
		std::cout << "The Name " << name << " is not valid!";
		return false;
	}
	return true;  // Adaug? aceast? linie pentru a trata cazul în care numele este valid.
}

User& User::operator=(const User& other)
{
	if (this == &other)
	{
		return*this;
	}
	m_id = other.m_id;
	m_name = other.m_name;
	m_matchHistory = other.m_matchHistory;
	m_historyAverage = other.m_historyAverage;
	return *this;
}

User::User(User&& other) noexcept
{
	m_id = other.m_id;
	m_name = std::move(other.m_name);
	m_matchHistory = std::move(other.m_matchHistory);
	m_historyAverage = other.m_historyAverage;
}

User::User(const User& other) noexcept
{
	*this = other;
}

User& User::operator=(User&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}
	m_id = other.m_id;
	m_name = std::move(other.m_name);
	m_matchHistory = std::move(other.m_matchHistory);
	m_historyAverage = other.m_historyAverage;
	return *this;
}

std::ostream& gartic::operator<<(std::ostream& os, const User& user)
{
	os << "ID:" << user.getId() << "\nName:" << user.getName() << "\nMatch History:\n";
	os << "Match ID    Match Score\n";
	for (std::pair<uint32_t, int> match : user.getMatchHistory())
	{
		os << "   " << match.first << "             " << match.second << "\n";
	}
	os << "History Average:" << user.getHistoryAverage() << "\n";
	return os;
}