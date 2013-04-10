#pragma once 
#include <vector>

class Color{
	public:
		float red, green, blue;
		Color(float red, float green, float blue){ SetColor(red, green, blue);}
		virtual ~Color() {}

		void SetColor(float red, float green, float blue){
			this->red = red; 
			this->green = green; 
			this->blue = blue;
		}
};

class Matrix{
	public:
		virtual void rotateClockwise() = 0;
		virtual void rotateCounterClockwise() = 0;
};

class ColorMatrix : public Matrix { 
	public:
		ColorMatrix(Color color); 
		virtual ~ColorMatrix();
		void setColor(Color color);
		void setColorAt(Color *color, int i);
		Color* getColorAt(int i);
		void setLeftNeighbours(Color* one, Color* two, Color* three); 
		void setUpNeighbours(Color* one, Color* two, Color* three);
		void setRightNeighbours(Color* one, Color* two, Color* three);
		void setBottomNeighbours(Color* one, Color* two, Color* three); 
		void rotateClockwise();
		void rotateCounterClockwise();
		std::vector<Color*> matrix;
	private:
		Color color;
		std::vector<Color*> m_left, m_up, m_right, m_bottom;
};

/*
class ColorColumn : public Matrix {
	public:
	  ColorColumn(); 
	  virtual ~ColorColumn();
	  void setComponents(ColorMatrix *one, ColorMatrix *two, 
						 ColorMatrix *three, ColorMatrix *four,
						 int dir1, int dir2, int dir3, int dir4);
	  // 1 pentru directie orizontala, 1 pentru directie verticala
	  void rotateClockwise();
	  void rotateCounterClockwise();

	private:
	  ColorMatrix *m_one, *m_two, *m_three, *m_four;
	  int index1[3], index2[2], index3[3], index[4];
};
*/ 