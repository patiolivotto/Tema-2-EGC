#include "Color.h"
#include <iostream> 

ColorMatrix::ColorMatrix(Color color): color(color){
	for(int i=0; i<9; i++){
		matrix.push_back(new Color(color.red, color.green, color.blue));
	}
}

ColorMatrix::~ColorMatrix(){
}

void ColorMatrix::setColor(Color color){
	this->color = color;
}

void ColorMatrix::setColorAt(Color *color, int i){
	if (i>=0 && i<9){
		matrix[i] = color;
	}
}

Color* ColorMatrix::getColorAt(int i){
	if(i>=0 && i<9){
		return matrix[i];
	}
	// not very safe
	return new Color(0.0f, 0.0f, 0.0f);
}


void ColorMatrix::setLeftNeighbours(Color* one, Color* two, Color* three){
	m_left.push_back(one); 
	m_left.push_back(two); 
	m_left.push_back(three);
}

void ColorMatrix::setUpNeighbours(Color* one, Color* two, Color* three){
	m_up.push_back(one); 
	m_up.push_back(two); 
	m_up.push_back(three);
}
void ColorMatrix::setRightNeighbours(Color* one, Color* two, Color* three){
	m_right.push_back(one); 
	m_right.push_back(two); 
	m_right.push_back(three);
}
void ColorMatrix::setBottomNeighbours(Color* one, Color* two, Color* three){
	m_bottom.push_back(one); 
	m_bottom.push_back(two); 
	m_bottom.push_back(three);
}

void ColorMatrix::rotateClockwise(){
	std::vector<Color> copy, copyup, copybottom;
	for(int i=0; i<9; ++i){
		copy.push_back(*matrix[i]);
	}
	
	*matrix[0] = copy[6]; 
	*matrix[1] = copy[3];
	*matrix[2] = copy[0]; 
	*matrix[3] = copy[7]; 
	*matrix[4] = copy[4]; 
	*matrix[5] = copy[1]; 
	*matrix[6] = copy[8];
	*matrix[7] = copy[5];
	*matrix[8] = copy[2];

	// Facem niste copii pentru a putea face 
	// interschimbarile de culori
	for(int i=0; i<3; ++i){
		copyup.push_back(*m_up[i]);
		copybottom.push_back(*m_bottom[i]);
	}

	*m_bottom[0] = *m_right[0];
	*m_bottom[1] = *m_right[1];
	*m_bottom[2] = *m_right[2];

	*m_up[0] = *m_left[0]; 
	*m_up[1] = *m_left[1]; 
	*m_up[2] = *m_left[2];
	
	*m_left[0] = copybottom[0];
	*m_left[1] = copybottom[1];
	*m_left[2] = copybottom[2];

	*m_right[0] = copyup[0];
	*m_right[1] = copyup[1];
	*m_right[2] = copyup[2];

}

void ColorMatrix::rotateCounterClockwise(){
	std::vector<Color> copy, copyup, copybottom;
	for(int i=0; i<9; ++i){
		copy.push_back(*matrix[i]);
	}
	*matrix[0] = copy[2]; 
	*matrix[1] = copy[5];
	*matrix[2] = copy[8]; 
	*matrix[3] = copy[1]; 
	*matrix[4] = copy[4]; 
	*matrix[5] = copy[7]; 
	*matrix[6] = copy[0];
	*matrix[7] = copy[3];
	*matrix[8] = copy[6];

	// Facem niste copii pentru a putea face 
	// interschimbarile de culori
	for(int i=0; i<3; ++i){
		copyup.push_back(*m_up[i]);
		copybottom.push_back(*m_bottom[i]);
	}

	*m_bottom[0] = *m_left[0];
	*m_bottom[1] = *m_left[1];
	*m_bottom[2] = *m_left[2];

	*m_up[0] = *m_right[0]; 
	*m_up[1] = *m_right[1]; 
	*m_up[2] = *m_right[2];
	
	*m_left[0] = copyup[0];
	*m_left[1] = copyup[1];
	*m_left[2] = copyup[2];

	*m_right[0] = copybottom[0];
	*m_right[1] = copybottom[1];
	*m_right[2] = copybottom[2];

	
}