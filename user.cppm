export module user;
import <iostream>;
import <vector>;

namespace user
{
	export class User
	{
	public:
		User();
		User(const uint32_t& id, const std::string name, const std::vector<std::pair<int, int>>& matchHistory, const float historyAverage);

		int32_t getId() const;
		std::string getName() const;
		std::vector<std::pair<int, int>> getMatchHistory() const;
		float getHistoryAverage() const;

		void setId(const uint32_t& id);
		void setName(const std::string& name);
		void setMatchHistory(const std::vector<std::pair<int, int>>& matchHistory);
		void setHistoryAverage(const std::vector<std::pair<int, int>>& matchHistory);

		bool validateName(const std::string& name);

	private:
		uint32_t m_id;
		std::string m_name;
		std::vector<std::pair<int, int>>m_matchHistory;
		float m_historyAverage;
	};
	export std::ostream& operator<<(std::ostream& os, const User& user);
	std::ostream& operator<<(std::ostream& os, const User& user)
	{
		os << "ID:" << user.getId() << "\nName:" << user.getName() << "\nMatch History:\n";
		os << "Match ID    Match Score\n";
		for (int i = 0; i < user.getMatchHistory().size(); i++)
		{
			os << "   "<<user.getMatchHistory()[i].first << "             " << user.getMatchHistory()[i].second << "\n";
		}
		os << "History Average:" << user.getHistoryAverage() << "\n";
		return os;
	}
}