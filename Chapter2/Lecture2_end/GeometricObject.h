#pragma once

#include "Game2D.h"

namespace jm
{
	class GeometricObject : public Game2D
	{
	public:
		vec2 pos;
		RGB  color;
		float time = 0.0f;

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
				rotate(getRadian(time * 360.0f * 10.0f));
				drawGeometry();
			}
			endTransformation();
			time += this->getTimeStep();
		}
	};
}