#include "stdafx.h"
#include "CppUnitTest.h"
#include "..//include//Game.h"
#include <SFML/Graphics.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestgetCarPos)
		{
			Game game;
			sf::Vector2f Actual(game.getCarPos());
			sf::Vector2f Expected(200, 200);
			Assert::AreEqual(Expected, Actual, L"message", LINE_INFO());
		}

	};
}