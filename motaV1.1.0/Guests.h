#pragma once
#include <string>

class Guests
{
private:
	std::string m_Id;
	std::string m_Computer;
	int m_X;
	int m_Y;
public:
    std::string getId() const;
    void setId(std::string mId);

    std::string getComputer() const;
    void setComputer(std::string mComputer);

    int getX() const;
    void setX(int mX);

    int getY() const;
    void setY(int mY);

};




