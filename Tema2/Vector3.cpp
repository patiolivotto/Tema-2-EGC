#include "Vector3.h" 

//--- Metode clasa Vector3 ---
Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {
}

Vector3::~Vector3(){
}

void Vector3::setVector3(float x, float y, float z){
	this->x = x; 
	this->y = y; 
	this->z = z;
}