#include "Cube.h"
#include "RubikCube.h"
#include "Color.h"
#include "dependinte/freeglut.h"
#include <iostream>
#include <cmath>
#include <ctime> 

RubikCube::RubikCube() : 
	active_layer(INACTIVE), 
	no_moves(0),
	started(false), 
	save_moves(true) {
	initSelectionOrder();
	createLayers();

	faces_colors.push_back(ColorMatrix(Color(1.0f, 0.0f, 0.0f)));
	faces_colors.push_back(ColorMatrix(Color(0.0f, 0.0f, 1.0f)));
	faces_colors.push_back(ColorMatrix(Color(1.0f, 0.0f, 1.0f)));
	faces_colors.push_back(ColorMatrix(Color(1.0f, 1.0f, 1.0f)));
	faces_colors.push_back(ColorMatrix(Color(1.0f, 1.0f, 0.0f)));
	faces_colors.push_back(ColorMatrix(Color(0.0f, 1.0f, 0.0f)));
	initFacesNeighbours();
}

RubikCube::~RubikCube(){
}

/* Initializeaza culorile vecine pentru fiecare 
 * fata a cubului mare in parte */ 
void RubikCube::initFacesNeighbours(){

	// TOP Face cu culori
	faces_colors[TOP_FACE].setUpNeighbours(
		faces_colors[BACK_FACE].getColorAt(2),
		faces_colors[BACK_FACE].getColorAt(1), 
		faces_colors[BACK_FACE].getColorAt(0));
	faces_colors[TOP_FACE].setRightNeighbours(
		faces_colors[RIGHT_FACE].getColorAt(0), 
		faces_colors[RIGHT_FACE].getColorAt(1), 
		faces_colors[RIGHT_FACE].getColorAt(2));
	faces_colors[TOP_FACE].setBottomNeighbours(
		faces_colors[FRONT_FACE].getColorAt(0), 
		faces_colors[FRONT_FACE].getColorAt(1),
		faces_colors[FRONT_FACE].getColorAt(2));
	faces_colors[TOP_FACE].setLeftNeighbours(
		faces_colors[LEFT_FACE].getColorAt(2), 
		faces_colors[LEFT_FACE].getColorAt(1), 
		faces_colors[LEFT_FACE].getColorAt(0));

	// FRONT face pentru culori 
	faces_colors[FRONT_FACE].setUpNeighbours(
		faces_colors[TOP_FACE].getColorAt(8), 
		faces_colors[TOP_FACE].getColorAt(7), 
		faces_colors[TOP_FACE].getColorAt(6));
	faces_colors[FRONT_FACE].setRightNeighbours(
		faces_colors[RIGHT_FACE].getColorAt(6), 
		faces_colors[RIGHT_FACE].getColorAt(3),
		faces_colors[RIGHT_FACE].getColorAt(0));
	faces_colors[FRONT_FACE].setBottomNeighbours(
		faces_colors[BOTTOM_FACE].getColorAt(6), 
		faces_colors[BOTTOM_FACE].getColorAt(7),
		faces_colors[BOTTOM_FACE].getColorAt(8));
	faces_colors[FRONT_FACE].setLeftNeighbours(
		faces_colors[LEFT_FACE].getColorAt(0),
		faces_colors[LEFT_FACE].getColorAt(3), 
		faces_colors[LEFT_FACE].getColorAt(6));
	createCubes();
	
	// Fata din stanga a cubului mare
	faces_colors[LEFT_FACE].setBottomNeighbours(
		faces_colors[TOP_FACE].getColorAt(0), 
		faces_colors[TOP_FACE].getColorAt(3), 
		faces_colors[TOP_FACE].getColorAt(6)); 
	faces_colors[LEFT_FACE].setLeftNeighbours(
		faces_colors[BACK_FACE].getColorAt(6), 
		faces_colors[BACK_FACE].getColorAt(3), 
		faces_colors[BACK_FACE].getColorAt(0));
	faces_colors[LEFT_FACE].setUpNeighbours(
		faces_colors[BOTTOM_FACE].getColorAt(6), 
		faces_colors[BOTTOM_FACE].getColorAt(3), 
		faces_colors[BOTTOM_FACE].getColorAt(0));
	faces_colors[LEFT_FACE].setRightNeighbours(
		faces_colors[FRONT_FACE].getColorAt(0),
		faces_colors[FRONT_FACE].getColorAt(3), 
		faces_colors[FRONT_FACE].getColorAt(6));

	// Fata din dreapta a cubului mare 
	faces_colors[RIGHT_FACE].setUpNeighbours(
		faces_colors[TOP_FACE].getColorAt(2), 
		faces_colors[TOP_FACE].getColorAt(5), 
		faces_colors[TOP_FACE].getColorAt(8)); 
	faces_colors[RIGHT_FACE].setRightNeighbours(
		faces_colors[BACK_FACE].getColorAt(8),
		faces_colors[BACK_FACE].getColorAt(5), 
		faces_colors[BACK_FACE].getColorAt(2));
	faces_colors[RIGHT_FACE].setBottomNeighbours(
		faces_colors[BOTTOM_FACE].getColorAt(8), 
		faces_colors[BOTTOM_FACE].getColorAt(5), 
		faces_colors[BOTTOM_FACE].getColorAt(2));
	faces_colors[RIGHT_FACE].setLeftNeighbours(
		faces_colors[FRONT_FACE].getColorAt(2), 
		faces_colors[FRONT_FACE].getColorAt(5), 
		faces_colors[FRONT_FACE].getColorAt(8));

	// Fata din spate a cubului mare 
	faces_colors[BACK_FACE].setUpNeighbours(
		faces_colors[TOP_FACE].getColorAt(2), 
		faces_colors[TOP_FACE].getColorAt(1),
		faces_colors[TOP_FACE].getColorAt(0));
	faces_colors[BACK_FACE].setLeftNeighbours(
		faces_colors[LEFT_FACE].getColorAt(2),
		faces_colors[LEFT_FACE].getColorAt(5),
		faces_colors[LEFT_FACE].getColorAt(8));
	faces_colors[BACK_FACE].setBottomNeighbours(
		faces_colors[BOTTOM_FACE].getColorAt(0),
		faces_colors[BOTTOM_FACE].getColorAt(1),
		faces_colors[BOTTOM_FACE].getColorAt(2));
	faces_colors[BACK_FACE].setRightNeighbours(
		faces_colors[RIGHT_FACE].getColorAt(8), 
		faces_colors[RIGHT_FACE].getColorAt(5), 
		faces_colors[RIGHT_FACE].getColorAt(2));

	// Fata de jos a cubului mare
	faces_colors[BOTTOM_FACE].setUpNeighbours(
		faces_colors[BACK_FACE].getColorAt(6),
		faces_colors[BACK_FACE].getColorAt(7), 
		faces_colors[BACK_FACE].getColorAt(8));
	faces_colors[BOTTOM_FACE].setRightNeighbours(
		faces_colors[RIGHT_FACE].getColorAt(8),
		faces_colors[RIGHT_FACE].getColorAt(7), 
		faces_colors[RIGHT_FACE].getColorAt(6)); 
	faces_colors[BOTTOM_FACE].setBottomNeighbours(
		faces_colors[FRONT_FACE].getColorAt(8), 
		faces_colors[FRONT_FACE].getColorAt(7), 
		faces_colors[FRONT_FACE].getColorAt(6));
	faces_colors[BOTTOM_FACE].setLeftNeighbours(
		faces_colors[LEFT_FACE].getColorAt(6),
		faces_colors[LEFT_FACE].getColorAt(7), 
		faces_colors[LEFT_FACE].getColorAt(8));
}

