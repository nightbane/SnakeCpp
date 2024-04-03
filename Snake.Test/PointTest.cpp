#include "pch.h"
#include "CppUnitTest.h"
#include "../Snake.Logic/SnakeGame.h"
#include <vector>
#include "../Snake.Logic/Move.h"
#include "PointCompare.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SnakeTest
{
	TEST_CLASS(PointTest)
	{
	public:

		TEST_METHOD(AddPointsTogether)
		{
			point expected = { 4,6 };

			point p1 = { 1,2 };
			point p2 = { 3,4 };
			point actual = p1 + p2;

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(OverloadEqual)
		{
			point p1 = { 1,2 };
			point p2 = { 1,2 };

			Assert::IsTrue(p1 == p2);
		}

		TEST_METHOD(OverloadNotEqual)
		{
			point p1 = { 1,2 };
			point p2 = { 1,3 };

			Assert::IsTrue(p1 != p2);
		}

		TEST_METHOD(TestMultiply)
		{
			point expected = { -1, 2 };
			
			point p1 = { 1,-2 };
			point actual = p1 * -1;

			Assert::AreEqual(expected, actual);
		}


	};
}