#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <vector>
#include <memory>

namespace jm
{
	class Example : public Game2D
	{
	public:
		RigidCircle rb0, rb1, rb2;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			// Initial position and velocity
			rb0.pos = vec2(-0.8f, 0.3f);
			rb0.vel = vec2(5.0f, 0.0f);
			rb0.color = Colors::hotpink;
			rb0.radius = 0.1f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.8f, 0.3f);
			rb1.vel = vec2(-5.0f, 0.0f);
			rb1.color = Colors::yellow;
			rb1.radius = 0.1f;
			rb1.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);

			rb2.pos = vec2(0.0f, -0.3f);
			rb2.vel = vec2(0.0f, 5.0f);
			rb2.color = Colors::blue;
			rb2.radius = 0.1f;
			rb2.mass = rb0.mass * std::pow(rb2.radius / rb0.radius, 2.0f);
		}

		void drawWall()
		{
			setLineWidth(5.0f);
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			drawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		void update() override
		{
			const float dt = getTimeStep() * 0.4f;
			const float epsilon = 0.5f;

			// physics update
			rb0.update(dt);
			rb1.update(dt);
			rb2.update(dt);

			// check collision between two rigid bodies
			const float distance_01 = (rb0.pos - rb1.pos).getMagnitude();
			const float distance_12 = (rb1.pos - rb2.pos).getMagnitude();
			const float distance_20 = (rb2.pos - rb0.pos).getMagnitude();

			if (distance_01 <= rb0.radius + rb1.radius)
			{
				// compute impulse
				const auto vel_rel = rb0.vel - rb1.vel; // 상대속도
				const auto normal = -(rb1.pos - rb0.pos) / (rb1.pos - rb0.pos).getMagnitude(); // 노말 벡터

				if (vel_rel.getDotProduct(normal) < 0.0f)	// approaching
				{
					const auto impulse = normal * -(1.0f + epsilon) * vel_rel.getDotProduct(normal) / ((1.0f / rb0.mass) + (1.0f / rb1.mass));

					// update velocities of two bodies
					rb0.vel += impulse / rb0.mass;
					rb1.vel -= impulse / rb1.mass;
				}
			}

			if (distance_12 <= rb1.radius + rb2.radius)
			{
				// compute impulse
				const auto vel_rel = rb1.vel - rb2.vel; // 상대속도
				const auto normal = -(rb2.pos - rb1.pos) / (rb2.pos - rb1.pos).getMagnitude(); // 노말 벡터

				if (vel_rel.getDotProduct(normal) < 0.0f)	// approaching
				{
					const auto impulse = normal * -(1.0f + epsilon) * vel_rel.getDotProduct(normal) / ((1.0f / rb1.mass) + (1.0f / rb2.mass));

					// update velocities of two bodies
					rb1.vel += impulse / rb1.mass;
					rb2.vel -= impulse / rb2.mass;
				}
			}

			if (distance_20 <= rb2.radius + rb0.radius)
			{
				// compute impulse
				const auto vel_rel = rb2.vel - rb0.vel; // 상대속도
				const auto normal = -(rb0.pos - rb2.pos) / (rb0.pos - rb2.pos).getMagnitude(); // 노말 벡터

				if (vel_rel.getDotProduct(normal) < 0.0f)	// approaching
				{
					const auto impulse = normal * -(1.0f + epsilon) * vel_rel.getDotProduct(normal) / ((1.0f / rb2.mass) + (1.0f / rb0.mass));

					// update velocities of two bodies
					rb2.vel += impulse / rb2.mass;
					rb0.vel -= impulse / rb0.mass;
				}
			}

			// draw
			drawWall();
			rb0.draw();
			rb1.draw();
			rb2.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
		}
	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}