#include "GeometricObject.h"
#include <memory>

#include "Triangle.h"
#include "Circle.h"
#include "Box.h"
#include "Star.h"

namespace jm
{
	std::unique_ptr<GeometricObject> GeometricObject::makeTriangle(const RGB &_color, const vec2 &_pos, const float &_size)
	{
		return std::make_unique<Triangle>(_color, _pos, _size);
	}

	std::unique_ptr<GeometricObject> GeometricObject::makeCircle(const RGB &_color, const vec2 &_pos, const float &_size)
	{
		return std::make_unique<Circle>(_color, _pos, _size);
	}

	std::unique_ptr<GeometricObject> GeometricObject::makeBox(const RGB &_color, const vec2 &_pos, const float &_width, const float &_height)
	{
		return std::make_unique<Box>(_color, _pos, _width, _height);
	}

	std::unique_ptr<GeometricObject> GeometricObject::makeStar(const RGB &_color, const vec2 &_pos, const float &_os, const float &_is)
	{
		return std::make_unique<Star>(_color, _pos, _os, _is);
	}
}