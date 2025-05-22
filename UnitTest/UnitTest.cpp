#include "CppUnitTest.h"
#include "../SpaceShooter/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(PlayerTest)
	{
	public:
		TEST_METHOD(LimitToScreen_ClampRight)
		{
			Player player;
			player.setPosition({ 300, 100 }); // izvan desne granice
			player.limitToScreen(128, 32);
			Assert::AreEqual<short>(115, player.getPosition().x); // 800 - 13
		}
	};
}
