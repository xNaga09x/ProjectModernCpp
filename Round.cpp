module round;

using round::Round;

Round::Round()
{

}


Round::Round(int noRounds)
	:m_noRounds(noRounds)
{
}

round::Round::Round(const Round& other)
	: m_noRounds(other.m_noRounds)
{
}

int round::Round::getNoRounds() const
{
    return m_noRounds;

}

void round::Round::setNoRounds(int noRounds)
{
    m_noRounds = noRounds;
}

round::Round::Round(Round&& other) noexcept
	: m_noRounds(other.m_noRounds)
{
	other.m_noRounds = 0;
}

Round& round::Round::operator=(Round&& other) noexcept
{
    if(this != &other) {
        m_noRounds = other.m_noRounds;
        other.m_noRounds = 0;
    }
    return *this;
}

Round& round::Round::operator=(const Round& other)
{
    if (this != &other) {
        m_noRounds = other.m_noRounds;
    }
    return *this;
}





