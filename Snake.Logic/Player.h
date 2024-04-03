#pragma once
#include "Point.h"
#include <vector>

class Player
{
private:

	point head;
	point direction;
	point lastDirection;
	int length;
	std::vector<point> segments;

public:
	Player();
	Player(int, int, int, int, int);

	point Head();
	point Direction();
	void setDirection(point d);
	int Length();
	void setLocation(int, int);

	std::vector<point> TailSegments();

	void Step();
	void AteFood();
};

