#include "pch.h"
#include "Point.h"

point::point()
{
	x = y = 0;
}

point::point(int x1, int y1)
{
	x = x1;
	y = y1;
}

std::string point::ToString() const
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

bool point::operator==(const point& p) const {
	return x == p.x && y == p.y;
}

bool point::operator!=(const point& right) const
{
	return x != right.x || y != right.y;
}

point point::operator+(const point& right) const
{
	point temp = { x + right.x, y + right.y };
	return temp;
}

point point::operator*(const int& right) const
{
	point temp = { x * right, y * right };
	return temp;
}

