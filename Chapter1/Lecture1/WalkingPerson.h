#pragma once

#include "Game2D.h"
#include <vector>

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/

	class WalkingPerson
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//float time = 0.0f;

	public:
		void draw(const float &time)
		{
			translate(center);
			// gold face
			beginTransformation();
			translate(0.0f, 0.12f);
			drawFilledCircle(Colors::gold, 0.08f);
			translate(0.05f, 0.03f);
			drawFilledCircle(Colors::white, 0.01f); // while eye

			endTransformation();

			// yellow left arm
			beginTransformation();
			rotate(sin(time * 5.0f) * -30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green left leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time * 5.0f + 3.141592f) * -30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			// red body
			beginTransformation();
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::red, 0.13f, 0.2f);
			endTransformation();

			// yellow right arm
			beginTransformation();
			rotate(sin(time * 5.0f) * 30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green right leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time * 5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			//time += this->getTimeStep();
		}

		//void shoot()
		//{
		//	translate(center);
		//	// gold face
		//	beginTransformation();
		//	translate(0.0f, 0.12f);
		//	drawFilledCircle(Colors::gold, 0.08f);
		//	translate(0.05f, 0.03f);
		//	drawFilledCircle(Colors::white, 0.01f); // while eye

		//	endTransformation();
		//}
	};

	class WalkingPersonExample : public Game2D
	{
	public:
		std::vector<WalkingPerson> myPerson;
		float time = 0.0f;

	public:
		WalkingPersonExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		~WalkingPersonExample()
		{
		}

		void update() override
		{
			for (int i = 0; i < 3; i++)
			{
				WalkingPerson person;
				person.center += vec2((float)i * 0.3, (float)i * 0.3);
				person.draw(time);
				myPerson.push_back(person);
			}

			/*if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				for (auto &person : myPerson)
				{
					person.shoot();
				}
			}*/

			time += this->getTimeStep();
		}
	};
}