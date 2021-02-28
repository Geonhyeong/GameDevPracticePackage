#pragma once

#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		vec2 pos;
		RGB  color;

		virtual ~GeometricObject()
		{}

		void init(const RGB &_color, const vec2 &_pos)
		{
			color = _color;
			pos = _pos;
		}

		virtual void drawGeometry() const = 0;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawGeometry();
			}
			endTransformation();
		}

		static std::unique_ptr<GeometricObject> makeTriangle(const RGB &_color, const vec2 &_pos, const float &_size);
		static std::unique_ptr<GeometricObject> makeCircle(const RGB &_color, const vec2 &_pos, const float &_size);
		static std::unique_ptr<GeometricObject> makeBox(const RGB &_color, const vec2 &_pos, const float &_width, const float &_height);
		static std::unique_ptr<GeometricObject> makeStar(const RGB &_color, const vec2 &_pos, const float &_os, const float &_is);
	};
}