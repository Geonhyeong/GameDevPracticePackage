#pragma once
#include "Game2D.h"
#include <math.h>

namespace jm
{
	class Gun
	{
	private:
		float degree = 0.0f;
		const float PI = 3.14159265f;
	public:
		void draw(const vec2 &mouse_pos)
		{
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
	};

	class Bullet
	{
	};

	class MouseExample : public Game2D
	{
	private:
		float time = 0.0f;
		Gun gun;

	public:
		MouseExample()
		{}

		~MouseExample()
		{}

		void update() override
		{
			const vec2 mouse_pos = getCursorPos(true);

			gun.draw(mouse_pos);

			//time += this->getTimeStep();
		}
	};
}