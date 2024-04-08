#include "pch.h"
#include <ctime>
#include "SnakeGame.h"

void SnakeGame::moveFood()
{
    point p = { getRandomBoard(), getRandomBoard() };
    
    while (p == food) {
        p = { getRandomBoard(), getRandomBoard() };
    }



    food = p;
}

int SnakeGame::getRandomBoard()
{
    int loc = (rand() % (19 - 0 + 1)) + 0;
    return loc;
}

SnakeGame::SnakeGame()
{
    srand(time(0));

    Player temp(0, 10, 1, 0, 5);
    player = temp;
    moveFood();
}

bool SnakeGame::isRunning()
{
    return running;
}



void SnakeGame::advanceTurn()
{
    if (!running) return;

    player.Step();
    if (player.Head() == food) {
        player.AteFood();
        moveFood();
    }
    
    point head = player.Head();
    if (head.x > SnakeGame::SIZE || head.x < 0 ||
        head.y > SnakeGame::SIZE || head.y < 0) {
        running = false;
        return;
    }

    std::vector<point> segements = player.TailSegments();
    for (int i = 0; i < segements.size(); i++) {
        if (head == segements[i]) {
            running = false;
            return;
        }
    }
}

void SnakeGame::setDirection(Move m)
{
    switch (m)
    {
    case Move::UP:
        player.setDirection({ 0,-1 });
        break;
    case Move::DOWN:
        player.setDirection({ 0,1 });
        break;
    case Move::LEFT:
        player.setDirection({ -1,0 });
        break;
    case Move::RIGHT:
        player.setDirection({ 1,0 });
        break;
    default:
        break;
    }
}

void SnakeGame::setFood(int x, int y)
{
    food = { x, y };
}

point SnakeGame::Food()
{
    return food;
}


