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
	class Beam
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledBox(Colors::skyblue, 1.0f, 0.08f);
			endTransformation();
		}
	};

	class Person
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(1.0f, 0.0f);
		Beam *beam = nullptr;

		float time = 0.0f;
		bool _stand = false;

	public:
		void drawFaceAndBody()
		{
			// gold face
			beginTransformation();
			{
				translate(0.0f, 0.12f);
				drawFilledCircle(Colors::gold, 0.08f);
				translate(direction.x * 0.05f, 0.03f);
				drawFilledCircle(Colors::white, 0.01f); // while eye
			}
			endTransformation();

			// red body
			beginTransformation();
			{
				scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledBox(Colors::red, 0.13f, 0.2f);
			}
			endTransformation();
		}
		void drawLeftArm()
		{
			// yellow left arm
			beginTransformation();
			{
				if (_stand == false)
					rotate(sin(time * 5.0f) * -30.0f);					// animation!
				scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			}
			endTransformation();
		}
		void drawRightArm(bool _beam)
		{
			// yellow right arm

			if (_beam == true)
			{
				beginTransformation();
				{
					rotate(direction.x * 90.0f);
					scale(1.0f, 2.0f);
					translate(0.0f, -0.1f);
					drawFilledBox(Colors::yellow, 0.05f, 0.18f);
				}
				endTransformation();
				this->shoot();
			}
			else
			{
				if (beam != nullptr)
				{
					delete beam;
					beam = nullptr;
					std::cout << "beam is deleted" << std::endl;
				}
				beginTransformation();
				{
					if (_stand == false)
						rotate(sin(time * 5.0f) * 30.0f);					// animation!
					scale(1.0f, 2.0f);
					translate(0.0f, -0.1f);
					drawFilledBox(Colors::yellow, 0.05f, 0.18f);
				}
				endTransformation();
			}
		}
		void drawLeftLeg() {
			// green left leg
			beginTransformation();
			{
				translate(0.0f, -0.6f);
				translate(0.0f, 0.2f);
				if (_stand == false)
					rotate(sinf(time * 5.0f + 3.141592f) * -30.0f);	// animation!
				translate(0.0f, -0.2f);
				drawFilledBox(Colors::green, 0.1f, 0.4f);
			}
			endTransformation();
		}
		void drawRightLeg() {
			// green right leg
			beginTransformation();
			{
				translate(0.0f, -0.6f);
				translate(0.0f, 0.2f);
				if (_stand == false)
					rotate(sinf(time * 5.0f + 3.141592f) * 30.0f);	// animation!
				translate(0.0f, -0.2f);
				drawFilledBox(Colors::green, 0.1f, 0.4f);
			}
			endTransformation();
		}
		void move(const float &dt, const bool &_beam)
		{
			beginTransformation();
			{
				translate(center);
				this->drawLeftArm();
				this->drawLeftLeg();
				this->drawFaceAndBody();
				this->drawRightArm(_beam);
				this->drawRightLeg();
			}
			endTransformation();
			time += dt;
		}
		void shoot()
		{
			if (beam == nullptr)
			{
				beam = new Beam;
				std::cout << "beam is constructed" << std::endl;
			}
			beam->center = this->center;
			beam->center.x = this->direction.x * 1.0f;
			beam->center.y = 0.0f;
			beam->draw();
		}
	};

	class WalkingPerson : public Game2D
	{
	public:
		Person myPerson;

	public:
		WalkingPerson()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
		}

		~WalkingPerson()
		{
		}

		void update() override
		{
			// move person
			if (isKeyPressed(GLFW_KEY_LEFT))
			{
				myPerson.center.x -= 0.5f * getTimeStep();
				myPerson.direction.x = -1.0f;
				myPerson._stand = false;
			}
			if (isKeyPressed(GLFW_KEY_RIGHT))
			{
				myPerson.center.x += 0.5f * getTimeStep();
				myPerson.direction.x = 1.0f;
				myPerson._stand = false;
			}
			if (isKeyPressed(GLFW_KEY_UP))
			{
				myPerson.center.y += 0.5f * getTimeStep();
				myPerson._stand = false;
			}
			if (isKeyPressed(GLFW_KEY_DOWN))
			{
				myPerson.center.y -= 0.5f * getTimeStep();
				myPerson._stand = false;
			}

			// stand person
			if (!isKeyPressed(GLFW_KEY_RIGHT) && !isKeyPressed(GLFW_KEY_LEFT) && !isKeyPressed(GLFW_KEY_UP) && !isKeyPressed(GLFW_KEY_DOWN))
			{
				myPerson._stand = true;
			}

			// rendering
			// shoot repulsor beam
			if (isKeyPressed(GLFW_KEY_SPACE))
			{
				myPerson.move(this->getTimeStep(), true);
			}
			else
			{
				myPerson.move(this->getTimeStep(), false);
			}
		}
	};
}