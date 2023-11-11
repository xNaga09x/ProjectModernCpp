export module subround;
import game;
import round;
import user;

namespace gartic
{
	export class Subround {
	private:
		User m_painter;
		std::vector<User>m_guessers;

	public:

		Subround();

		Subround(const User& m_painter, const std::vector<User>& m_guessers);

		const User& getPainter() const;
		void setPainter(const User& painter);
		const std::vector<User>& getGuessers() const;
		void setGuessers(const std::vector<User>& guessers);

		Subround& operator=(const Subround& other);//copy assigment
		Subround(Subround&& other) noexcept;//move constructor
		Subround& operator=(Subround&& other) noexcept;//move assigment
	};
}