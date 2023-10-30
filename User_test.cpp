import user;
import<iostream>;
import<vector>;

int main()
{
	using namespace user;
	std::vector<std::pair<int, int>> vect;
	vect.push_back(std::make_pair(1, 200));
	vect.push_back(std::make_pair(2, 400));
	vect.push_back(std::make_pair(3, 250));
	vect.push_back(std::make_pair(4, 500));
	User a = User(1, "Andrei", vect, 0);
	a.setHistoryAverage(a.getMatchHistory());
	a.setId(2);
	std::cout<<a;
}