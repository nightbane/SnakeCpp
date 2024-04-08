#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <chrono>
#include "../Snake.Logic/SnakeGame.h"
#include <iostream>

using namespace std;

#define key_UP 72
#define key_DOWN 80
#define key_LEFT 75
#define key_RIGHT 77
#define key_ESCAPE 27

//keypress keeps track of what the last pressed key. It is global, but could be made local.
int keypress = 0;

void runGame();
Move keyPressed();
void gotoxy(int x, int y);
void setcolor(WORD color);
void txtPlot(point item, unsigned char Color);

//Add function declarations here


int main() {

    //Uncomment the next four lines to see console color options 0-255
    /*
    for (int i = 0; i < 255; i++) {
        setcolor(i);
        _cprintf("Color option: %i. Hello, world.\n", i);
    }
    //*/

    runGame();
    return 0;
}

void runGame() {

    SnakeGame game;

    chrono::time_point<chrono::system_clock> runTime;
    chrono::time_point<chrono::system_clock> currentTime;
    runTime = std::chrono::system_clock::now();
    Sleep(300);

    //Loop to start drawing and playing.
    while (game.isRunning()) {

        Move direction = keyPressed();
        game.setDirection(direction);

        currentTime = chrono::system_clock::now();

        double elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - runTime).count();
        if (elapsedTime > 0.3 * 1000) {
            runTime = chrono::system_clock::now();
            game.advanceTurn();

            txtPlot(game.player.Head(), 31);
            point removed = game.player.TailRemoved();
            if (removed != point( - 1, -1 )) {
                txtPlot(removed, 15);
            }
            txtPlot(game.Food(), 100);

            setcolor(15);
            gotoxy(1, 21);
            _cprintf("Length: %i", game.player.Length());



        }

        Sleep(10);
    }
}

//Put function definitions here.



//These are helper funcitons to capture keyboard and draw to the console.
Move keyPressed() {
    Move direction = Move::NONE;
    if (_kbhit())
    {
        keypress = _getch();
        switch (keypress)
        {
        case key_LEFT:
            direction = Move::LEFT;
            break;

        case key_RIGHT:
            direction = Move::RIGHT;
            break;

        case key_UP:
            direction = Move::UP;
            break;

        case key_DOWN:
            direction = Move::DOWN;
            break;

        default:

            break;
        }
    }
    return direction;
}

void txtPlot(point item, unsigned char Color)
{
    setcolor(Color);
    gotoxy(item.x * 2, item.y);
    _cprintf("  ");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return;
}