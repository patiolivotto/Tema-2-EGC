#pragma once 
#include <vector> 
#include "Vector3.h"

class RubikLayer;
class Color;

enum LAYER{
	INACTIVE = -1,
	FRONT = 0, RIGHT = 1,
	BACK = 2, LEFT = 3, 
	UP = 4, BOTTOM = 5 
};

enum FACE{
	FRONT_FACE = 0, RIGHT_FACE = 1, BACK_FACE = 2, 
	LEFT_FACE = 3, TOP_FACE = 4, BOTTOM_FACE = 5
};

class Cube{
	public:
		Cube(Color *color, Vector3 position);
		virtual ~Cube();
		void DrawFace(Color *fill, Color *outline);
		void DrawCube(bool highlighted);
		void setSameColor(Color *color);
		void setFaceColor(FACE face, Color* color);
		Color getFaceColor(FACE face);
		void AddToLayer(LAYER layer);
		// Indecsii layerelor in care se gaseste 
		std::vector<int> layers;
	private:
		// Tine culori pentru fiecare fata in parte
		std::vector<Color*> colors;
		Vector3 m_position;
};