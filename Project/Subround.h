#pragma once
#include "Round.h"
class Subround :
    public Round
{
private:
    User m_painter;
    std::vector<User>m_guessers;

public:

    Subround();

    Subround(const User& m_painter, const std::vector<User>& m_guessers);
};

