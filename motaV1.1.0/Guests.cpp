#include "Guests.h"

std::string Guests::getId() const
{
    return m_Id;
}

void Guests::setId(std::string mId)
{
    m_Id = mId;
}

std::string Guests::getComputer() const
{
    return m_Computer;
}

void Guests::setComputer(std::string mComputer)
{
    m_Computer = mComputer;
}

int Guests::getX() const
{
    return m_X;
}

void Guests::setX(int mX)
{
    m_X = mX;
}

int Guests::getY() const
{
    return m_Y;
}

void Guests::setY(int mY)
{
    m_Y = mY;
}

