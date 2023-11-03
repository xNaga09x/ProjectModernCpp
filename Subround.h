#pragma once
import user;
import <vector>;
import round;
class Subround :
    public Round
{
private:
    user::User m_painter;
    std::vector<user::User>m_guessers;

public:

    Subround();

    Subround(const user::User& m_painter, const std::vector<user::User>& m_guessers);
};

