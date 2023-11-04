export module subround;
import game;
import round;
import user;


export class Subround {
private:
	user::User m_painter;
	std::vector<user::User>m_guessers;

public:

	Subround();

	Subround(const user::User& m_painter, const std::vector<user::User>& m_guessers);

	const user::User& getPainter() const;
	void setPainter(const user::User& painter);
	const std::vector<user::User>& getGuessers() const;
	void setGuessers(const std::vector<user::User>& guessers);

	Subround& operator=(const Subround& other);//copy assigment
	Subround(Subround&& other) noexcept;//move constructor
	Subround& operator=(Subround&& other) noexcept;//move assigment
};
