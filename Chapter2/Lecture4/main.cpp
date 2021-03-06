#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "GeometricObject.h"
#include <vector>
#include <memory>

namespace jm
{
	class Example : public Game2D
	{
	public:
		std::vector<std::unique_ptr<GeometricObject>> my_objs;
		int a;

		Example()
			: Game2D()
		{
			my_objs.push_back(GeometricObject::makeTriangle(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f));
			my_objs.push_back(GeometricObject::makeCircle(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f));
			my_objs.push_back(GeometricObject::makeBox(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f));
			my_objs.push_back(GeometricObject::makeStar(Colors::yellow, vec2{ -0.2f, -0.2f }, 0.25f, 0.15f));
		}

		~Example()
		{
			//delete is unnecessary with shared_ptr
			//for (const auto & obj : my_objs)
			//	delete obj;
		}

		/*void addObject(std::string &_type, const vec2 &_pos, const float &_size)
		{
			if (_type == "")
				return;
			if (_type == "Triangle")
			{
				my_objs.push_back(GeometricObject::makeTriangle(Colors::gold, _pos, _size));
			}
			else if (_type == "Circle")
			{
				my_objs.push_back(GeometricObject::makeCircle(Colors::olive, _pos, _size));
			}
			else if (_type == "Box")
			{
				my_objs.push_back(GeometricObject::makeBox(Colors::olive, _pos, _size, _size));
			}
			else if (_type == "Star")
			{
				my_objs.push_back(GeometricObject::makeStar(Colors::olive, _pos, _size, _size));
			}
			_type = "";
		}*/

		void update() override
		{
			for (const auto &obj : my_objs)
				obj->draw();

			// TODO : 콘솔창으로부터 입력을 받아서 화면에 물체를 생성하기....어떻게 함?
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