void RubikCube::createLayers(){
	Vector3 pivot(0.0f, 0.0f, 2.0f), 
			rotation_axis(0.0f, 0.0f, 1.0f);
	// Initializare layer FRONT 
	pivot.setVector3(0.0f, 0.0f, 2.0f);
	rotation_axis.setVector3(0.0f, 0.0f, 1.0f);
	cube_layers.push_back(RubikLayer(pivot, rotation_axis));
	// Initializare layer RIGHT
	pivot.setVector3(2.0f, 0.0f, 0.0f);
	rotation_axis.setVector3(1.0f, 0.0f, 0.0f); 
	cube_layers.push_back(RubikLayer(pivot, rotation_axis));

	// Initializare layer BACK
	pivot.setVector3(0.0f, 0.0f, -2.0f);
	rotation_axis.setVector3(0.0f, 0.0f, 1.0f);
	cube_layers.push_back(RubikLayer(pivot, rotation_axis));
	// Initializare layer LEFT
	pivot.setVector3(-2.0f, 0.0f, 0.0f); 
	rotation_axis.setVector3(1.0f, 0.0f, 0.0f);
	cube_layers.push_back(RubikLayer(pivot, rotation_axis));

	// Initializare layer UP 
	pivot.setVector3(0.0f, 2.0f, 0.0f);
	rotation_axis.setVector3(0.0f, 1.0f, 0.0f);
	cube_layers.push_back(RubikLayer(pivot, rotation_axis));
	// Initializare layer BOTTOM
	pivot.setVector3(0.0f, -2.0f, 0.0f); 
	rotation_axis.setVector3(0.0f, 1.0f, 0.0f);
	cube_layers.push_back(RubikLayer(pivot, rotation_axis));


	
	// Adaugarea listelor de conflicte pentru fiecare layer
	cube_layers[UP].addConflictLayer(&cube_layers[LEFT]);
	cube_layers[UP].addConflictLayer(&cube_layers[RIGHT]);
	cube_layers[UP].addConflictLayer(&cube_layers[FRONT]);
	cube_layers[UP].addConflictLayer(&cube_layers[BACK]);


	cube_layers[BOTTOM].addConflictLayer(&cube_layers[LEFT]);  
	cube_layers[BOTTOM].addConflictLayer(&cube_layers[RIGHT]);
	cube_layers[BOTTOM].addConflictLayer(&cube_layers[FRONT]);
	cube_layers[BOTTOM].addConflictLayer(&cube_layers[BACK]);

	cube_layers[LEFT].addConflictLayer(&cube_layers[UP]);  
	cube_layers[LEFT].addConflictLayer(&cube_layers[BOTTOM]);
	cube_layers[LEFT].addConflictLayer(&cube_layers[FRONT]);
	cube_layers[LEFT].addConflictLayer(&cube_layers[BACK]);

	cube_layers[RIGHT].addConflictLayer(&cube_layers[UP]); 
	cube_layers[RIGHT].addConflictLayer(&cube_layers[BOTTOM]);
	cube_layers[RIGHT].addConflictLayer(&cube_layers[FRONT]);
	cube_layers[RIGHT].addConflictLayer(&cube_layers[BACK]);
	
	cube_layers[FRONT].addConflictLayer(&cube_layers[LEFT]);
	cube_layers[FRONT].addConflictLayer(&cube_layers[RIGHT]);
	cube_layers[FRONT].addConflictLayer(&cube_layers[UP]);
	cube_layers[FRONT].addConflictLayer(&cube_layers[BOTTOM]);

	cube_layers[BACK].addConflictLayer(&cube_layers[LEFT]);
	cube_layers[BACK].addConflictLayer(&cube_layers[RIGHT]);
	cube_layers[BACK].addConflictLayer(&cube_layers[UP]);
	cube_layers[BACK].addConflictLayer(&cube_layers[BOTTOM]);

}
void RubikCube::addCube(Cube *cube, int layer1, int layer2, int layer3){
	cube->AddToLayer((LAYER)layer1); 
	cube->AddToLayer((LAYER)layer2); 
	cube->AddToLayer((LAYER)layer3); 
	cubes.push_back(cube);
}

