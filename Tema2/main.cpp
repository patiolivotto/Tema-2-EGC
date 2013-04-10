//programul deseneaza figuri care incep sa se roteasca la apasarea
//butonului din stanga al mouse-ului si se opresc la apasarea
//butonului din dreapta.
#include <cstdlib>
#include "dependinte\freeglut.h"
#include <iostream>

#include "Game.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH|GLUT_MULTISAMPLE);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,50);
	glutCreateWindow("Ultimate RibixCon");
	glEnable(GL_DEPTH_TEST);
	Game::init();
	
	//functia de afisare se numeste display()
	glutDisplayFunc(Game::display);
	
	//functia reshape() este apelata la redimensionarea ferestrei de afisare 
	//sau cand sistemul determina ca s-a acoperit (partial) fereastra
	glutReshapeFunc(Game::reshape);
	
	//functia mouse() se apeleaza la actionarea mouse-ului
	glutMouseFunc(Game::mouse);

	// functia mouse_motion() se apleaza la miscarea mouseului
	// cand un buton al mouseul este apasat 
	glutMotionFunc(Game::mouse_motion);
	
	// functia mouse_passive_motion se apleaza la miscarea 
	// mouseului cand nici un buton nu e apasat 
	glutPassiveMotionFunc(Game::mouse_passive_motion);


	//functia keyboard() se apeleaza la apasarea unei taste
	glutKeyboardFunc(Game::keyboard);

	//functia special() se apeleaza la apasarea unei taste speciale
	glutSpecialFunc(Game::special);
	
	//functia idle animatieDisplay() se apeleaza oricand nu sunt evenimente
	glutIdleFunc(Game::animatieDisplay);

	//contine o bucla in care aplicatia asteapta evenimente
	glutMainLoop();

	
	return 0;
}