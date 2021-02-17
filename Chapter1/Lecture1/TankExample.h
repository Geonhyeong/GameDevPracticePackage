#pragma once

#include "Game2D.h"
#include <vector>

namespace jm
{
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(1.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f * direction.x, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f * direction.x, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		const float radius = 0.02f;

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, radius, 8);
			drawWiredRegularConvexPolygon(Colors::gray, radius, 8);
			endTransformation();
		}

		void update(const float &dt)
		{
			center += velocity * dt;
		}

		bool isOnDisplay(const int &width, const int &height)
		{
			const float aspect_ratio = (float)width / (float)height;
			if (std::abs(this->center.x) > aspect_ratio + radius || std::abs(this->center.y) > 1.0f + radius)
			{
				std::cout << "bullet is out of display" << std::endl;
				return false;
			}
			return true;
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		//MyBullet *bullet = nullptr;
		std::vector<MyBullet *> bullets;
		const int width = 1024;
		const int height = 768;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		~TankExample()
		{
			for (auto &bullet : bullets)
			{
				if (bullet != nullptr) delete bullet;
			}
		}

		void update() override
		{
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))
			{
				tank.center.x -= 0.5f * getTimeStep();
				tank.direction.x = -1.0f;
			}
			if (isKeyPressed(GLFW_KEY_RIGHT))
			{
				tank.center.x += 0.5f * getTimeStep();
				tank.direction.x = 1.0f;
			}
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				MyBullet *bullet = new MyBullet;
				bullet->center = tank.center;
				bullet->center.x += 0.2f * tank.direction.x;
				bullet->center.y += 0.1f;
				bullet->velocity = vec2(2.0f * tank.direction.x, 0.0f);
				bullets.push_back(bullet);
			}

			// rendering
			tank.draw();

			auto iterator = 0;
			for (auto &bullet : bullets)
			{
				bullet->update(getTimeStep());
				bullet->draw();
				if (!bullet->isOnDisplay(width, height))
				{
					delete bullet;
					bullets.erase(bullets.begin() + iterator);
				}
				iterator++;
			}
		}
	};
}