void RubikCube::addCube(Cube *cube, int layer1, int layer2){
	cube->AddToLayer((LAYER)layer1); 
	cube->AddToLayer((LAYER)layer2); 
	cubes.push_back(cube);
}

void RubikCube::addCube(Cube *cube, int layer1){
	cube->AddToLayer((LAYER)layer1); 
	cubes.push_back(cube);
}

void RubikCube::createCubes(){
	Cube *p_cube;
	Color *default_col = new Color(0.0f, 0.0f, 0.0f);
	
	// Partea de sus a cubului mare alcatuita 
	// din alte 9 cuburi individuale
	p_cube = new Cube(default_col, Vector3(-2.0f, 2.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(0));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(6));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(0));
	addCube(p_cube, UP, LEFT, FRONT);
	p_cube = new Cube(default_col, Vector3(-2.0f, 2.0f, 0.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(3));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(1));
	addCube(p_cube, UP, LEFT);
	p_cube = new Cube(default_col, Vector3(-2.0f, 2.0f, -2.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(0));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(0));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(2));
	addCube(p_cube, UP, LEFT, BACK);

	p_cube = new Cube(default_col, Vector3(0.0f, 2.0f, 2.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(7));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(1));
	addCube(p_cube, UP, FRONT);
	p_cube = new Cube(default_col, Vector3(0.0f, 2.0f, 0.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(4));
	addCube(p_cube, UP);
	p_cube = new Cube(default_col, Vector3(0.0f, 2.0f, -2.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(1));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(1));
	addCube(p_cube, UP, BACK);

	p_cube = new Cube(default_col, Vector3(2.0f, 2.0f, 2.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(8));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(2));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(0));
	addCube(p_cube, UP, RIGHT, FRONT);
	p_cube = new Cube(default_col, Vector3(2.0f, 2.0f, 0.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(5));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(1));
	addCube(p_cube, UP, RIGHT);
	p_cube = new Cube(default_col, Vector3(2.0f, 2.0f, -2.0f));
	p_cube->setFaceColor(TOP_FACE, faces_colors[TOP_FACE].getColorAt(2));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(2));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(2));
	addCube(p_cube, UP, RIGHT, BACK);
	
	// Partea de mijloc a cubului mare alcatuita 
	// din alte 9 cuburi individuale
	p_cube = new Cube(default_col, Vector3(-2.0f, 0.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(3));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(3));
	addCube(p_cube, LEFT, FRONT);
	p_cube = new Cube(default_col, Vector3(-2.0f, 0.0f, 0.0f));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(4));
	addCube(p_cube, LEFT);
	p_cube = new Cube(default_col, Vector3(-2.0f, 0.0f, -2.0f));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(5));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(3));
	addCube(p_cube, LEFT, BACK);

	p_cube = new Cube(default_col, Vector3(0.0f, 0.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(4));
	addCube(p_cube, FRONT);
	p_cube = new Cube(default_col, Vector3(0.0f, 0.0f, 0.0f));
	cubes.push_back(p_cube);
	p_cube = new Cube(default_col, Vector3(0.0f, 0.0f, -2.0f));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(4));
	addCube(p_cube, BACK);

	p_cube = new Cube(default_col, Vector3(2.0f, 0.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(5));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(3));
	addCube(p_cube, RIGHT, FRONT);
	p_cube = new Cube(default_col, Vector3(2.0f, 0.0f, 0.0f));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(4));
	addCube(p_cube, RIGHT);
	p_cube = new Cube(default_col, Vector3(2.0f, 0.0f, -2.0f));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(5));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(5));
	addCube(p_cube, RIGHT, BACK);
	
	// Partea de jos a cubului mare alcatuita 
	// din alte 9 cuburi individuale
	p_cube = new Cube(default_col, Vector3(-2.0f, -2.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(6));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(6));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(6));
	addCube(p_cube, BOTTOM, LEFT, FRONT);
	p_cube = new Cube(default_col, Vector3(-2.0f, -2.0f, 0.0f));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(7));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(3));
	addCube(p_cube, BOTTOM, LEFT);
	p_cube = new Cube(default_col, Vector3(-2.0f, -2.0f, -2.0f));
	p_cube->setFaceColor(LEFT_FACE, faces_colors[LEFT_FACE].getColorAt(8));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(6));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(0));
	addCube(p_cube, BOTTOM, LEFT, BACK);

	p_cube = new Cube(default_col, Vector3(0.0f, -2.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(7));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(7));
	addCube(p_cube, BOTTOM, FRONT);
	p_cube = new Cube(default_col, Vector3(0.0f, -2.0f, 0.0f));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(4));
	addCube(p_cube, BOTTOM);
	p_cube = new Cube(default_col, Vector3(0.0f, -2.0f, -2.0f));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(1));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(7));
	addCube(p_cube, BOTTOM, BACK);
	
	p_cube = new Cube(default_col, Vector3(2.0f, -2.0f, 2.0f));
	p_cube->setFaceColor(FRONT_FACE, faces_colors[FRONT_FACE].getColorAt(8));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(8));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(6));
	addCube(p_cube, BOTTOM, RIGHT, FRONT);
	p_cube = new Cube(default_col, Vector3(2.0f, -2.0f, 0.0f));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(7));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(5));
	addCube(p_cube, BOTTOM, RIGHT);
	p_cube = new Cube(default_col, Vector3(2.0f, -2.0f, -2.0f));
	p_cube->setFaceColor(RIGHT_FACE, faces_colors[RIGHT_FACE].getColorAt(8));
	p_cube->setFaceColor(BACK_FACE, faces_colors[BACK_FACE].getColorAt(8));
	p_cube->setFaceColor(BOTTOM_FACE, faces_colors[BOTTOM_FACE].getColorAt(2));
	addCube(p_cube, BOTTOM, RIGHT, BACK);
}


