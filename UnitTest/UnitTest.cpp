#include "CppUnitTest.h"
#include "../SpaceShooter/Player.h"
#include "../SpaceShooter/Bullet.h"
#include "../SpaceShooter/Enemy.h"

#include <memory>
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(PlayerTest)
	{
	public:
		//Player limitToScreen tests
		//**************************************************************
		TEST_METHOD(LimitToScreen_ClampRight)
		{
			Player player;
			player.init({ 300, 100 }, 10.0f, 128, 32);
			player.limitToScreen();
			Assert::AreEqual<short>(128 - 25, static_cast<short>(player.getPosition().x)); // 128 - 25 = 103
		}

		TEST_METHOD(LimitToScreen_ClampLeft)
		{
			Player player;
			player.init({ -100, 100 }, 10.0f, 128, 32);
			player.limitToScreen();
			Assert::AreEqual<short>(2, static_cast<short>(player.getPosition().x)); // min x = 2
		}

		TEST_METHOD(LimitToScreen_ClampTop)
		{
			Player player;
			player.init({ 50, -100 }, 10.0f, 128, 32);
			player.limitToScreen();
			Assert::AreEqual<short>(3, static_cast<short>(player.getPosition().y)); // min y = 3
		}
		TEST_METHOD(LimitToScreen_ClampBottom)
		{
			Player player;
			player.init({ 50, 100 }, 10.0f, 128, 32);
			player.limitToScreen();
			Assert::AreEqual<short>(32 - 5, static_cast<short>(player.getPosition().y)); // 32 - 5 = 27
		}
		//**************************************************************
	};

    TEST_CLASS(BulletTest)
    {
    public:

		//Bullet update test
        TEST_METHOD(Update_MovesBullet)
        {
            Position pos{ 50, 50 };
            Direction dir{ 1, 0 };
            float damage = 10.0f;
            float speed = 200.0f;
            Bullet bullet(pos, dir, damage, speed);

            bullet.update();

            float expectedX = 50.0f + (1 * 200.0f);
            float expectedY = 50.0f;
            Assert::AreEqual(expectedX, bullet.getPosition().x, 0.001f);
            Assert::AreEqual(expectedY, bullet.getPosition().y, 0.001f);
            Assert::AreEqual(99, bullet.getLifeTime());
        }
    };

}
