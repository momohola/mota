#pragma once

class Position
{
public:
	Position(int x=0,int y=0);
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
private:
	int m_X;
	int m_Y;
};
