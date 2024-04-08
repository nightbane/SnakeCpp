#include "pch.h"
#include "CppUnitTest.h"
#include "../Snake.Logic/SnakeGame.h"
#include <vector>
#include "../Snake.Logic/Move.h"
#include "PointCompare.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SnakeTest
{
	TEST_CLASS(SnakeTest)
	{
	public:
		
		TEST_METHOD(GameInitilize)
		{
			SnakeGame game;
			point expectedPosition = { 0,10 };
			point expectedDirection = { 1,0 };
			int expectedLength = 5;
			Assert::AreEqual(expectedPosition, game.player.Head());
			Assert::AreEqual(expectedDirection, game.player.Direction());
			Assert::AreEqual(expectedLength, game.player.Length());
		}

		TEST_METHOD(GameOneMove)
		{
			SnakeGame game;
			point loc = { 1,10 };
			game.advanceTurn();
			Assert::AreEqual(loc, game.player.Head());
		}

		TEST_METHOD(GameStartsWityTailEmpty)
		{
			SnakeGame game;
			int expectedSegmentCount = 0;

			std::vector<point> t = game.player.TailSegments();
			int length = t.size();
			Assert::AreEqual(expectedSegmentCount, length);
		}

		TEST_METHOD(TailGrowsAsTurnAdvances)
		{
			SnakeGame game;
			int expectedSegmentCount = 1;

			game.advanceTurn();

			std::vector<point> t = game.player.TailSegments();
			int length = t.size();
			Assert::AreEqual(expectedSegmentCount, length);
		}

		TEST_METHOD(TailSegmentsIsOldHead)
		{
			SnakeGame game;
			point expectedSegment = game.player.Head();

			game.advanceTurn();

			std::vector<point> t = game.player.TailSegments();
			Assert::AreEqual(expectedSegment, t[0]);
		}

		TEST_METHOD(TailSegmentAddedAtEnd)
		{
			SnakeGame game;
			game.advanceTurn();
			point expectedSegment = game.player.Head();
			
			game.advanceTurn();

			std::vector<point> t = game.player.TailSegments();
			Assert::AreEqual(expectedSegment, t[1]);
		}

		TEST_METHOD(TailGrowsUntilEqualToLength)
		{
			SnakeGame game;
			int expectedSegmentCount = 5;

			for (int i = 0; i < 6; i++) {
				game.advanceTurn();
			}

			std::vector<point> t = game.player.TailSegments();
			int length = t.size();
			Assert::AreEqual(expectedSegmentCount, length);
		}

		TEST_METHOD(TailSegmentRemovesOldestFirst)
		{
			SnakeGame game;
			point expectedSegment = game.player.Head();

			for (int i = 0; i < 6; i++) {
				game.advanceTurn();
			}

			std::vector<point> t = game.player.TailSegments();
			Assert::AreNotEqual(expectedSegment, t[0]);
		}

		TEST_METHOD(TailOldestSegmentIndcatedForWipe)
		{
			SnakeGame game;
			point expectedSegment = game.player.Head();

			for (int i = 0; i < 6; i++) {
				game.advanceTurn();
			}

			point t = game.player.TailRemoved();
			Assert::AreEqual(expectedSegment, t);
		}

		TEST_METHOD(SnakeGrowsWhenItEats)
		{
			SnakeGame game;
			int expectedLength = game.player.Length() + 1;
			game.setFood(1, 10);

			game.advanceTurn();

			Assert::AreEqual(expectedLength, game.player.Length());
		}

		TEST_METHOD(FoodMovesAfterEaten)
		{
			SnakeGame game;
			game.setFood(1, 10);
			point oldFood = { 1,10 };

			game.advanceTurn();

			Assert::AreNotEqual(oldFood, game.Food());
		}

		TEST_METHOD(MovesLeft)
		{
			SnakeGame game;
			point loc = { 0,10 };
			
			loc = loc + point(-1, 0);
			game.setDirection(Move::LEFT);
			game.advanceTurn();
			Assert::AreEqual(loc, game.player.Head());
		}

		TEST_METHOD(MovesDown)
		{
			SnakeGame game;
			game.player.setLocation(10, 10);

			game.setDirection(Move::DOWN);
			point loc = game.player.Head() + point(0, 1);
			game.advanceTurn();

			Assert::AreEqual(loc, game.player.Head());
		}

		TEST_METHOD(DiesWhenLeaveBoardRight)
		{
			SnakeGame game;
			game.player.setLocation(19, 10);
			game.setDirection(Move::RIGHT);

			game.advanceTurn();

			Assert::IsFalse(game.isRunning());
		}

		TEST_METHOD(DiesWhenLeaveBoardLeft)
		{
			SnakeGame game;
			game.player.setLocation(0, 10);
			game.setDirection(Move::LEFT);

			game.advanceTurn();

			Assert::IsFalse(game.isRunning());
		}

		TEST_METHOD(DiesWhenLeaveBoardDown)
		{
			SnakeGame game;
			game.player.setLocation(10, 19);
			game.setDirection(Move::DOWN);

			game.advanceTurn();

			Assert::IsFalse(game.isRunning());
		}

		TEST_METHOD(SnakeDoesntMoveAfterDieing)
		{
			SnakeGame game;
			game.player.setLocation(0, 10);
			game.setDirection(Move::LEFT);
			game.advanceTurn();
			point expectedLocation = game.player.Head();

			game.setDirection(Move::DOWN);
			game.advanceTurn();

			Assert::AreEqual(expectedLocation, game.player.Head());
		}

		TEST_METHOD(DiesWhenBitesTail)
		{
			SnakeGame game;
			game.player.setLocation(10, 10);
			
			game.setDirection(Move::RIGHT);
			game.advanceTurn();
			game.setDirection(Move::DOWN);
			game.advanceTurn();
			game.setDirection(Move::LEFT);
			game.advanceTurn();
			game.setDirection(Move::UP);
			game.advanceTurn();

			Assert::IsFalse(game.isRunning());
		}

		TEST_METHOD(SnakeCantDoubleBack)
		{
			point expected = { 10, 8 };
			SnakeGame game;
			game.player.setLocation(10, 10);
			game.setDirection(Move::UP);
			game.advanceTurn();
			
			game.setDirection(Move::DOWN);
			game.advanceTurn();

			point actual = game.player.Head();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(SnakeCanDoubleBackBeforeTick)
		{
			point expected = { 11, 9 };
			SnakeGame game;
			game.player.setLocation(10, 10);
			game.setDirection(Move::UP);
			game.advanceTurn();

			game.setDirection(Move::LEFT);
			game.setDirection(Move::RIGHT);
			game.advanceTurn();

			point actual = game.player.Head();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(FoodCantAppearOnTail)
		{
			SnakeGame game;
			game.player.setLocation(0, 19);
			game.setDirection(Move::RIGHT);
			game.setFood(1, 19);
			game.player.setLength(380);

			std::vector<point> tail;
			for (int y = 18; y >= 0; y--) {
				if (y % 2 == 1) {
					for (int x1 = 0; x1 < 20;x1++) {
						point p = { x1,y };
						tail.push_back(p);
					}
				}
				else
				{
					for (int x2 = 19; x2 >= 0;x2--) {
						point p = { x2,y };
						tail.push_back(p);
					}
				}

			}

			game.player.setTailSegments(tail);

			game.advanceTurn();

			point food = game.Food();
			Assert::AreEqual(381, game.player.Length());
			Assert::AreEqual(19, food.y);
		}
		


		//Input buffering

	};
}