void RubikCube::drawCubes(){
	std::vector<Cube*>::iterator it1;
	std::vector<int>::iterator it2;
	std::vector<RubikLayer>::iterator it3;
	bool highlighted;
	

	for (it1=cubes.begin(); it1!=cubes.end(); ++it1){
		highlighted = false;

		glPushMatrix();
			// Pentru fiecare strat din care face parte cubul respectiv 
			// il vom roti relativ la pivot. Rotirea se va face numai
			// daca este cazul. Datorita conditiei de exclusivitate 
			// cubul se va roti doar in interiorul unui singur strat 
			// la un moment dat
			for(it2=(*it1)->layers.begin(); it2!=(*it1)->layers.end(); ++it2){
				cube_layers[*it2].rotateRelativeToPivot(0.02f);

				// Verificam daca nu cumva cubul se regaseste in layerul 
				// activ la moment dat. Asta inseamna ca face parte dintr-un
				// layer selectat pentru a fi mutat.
				if (*it2 == active_layer){
					highlighted = true;
				}
				
			}
			(*it1)->DrawCube(highlighted);
		glPopMatrix();
	}

	// Dupa ce s-au efectuat toate rotatiile verificam daca nu cumva 
	// s-a incheiat una si este cazul sa schimbam culorile fetelor
	for(it3=cube_layers.begin(); it3!=cube_layers.end(); it3++){
		if (it3->getChanges() < 0){
			faces_colors[it3-cube_layers.begin()].rotateClockwise();
			break;
		}
		else if(it3->getChanges() > 0){
			faces_colors[it3-cube_layers.begin()].rotateCounterClockwise();
			break;
		}
	}
	
	// Aici eliminam din stiva in care tinem mutarile 
	// o anumita mutare in cazul in care s-a finalizat
	if (!moves.empty() && !save_moves){ 
		LAYER layer = moves.top().first;
		SPIN direction = moves.top().second;
		if (cube_layers[layer].getChanges() != 0){
			moves.pop();
		}
	}
	

	// Stergem o schimbare pentru a nu se schimba culorile si
	// frameul viitor
	for(it3=cube_layers.begin(); it3!=cube_layers.end(); it3++){
		it3->removeOneChange();
	}

}

