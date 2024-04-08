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
	point removed;

public:
	Player();
	Player(int, int, int, int, int);

	point Head();
	void setLocation(int, int);
	point Direction();
	void setDirection(point d);
	int Length();
	void setLength(int l);

	std::vector<point> TailSegments();
	void setTailSegments(std::vector<point>);
	point TailRemoved();

	void Step();
	void AteFood();
};

