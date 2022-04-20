#include "Position.h"

int Position::GetX()
{
	return m_X;
}

int Position::GetY()
{
	return m_Y;
}

Position::Position(int x, int y)
{
	m_X = x;
	m_Y = y;
}

void Position::SetX(int x)
{
	m_X = x;
}

void Position::SetY(int y)
{
	m_Y = y;
}


