export module user;
import<iostream>;
import <string>;
import <vector>;
import <regex>;
namespace gartic
{
	export class User
	{
	public:
		User();
		User(const uint32_t& id, const std::string name, const std::vector<std::pair<uint32_t, int>>& matchHistory, const float historyAverage);

		int32_t getId() const;
		std::string getName() const;
		std::vector<std::pair<uint32_t, int>> getMatchHistory() const;
		float getHistoryAverage() const;
		bool getGuessed() const;

		void setGuessed();
		void setId(const uint32_t& id);
		void setName(const std::string& name);
		void setMatchHistory(const std::vector<std::pair<uint32_t, int>>& matchHistory);
		void setHistoryAverage(const std::vector<std::pair<uint32_t, int>>& matchHistory);

		bool validateName(const std::string& name);

		User& operator=(const User& other);//copy assigmnent
		User(User&& other) noexcept;//move constructor
		User(const User& other) noexcept;//copy constructor
		User& operator=(User&& other) noexcept;//move assigment operatorz
		/*friend std::ostream& operator<<(std::ostream& os, const User& user);*/
	private:
		uint32_t m_id;
		std::string m_name;
		std::vector<std::pair<uint32_t, int>>m_matchHistory;
		float m_historyAverage;
		bool m_guessed = false;
	};


	export std::ostream& operator<<(std::ostream& os, const User& user);
	

}