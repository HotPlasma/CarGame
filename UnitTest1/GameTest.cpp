#include "stdafx.h"
#include "CppUnitTest.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"

////////////////////////////////////////////////////////////
//
// PLEASE USE DEBUG MODE FOR RUNNING
// UNIT TESTS!!
//
////////////////////////////////////////////////////////////

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Game game;

namespace GameTest
{		
	TEST_CLASS(GameTestClass)
	{
	public:
		TEST_METHOD(TestCarGetPosition)
		{
			// Valid
			Assert::AreEqual(game.getCarPos().x, 2075, 1);
			Assert::AreEqual(game.getCarPos().y, 65, 1);

			// Invalid
			Assert::AreNotEqual(game.getCarPos().x, 5000, 0);
			Assert::AreNotEqual(game.getCarPos().y, 200, 0);
		}
		TEST_METHOD(TestRPMGetPosition)
		{
			// Valid
			Assert::AreEqual(game.getRPMCounterPos().x, 721, 1);
			Assert::AreEqual(game.getRPMCounterPos().y, 518, 1);

			// Invalid
			Assert::AreNotEqual(game.getCarPos().x, 5000, 1);
			Assert::AreNotEqual(game.getCarPos().y, 200, 1);
		}
	};
}