#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Circle.h"
#include "Box.h"
#include "Star.h"

namespace jm
{
	class Example : public Game2D
	{
	public:
		Triangle my_tri[5];
		Circle my_cir[5];
		Box my_box[5];
		Star my_star[5];

		RandomNumberGenerator rand;

		Example()
			: Game2D()
		{
			// using random number to draw objects random position
			for (int i = 0; i < 5; ++i)
				my_tri[i].init(Colors::red, rand.getFloatVector(-1.0f, 1.0f), 0.2f);

			for (int i = 0; i < 5; ++i)
				my_cir[i].init(Colors::olive, rand.getFloatVector(-1.0f, 1.0f), 0.2f);

			for (int i = 0; i < 5; ++i)
				my_box[i].init(Colors::blue, rand.getFloatVector(-1.0f, 1.0f), 0.2f, 0.3f);

			for (int i = 0; i < 5; ++i)
				my_star[i].init(Colors::gold, rand.getFloatVector(-1.0f, 1.0f), 0.2f, 0.12f);
		}

		void update() override
		{
			const vec2 mousepos = getCursorPos(true);
			//std::cout << mousepos.x << " " << mousepos.y << std::endl;

			for (int i = 0; i < 5; ++i)
				my_tri[i].draw();

			for (int i = 0; i < 5; ++i)
				my_cir[i].draw();

			for (int i = 0; i < 5; ++i)
				my_box[i].draw();

			for (int i = 0; i < 5; ++i)
				my_star[i].draw();
		}
	};
}

int main(void)
{
	jm::Example().run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}