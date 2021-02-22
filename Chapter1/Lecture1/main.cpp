#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "TankExample.h"
#include "FaceExample.h"
#include "WalkingPerson.h"
#include "SolarSystem.h"
#include "CrayonFace.h"

namespace jm
{
	class MouseExample : public Game2D
	{
	private:
		float time = 0.0f;

	public:
		void update() override
		{
			const vec2 mouse_pos = getCursorPos(true);

			beginTransformation();
			{
				if (abs(mouse_pos.x) <= 0.1f && abs(mouse_pos.y) <= 0.1f)
					drawFilledCircle(Colors::red, 0.1f);
				else
					drawFilledCircle(Colors::blue, 0.1f);
			}
			endTransformation();

			//time += this->getTimeStep();
		}
	};
}

int main(void)
{
	jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::RotatingStarExample().run();
	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//jm::SolarSystem().run();
	//jm::FaceExample().run();
	//jm::WalkingPerson().run();
	//jm::TankExample().run();
	//jm::CrayonFace().run();

	return 0;
}