import user;
import game;
import<iostream>;
import<vector>;


int main()
{
	using namespace user;
	using namespace game;
	std::vector<std::pair<uint32_t, int>> vect;
	vect.push_back(std::make_pair(1, 200));
	vect.push_back(std::make_pair(2, 400));
	vect.push_back(std::make_pair(3, 250));
	vect.push_back(std::make_pair(4, 500));
	User a = User(1, "Andrei", vect, 0);
	a.setHistoryAverage(a.getMatchHistory());
	std::cout<<a;
	Game b = Game();
	b.FileRead();
	std::cout << b.selectRandomWord(b.getWords());
}