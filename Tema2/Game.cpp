#define _USE_MATH_DEFINES 
#include "Game.h"
#include "dependinte/freeglut.h"
#include "RubikCube.h"
#include "Color.h"
#include <iostream> 
#include <cmath> 

#define ENTER_KEY	13
#define ESCAPE_KEY	27
#define SPACE_KEY	32

/* Initializarea variabilelor statice */ 
const int Game::UNDEFINED = -1;
int Game::mouse_posx = Game::UNDEFINED;
int Game::mouse_posy = Game::UNDEFINED;
float Game::camera_rotx = 180.0f;
float Game::camera_roty = 270.0f;
float Game::cx = 0.0f; 
float Game::cy = 0.0f; 
float Game::cz = 8.5f;
float Game::upx = 0.0f; 
float Game::upy = 1.0f; 
float Game::upz = 0.0f;
RubikCube *Game::rubik_cube = NULL;
Cube *Game::cube = NULL;
float Game::aspect = 1;
int Game::win_w = 1;
int Game::win_h = 1;
bool Game::solve = false; 
float Game::radius = 8.5f;

Game::Game(){
}

Game::~Game(){
}

void Game::init(void)
{	//specifica valorile r,g,b,a folosite atunci cand se sterge bufferul de culoare cu glClear
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	rubik_cube = new RubikCube();
}

/* Functia de afisare */ 
void Game::display(void)
{
	// Initializeaza bufferul de culoare
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	if (solve){
		rubik_cube->solveGame();
	}
	rubik_cube->drawCubes();
	
	glViewport(5, 5, 0, 0);
	rubik_cube->drawText();
	glViewport(0, 0, win_w, win_h);
	
	glutSwapBuffers();

}

void Game::animatieDisplay()
{
	
	glutPostRedisplay();
}

void Game::reshape(int w, int h)
{
	//transformarea in poarta de vizualizare
	glViewport(0,0, (GLsizei) w, (GLsizei) h);

	aspect = (GLfloat) w / (GLfloat) h;

	//se lucreaza pe matricea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//transformarea de proiectie - specifica si volumul de vizualizare
	gluPerspective(79.0f, aspect, 0.1f, 60.0f);

	//se lucreaza pe matricea de modelare vizualizare
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cx, cy, cz,	   //pozitia observatorului
		      0.0, 0.0, 0.0,   //punctul catre care priveste
			  upx, upy, upz);  

	win_w = w;
	win_h = h;
	

}

void Game::special(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		rubik_cube->spinActiveLayer(NEGATIVE);
		break;
	case GLUT_KEY_RIGHT:
		rubik_cube->spinActiveLayer(POSITIVE);
		break;
	}
	//cere redesenarea scenei
	glutPostRedisplay();
}

void Game::keyboard(unsigned char key,int x,int y)
{
	
	switch(key)
	{
	case ESCAPE_KEY:
		exit(0);
		break;
	case ENTER_KEY:
		rubik_cube->startGame();
		break;
	case SPACE_KEY:
		rubik_cube->selectNextLayer();
		break;
	case 's':
		solve = true;
		break;
	case '+':
		// Zoom in
		radius -= 0.3f;
		if (radius<8.5f)
			radius=8.5f;
		std::cout << "+" << radius;
		break;
	case '-':
		// Zoom out
		radius += 0.3f;
		if (radius>12.5f)
			radius=11.5f;
		std::cout << "-" << radius;
	default:
		break;
	}
	//cere redesenarea scenei
	glutPostRedisplay();
}

//functie apelata la actionarea mouse-ului
void Game::mouse(int buton, int stare, int x, int y)
{
	
}
void Game::mouse_passive_motion(int x, int y){
	mouse_posx	= -1; 
	mouse_posy	= -1;
}

void Game::mouse_motion(int x, int y)
{
	int diffx, diffy;
	float cx_temp, cy_temp, cz_temp;
	float degree = (float)M_PI/180.0f;

	if (mouse_posx == -1 && mouse_posy == -1){
		mouse_posx = x; 
		mouse_posy = y; 
	}
	else {
		diffx = mouse_posx - x; 
		diffy = mouse_posy - y;
		camera_rotx += diffx;
		if (camera_rotx >= 360.0f || camera_rotx<=-360.0f)
			camera_rotx = 0; 

		camera_roty += diffy;
		if (camera_roty >= 360.0f || camera_roty<=-360.0f)
			camera_roty = 0;
		// theta = camera_roty 
		// phi	 = camera_royx
		// Transformarea din coordonate sferice in coordonate carteziene
		cx = radius * sin(camera_roty*degree) * sin(camera_rotx*degree);
		cy = radius * cos(camera_roty*degree);
		cz = radius * sin(camera_roty*degree) * cos(camera_rotx*degree);
		
		// Obtinerea unui punct cu aceeasi longitudine cu cel anterior
		cx_temp = radius * sin(camera_roty*degree+1.0f) * sin(camera_rotx*degree);
		cy_temp = radius * cos(camera_roty*degree+1.0f);
		cz_temp = radius * sin(camera_roty*degree+1.0f) * cos(camera_rotx*degree);
		
		// Acum folosim punctul temporar pentru vectorul up 
		upx = cx_temp - cx;
		upy = cy_temp - cy;
		upz = cz_temp - cz;
		glLoadIdentity();
		gluLookAt(cx, cy, cz,   //observatorul este in origine
		      0.0, 0.0, 0.0,   //si priveste in directia pozitiva a axei oz
			  upx, upy, upz);  
		mouse_posx = x; 
		mouse_posy = y;
	}
}