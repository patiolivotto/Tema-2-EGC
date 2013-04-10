#pragma once 

class Vector3{
	public:
		Vector3(float x, float y, float z);
		virtual ~Vector3();
		void setVector3(float x, float y, float z);
		float x, y, z;

};