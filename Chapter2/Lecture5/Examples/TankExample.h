#pragma once

#include "Game2D.h"
#include <map>
#include <vector>
#include <memory>
#include <fstream>

namespace jm
{
	class Actor
	{
	public:
		virtual void moveUp(float dt) = 0;
		virtual void moveDown(float dt) = 0;
		virtual void moveLeft(float dt) = 0;
		virtual void moveRight(float dt) = 0;
		virtual void shoot()
		{
		}
	};

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Actor &actor, float dt) = 0;
	};

	class UpCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveUp(dt);
		}
	};

	class DownCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveDown(dt);
		}
	};

	class LeftCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveLeft(dt);
		}
	};

	class RightCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveRight(dt);
		}
	};

	class ShootCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.shoot();
		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		const float radius = 0.02f;

		~MyBullet()
		{
			//std::cout << "Bullet destruction is called" << std::endl;
		}

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

	class MyTank : public Actor
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(1.0f, 0.0f);
		std::vector<MyBullet *> bullets;

		~MyTank()
		{
			for (auto &bullet : bullets)
			{
				if (bullet != nullptr) delete bullet;
			}
		}

		void moveUp(float dt) override
		{
			center.y += 0.5f * dt;
		}
		void moveDown(float dt) override
		{
			center.y -= 0.5f * dt;
		}
		void moveLeft(float dt) override
		{
			center.x -= 0.5f * dt;
			direction.x = -1.0f;
		}
		void moveRight(float dt) override
		{
			center.x += 0.5f * dt;
			direction.x = 1.0f;
		}

		void shoot() override
		{
			MyBullet *bullet = new MyBullet;
			bullet->center = this->center;
			bullet->center.x += 0.2f * this->direction.x;
			bullet->center.y += 0.1f;
			bullet->velocity = vec2(2.0f * this->direction.x, 0.0f);
			bullets.push_back(bullet);
		}

		void deleteBullet(float dt)
		{
			auto iterator = 0;
			for (auto &bullet : bullets)
			{
				bullet->update(dt);
				bullet->draw();
				if (!bullet->isOnDisplay(1024, 768))
				{
					delete bullet;
					bullets.erase(bullets.begin() + iterator);
				}
				iterator++;
			}
		}

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

	class InputHandler
	{
	public:
		/*Command * button_up = nullptr;*/

		std::map<int, Command *> key_command_map;
		std::pair<int, ShootCommand> button_shoot;

		InputHandler()
		{
			/*button_up = new UpCommand;*/
		}

		void handleInput(Game2D &game, Actor &actor, float dt)
		{
			/*if (game.isKeyPressed(GLFW_KEY_UP))  button_up->execute(actor, dt);*/

			if (game.isKeyPressedAndReleased(button_shoot.first))	button_shoot.second.execute(actor, dt);
			for (auto &m : key_command_map)
			{
				if (game.isKeyPressed(m.first)) m.second->execute(actor, dt);
			}
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		InputHandler input_handler;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			////key mapping
			//input_handler.key_command_map[GLFW_KEY_UP] = new UpCommand;
			//input_handler.key_command_map[GLFW_KEY_DOWN] = new DownCommand;
			//input_handler.key_command_map[GLFW_KEY_LEFT] = new LeftCommand;
			//input_handler.key_command_map[GLFW_KEY_RIGHT] = new RightCommand;

			// file reading
			std::ifstream ifs("key_binding.txt");

			if (!ifs)
			{
				std::cerr << "Cannot open file" << std::endl;
				exit(1);
			}

			while (ifs)
			{
				std::string key, str;
				std::getline(ifs, key, ' ');
				std::getline(ifs, str, '\n');

				if (str == "move_up")
				{
					if (key[0] == 'W')
						input_handler.key_command_map[GLFW_KEY_W] = new UpCommand;
				}
				else if (str == "move_down")
				{
					if (key[0] == 'S')
						input_handler.key_command_map[GLFW_KEY_S] = new DownCommand;
				}
				else if (str == "move_left")
				{
					if (key[0] == 'A')
						input_handler.key_command_map[GLFW_KEY_A] = new LeftCommand;
				}
				else if (str == "move_right")
				{
					if (key[0] == 'D')
						input_handler.key_command_map[GLFW_KEY_D] = new RightCommand;
				}
				else if (str == "shoot")
				{
					if (key == "SPACE")
						input_handler.button_shoot.first = GLFW_KEY_SPACE;
					else if (key == "LEFT_SHIFT")
						input_handler.button_shoot.first = GLFW_KEY_LEFT_SHIFT;
				}
			}

			ifs.close();
		}

		~TankExample()
		{
		}

		void update() override
		{
			input_handler.handleInput(*this, tank, getTimeStep());

			// rendering
			tank.draw();
			tank.deleteBullet(getTimeStep());
		}
	};
}