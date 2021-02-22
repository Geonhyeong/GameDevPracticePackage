#pragma once
#include "Game2D.h"
#include <math.h>

namespace jm
{
	class Gun
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		float degree = 0.0f;
		const float PI = 3.14159265f;
	public:
		void draw(const vec2 &mouse_pos)
		{
			beginTransformation();
			{
				translate(center);
				degree = atanf(mouse_pos.y / mouse_pos.x) * 180 / PI;
				if (mouse_pos.x < 0) degree += 180.0f;
				//std::cout << mouse_pos.x << " " << mouse_pos.y << " " << degree << std::endl;
				rotate(degree);
				beginTransformation();
				{
					translate(-0.05f, 0.0f);
					drawFilledBox(Colors::gold, 0.1f, 0.2f);
				}
				endTransformation();
				beginTransformation();
				{
					translate(0.05f, 0.05f);
					drawFilledBox(Colors::gold, 0.3f, 0.1f);
				}
				endTransformation();
			}
			endTransformation();
		}
	};

	class Bullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		const float radius = 0.02f;
		float degree = 0.0f;

		void draw()
		{
			beginTransformation();
			rotate(degree);
			translate(center);
			drawFilledRegularConvexPolygon(Colors::gray, radius, 8);
			drawWiredRegularConvexPolygon(Colors::black, radius, 8);
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

	class MouseExample : public Game2D
	{
	private:
		float time = 0.0f;
		Gun gun;
		std::vector<Bullet *> bullets;

	public:
		MouseExample()
		{}

		~MouseExample()
		{}

		void update() override
		{
			const vec2 mouse_pos = getCursorPos(true);

			// shoot bullet to mouse cursor direction
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_1))
			{
				Bullet *bullet = new Bullet();
				bullet->center.x = 0.2f;
				bullet->center.y = 0.05f;
				bullet->degree = gun.degree;
				bullet->velocity = vec2(1.0f, 0.0f);
				bullets.push_back(bullet);
			}

			// rendering gun
			gun.draw(mouse_pos);

			// rendering bullet
			auto iterator = 0;
			for (auto &bullet : bullets)
			{
				bullet->update(getTimeStep());
				bullet->draw();
				if (!bullet->isOnDisplay(1000, 1000))
				{
					delete bullet;
					bullets.erase(bullets.begin() + iterator);
				}
				iterator++;
			}

			//time += this->getTimeStep();
		}
	};
}