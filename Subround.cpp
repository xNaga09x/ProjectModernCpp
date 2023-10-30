#include "Subround.h"

Subround::Subround()
{

}

Subround::Subround(const user::User& painter, const std::vector<user::User>& guessers)
	: m_painter(painter), m_guessers(guessers)
{
}
