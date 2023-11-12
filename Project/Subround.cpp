module subround;
import user;
using gartic::Subround;

Subround::Subround()
{

}

Subround::Subround(const gartic::User& painter, const std::vector<gartic::User>& guessers)
	: m_painter(painter), m_guessers(guessers)
{
}

const gartic::User& Subround::getPainter() const
{
	return m_painter;
}

void Subround::setPainter(const gartic::User& painter)
{
	m_painter = painter;
}

const std::vector<gartic::User>& Subround::getGuessers() const
{
	return m_guessers;
}

void Subround::setGuessers(const std::vector<gartic::User>& guessers)
{
	m_guessers = guessers;
}

Subround& Subround::operator=(const Subround& other)
{
	if (this == &other) {
		return *this;
	}
	m_painter = other.m_painter;
	m_guessers = other.m_guessers;
	return *this;
}

Subround::Subround(Subround&& other) noexcept
{
	m_painter = std::move(other.m_painter);
	m_guessers = std::move(other.m_guessers);
}

Subround& Subround::operator=(Subround&& other) noexcept
{
	if (this == &other) {
		return *this;
	}
	m_painter = std::move(other.m_painter);
	m_guessers = std::move(other.m_guessers);
	return *this;
}