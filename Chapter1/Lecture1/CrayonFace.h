#pragma once

#include "Game2D.h"

namespace jm
{
	class CrayonFace : public Game2D
	{
	public:
		void update() override
		{
			rotate(-10.0f);
			// hair
			beginTransformation();
			{
				translate(0.04f, 0.03f);
				drawFilledCircle(Colors::black, 0.5f);
			}
			endTransformation();

			// over face
			beginTransformation();
			{
				scale(0.95f, 0.9f);
				drawFilledCircle(Colors::skin, 0.5f);
			}
			endTransformation();

			// undo face
			beginTransformation();
			{
				translate(-0.15f, -0.2f);
				scale(1.20f, 0.60f);
				drawFilledCircle(Colors::skin, 0.5f);
			}
			endTransformation();

			// left eyebrow
			beginTransformation();
			{
				vec2 center_of_rotation(0.125f, 0.05f);
				translate(-0.2f, 0.475f);
				rotate(40.0f);
				translate(-center_of_rotation);
				drawFilledBox(Colors::black, 0.25f, 0.1f);
			}
			endTransformation();
			beginTransformation();
			{
				vec2 center_of_rotation(0.05f, 0.125f);
				translate(-0.2f, 0.475f);
				rotate(50.0f);
				translate(-center_of_rotation);
				drawFilledBox(Colors::black, 0.1f, 0.25f);
			}
			endTransformation();
			beginTransformation();
			{
				setLineWidth(5);

				translate(-0.2f, 0.15f);
				vec2 pos1(-0.12f, 0.0f);
				vec2 pos2(0.0f, 0.1f);
				vec2 pos3(0.12f, 0.0f);
				drawLine(Colors::black, pos1, Colors::black, pos2);
				drawLine(Colors::black, pos2, Colors::black, pos3);
			}
			endTransformation();

			// right eyebrow
			beginTransformation();
			{
				vec2 center_of_rotation(0.125f, 0.05f);
				translate(0.2f, 0.475f);
				rotate(40.0f);
				translate(-center_of_rotation);
				drawFilledBox(Colors::black, 0.25f, 0.1f);
			}
			endTransformation();
			beginTransformation();
			{
				vec2 center_of_rotation(0.05f, 0.125f);
				translate(0.2f, 0.475f);
				rotate(50.0f);
				translate(-center_of_rotation);
				drawFilledBox(Colors::black, 0.1f, 0.25f);
			}
			endTransformation();
			beginTransformation();
			{
				setLineWidth(5);

				translate(0.2f, 0.15f);
				vec2 pos1(-0.12f, 0.0f);
				vec2 pos2(0.0f, 0.1f);
				vec2 pos3(0.12f, 0.0f);
				drawLine(Colors::black, pos1, Colors::black, pos2);
				drawLine(Colors::black, pos2, Colors::black, pos3);
			}
			endTransformation();

			// left eye
			beginTransformation();
			{
				translate(-0.2f, 0.0f);
				drawFilledCircle(Colors::black, 0.12f);
				drawFilledCircle(Colors::white, 0.04f);
			}
			endTransformation();

			// right eye
			beginTransformation();
			{
				translate(0.2f, 0.0f);
				drawFilledCircle(Colors::black, 0.12f);
				drawFilledCircle(Colors::white, 0.04f);
			}
			endTransformation();

			// mouth
			beginTransformation();
			{
				translate(-0.25f, -0.475f);
				rotate(-20.0f);
				scale(1.0f, 1.5f);
				drawFilledCircle(Colors::red, 0.04f);
			}
			endTransformation();

			// ear
			beginTransformation();
			{
				translate(0.48f, -0.175f);
				rotate(-20.0f);
				scale(1.0f, 1.5f);
				drawFilledCircle(Colors::skin, 0.1f);
			}
			endTransformation();
		}
	};
}