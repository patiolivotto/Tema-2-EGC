#include "Cube.h" 
#include "Vector3.h"
#include "dependinte/freeglut.h" 
#include "RubikCube.h"
#include "Color.h" 
#include <iostream> 
#include <windows.h>

Cube::Cube(Color *color, Vector3 position) : 
	colors(colors),
	m_position(position.x, position.y, position.z) {
		setSameColor(color);
};

Cube::~Cube(){
}

void Cube::DrawFace(Color *fill, Color *outline){
	glBegin(GL_TRIANGLE_STRIP);
		// Desenam mai intai continutul planului 
		glColor3f(fill->red, fill->green, fill->blue);
		glVertex3f(-0.9f, -0.9f, 0.0f); 
		glVertex3f(-0.9f, 0.9f, 0.0f); 
		glVertex3f(0.9f, -0.9f, 0.0f); 
		glVertex3f(0.9f, 0.9f, 0.0f);
	glEnd(); 
	glBegin(GL_TRIANGLES);
		// Desenam conturului planului 
		glColor3f(outline->red, outline->green, outline->blue);
		glVertex3f(-1.0f, -1.0f, 0.0f); 
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-0.9f, 1.0f, 0.0f); 

		glVertex3f(-0.9f, 1.0f, 0.0f);
		glVertex3f(-0.9f, -1.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glVertex3f(-0.9f, -1.0f, 0.0f); 
		glVertex3f(0.9f, -1.0f, 0.0f); 
		glVertex3f(0.9f, -0.9f, 0.0f);

		glVertex3f(0.9f, -0.9f, 0.0f); 
		glVertex3f(-0.9f, -0.9f, 0.0f); 
		glVertex3f(-0.9f, -1.0f, 0.0f); 

		glVertex3f(0.9f, -1.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, 0.0f); 
		glVertex3f(1.0f, 1.0f, 0.0f); 
		
		glVertex3f(1.0f, 1.0f, 0.0f); 
		glVertex3f(0.9f, 1.0f, 0.0f); 
		glVertex3f(0.9f, -1.0f, 0.0f);

		glVertex3f(-0.9f, 0.9f, 0.0f); 
		glVertex3f(-0.9f, 1.0f, 0.0f); 
		glVertex3f(0.9f, 0.9f, 0.0f);

		glVertex3f(0.9f, 0.9f, 0.0f); 
		glVertex3f(0.9f, 1.0f, 0.0f); 
		glVertex3f(-0.9f, 1.0f, 0.0f);
	glEnd();
}

void Cube::DrawCube(bool highlighted){
	Color *border;
	if (colors.size() != 6){
		std::cout << "Trebuie specificate 6 culori pentru fetele cubului";
		std::cout << std::endl;
	}
	else {
		if (highlighted==true){
			border = new Color(0.5f, 0.5f, 0.5f);
		}
		else {
			border = new Color(0.0f, 0.0f, 0.0f);
		}
		glPushMatrix();
		glTranslatef(m_position.x, m_position.y, m_position.z);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 1.0f);
				// std::cout << "color%%" << (*colors[0]).red << std::endl;
				DrawFace(colors[0], border);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, 1.0f);
				DrawFace(colors[1], border);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -1.0f);
				DrawFace(colors[2], border);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, -1.0f);
				DrawFace(colors[3], border);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, -1.0f);
				DrawFace(colors[4], border);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, 1.0f);
				DrawFace(colors[5], border);
			glPopMatrix();
			
		glPopMatrix();
		delete border;
	}
}


void Cube::AddToLayer(LAYER layer){
	layers.push_back(layer);

}

void Cube::setSameColor(Color *color){
	for(int i=0; i<6; ++i){
		colors.push_back(color);
	}
}

void Cube::setFaceColor(FACE face, Color *color){
	colors[face] = color;
}

Color Cube::getFaceColor(FACE face){
	return *colors[face];
}