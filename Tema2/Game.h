#pragma once 

#include <vector> 
#include "Cube.h"
class RubikCube;

class Game{
	private:
		Game();
		virtual ~Game();
	public:
		static void init(void);
		static void display(void);
		static void animatieDisplay();
		static void reshape(int w, int h);
		static void special(int key,int x,int y);
		static void keyboard(unsigned char key,int x,int y);
		static void mouse(int buton, int stare, int x, int y);
		static void mouse_motion(int x, int y);
		static void mouse_passive_motion(int x, int y);
	private:
		static int mouse_posx, mouse_posy;
		static float camera_rotx, camera_roty;
		static float cx, cy, cz, upx, upy, upz;
		const static int UNDEFINED;
		static RubikCube *rubik_cube;
		static Cube *cube;
		static float aspect;
		static int win_h, win_w;
		static bool solve;
		static float radius;
};