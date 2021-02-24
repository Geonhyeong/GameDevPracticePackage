#pragma once
#include "Game2D.h"

namespace jm
{
	class Window
	{
	protected:
		RGB window_color;
		float window_angle = 0.0f;
		float time = 0.0f;

	public:
		Window()
			: window_color(Colors::skyblue)
		{}

		void setWindowColor(const RGB &_window_color)
		{
			window_color = _window_color;
		}

		void setWindowAngle(const float &_window_angle)
		{
			window_angle = _window_angle;
		}

		void drawWindow(const float &dt)
		{
			rotate(window_angle * time);
			drawFilledBox(window_color, 0.1f, 0.1f);
			drawWiredBox(Colors::gray, 0.1f, 0.1f);
			drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
			drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });
			time += dt;
		}

		void drawCircleWindow()
		{
			//rotate(window_angle * time);		// 동그란 창문은 회전이 필요없다.
			drawFilledCircle(window_color, 0.05f);
			drawWiredCircle(Colors::gray, 0.05f);
			drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
			drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });
		}
	};

	class House : public Window
	{
	private:
		RGB roof_color;
		RGB wall_color;
		vec2 pos;
		float angle = 0.0f;
		float time = 0.0f;

	public:
		House()
			: pos(0.0f, 0.0f), roof_color(Colors::red), wall_color(Colors::yellow)
		{}

		void setPos(const vec2 &_pos)
		{
			pos = _pos;
		}
		void setRoofColor(const RGB &_roof_color)
		{
			roof_color = _roof_color;
		}
		void setWallColor(const RGB &_wall_color)
		{
			wall_color = _wall_color;
		}
		void setAngle(const float &_angle)
		{
			angle = _angle;
		}

		void draw(const float &dt, const bool &_isWindowCircle = false)
		{
			beginTransformation();
			{
				translate(pos);
				rotate(angle * time);

				// wall
				drawFilledBox(wall_color, 0.2f, 0.2f);

				// roof
				drawFilledTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				drawWiredTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

				// window
				if (_isWindowCircle)	// 동그란 창문
					drawCircleWindow();
				else
					drawWindow(dt);
			}
			endTransformation();

			time += dt;
		}
	};

	class HouseExample : public Game2D
	{
	public:
		House left_house, center_house, right_house;

	public:
		HouseExample()
		{}

		void update() override
		{
			// draw a house
			left_house.setPos({ -0.5f, 0.0f });
			center_house.setPos({ 0.0f, 0.0f });
			right_house.setPos({ 0.5f, 0.0f });

			left_house.setAngle(30.0f);
			center_house.setWindowAngle(60.0f);
			right_house.setWindowColor(Colors::silver);

			left_house.setRoofColor(Colors::blue);

			left_house.draw(getTimeStep());
			center_house.draw(getTimeStep());
			right_house.draw(getTimeStep(), true);
		}
	};
}