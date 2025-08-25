#include "CppUnitTest.h"
#include "../SpaceShooter/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(PlayerTest)
	{
	public:
		//Clamp player to viewport
		TEST_METHOD(LimitToScreen_ClampRight)
		{
			Player player;
			player.setPosition({ 300, 100 }); // izvan desne granice
			player.limitToScreen(128, 32);
			Assert::AreEqual<short>(115, player.getPosition().x); // 128 - 13
		}

		TEST_METHOD(LimitToScreen_ClampLeft)
		{
			Player player;
			player.setPosition({ -100, 100 }); // izvan lijeve granice
			player.limitToScreen(128, 32);
			Assert::AreEqual<short>(1, player.getPosition().x); // min x = 1;
  		}
	};
}