void RubikCube::initSelectionOrder(){
	selection_order.push(UP); 
	selection_order.push(BOTTOM);
	selection_order.push(LEFT); 
	selection_order.push(RIGHT);
	selection_order.push(FRONT); 
	selection_order.push(BACK);
}

void RubikCube::spinLayer(LAYER layer, SPIN direction){
	if (layer>=0 && layer<=8){
		cube_layers[layer].startSpinning(direction);
		if (save_moves){
			moves.push(std::pair<LAYER, SPIN>(layer, direction));
		}
	}
}

void RubikCube::spinActiveLayer(SPIN direction){
	spinLayer((LAYER)active_layer, direction);
	if (started){
		no_moves++;
	}
}


/* Selecteaza urmatorul layer din axa/dimensiunea activa. Practic
 * functia va fi apelata la apasarea unei taste (aceasi tasta). 
 * De fiecare data se face trecerea la urmatorul layer, 
 * insa numai de pe aceasi axa. Nu se doreste trecerea de la 
 * de la un layer la altul trecand prin toate indiferent de 
 * dimensiune */ 
void RubikCube::selectNextLayer(){
	active_layer = selection_order.front();
	selection_order.pop(); 
	selection_order.push(active_layer);
}

void RubikCube::startGame(){
	started = true;
};

void RubikCube::printText(float x, float y, char *text, Color color){
	if (!text || !strlen(text)) return;
	glColor3f(color.red, color.green, color.blue);
	glRasterPos2f(x,y);
	while(*text){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
		text++;
	}

}

void RubikCube::drawText(){
	char *text = new char[20];
	sprintf_s(text, 20, "Score: %d", no_moves);
	glPushMatrix();
		printText(-2.5, 5.0, text, Color(1.0f, 1.0f, 1.0f));
	glPopMatrix();
	delete[] text;
}

void RubikCube::solveGame(){
	save_moves = false;
	active_layer = INACTIVE; 
	if (!moves.empty()){
		LAYER layer = moves.top().first;
		SPIN direction = moves.top().second;
		// Trebuie schimbata in sens invers directia
		if (direction==NEGATIVE)
			direction = POSITIVE; 
		else 
			direction = NEGATIVE;
		spinLayer(layer, direction);
	}

}