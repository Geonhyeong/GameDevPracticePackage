#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Star : public GeometricObject
	{
	public:
		float out_radius, in_radius;

		void init(const RGB &_color, const vec2 &_pos, const float &_out_radius,
			const float &_in_radius)
		{
			GeometricObject::init(_color, _pos);
			out_radius = _out_radius;
			in_radius = _in_radius;
		}

		void drawGeometry() const override
		{
			drawFilledStar(GeometricObject::color, out_radius, in_radius);
		}
	};
}