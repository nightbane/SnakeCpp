#pragma once
#include "Point.h"
#include "Player.h"
#include "Move.h"

class SnakeGame
{
private:
	const int SIZE = 19;
	
	bool running = true;
	point food;
	
	void moveFood();
	int getRandomBoard();

public:
	Player player;

	SnakeGame();

	bool isRunning();

	void advanceTurn();
	void setDirection(Move m);
	
	void setFood(int, int);
	point Food();
};

