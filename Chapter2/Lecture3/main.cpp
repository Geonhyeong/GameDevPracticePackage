#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Circle.h"
#include "Box.h"
#include <vector>
#include <memory>

namespace jm
{
	class Example : public Game2D
	{
	public:
		std::vector<std::unique_ptr<GeometricObject>> my_objs;

		Example()
			: Game2D()
		{
			my_objs.push_back(std::make_unique<Triangle>(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f));
			my_objs.push_back(std::make_unique<Circle>(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f));
			my_objs.push_back(std::make_unique<Box>(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f));
		}

		void update() override
		{
			for (const auto &obj : my_objs)
				obj->draw();
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