export module subround;
import game;
import round;
import user;

namespace subround {
	export class Subround : public round::Round {
    private:
        user::User m_painter;
        std::vector<user::User>m_guessers;

    public:

        Subround();

        Subround(const user::User& m_painter, const std::vector<user::User>& m_guessers);
	};
}