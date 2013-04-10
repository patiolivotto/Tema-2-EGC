#include "RubikLayer.h" 
#include "dependinte/freeglut.h"
#include <iostream>

// Constructori
RubikLayer::RubikLayer(Vector3 pivot, Vector3 axis) : 
	pivot(pivot.x, pivot.y, pivot.z), 
	rotation_axis(axis.x, axis.y, axis.z), 
	spin(NONE), 
	rotation(0.0f), 
	changes(0) {
}

// Destructor
RubikLayer::~RubikLayer(){
}

bool RubikLayer::isSpinning(){
	return (spin!=NONE)?true:false;
}

void RubikLayer::startSpinning(SPIN direction){
	std::vector<RubikLayer*>::iterator it;
	// Verificam ca nu cumva un strat care are cuburi 
	// comune cu stratul curent nu se invarte deja. Daca 
	// se invarte nu mai incepem nici o rotire.
	for(it=layers.begin(); it!=layers.end(); it++){
		if ((*it)->isSpinning())
			return;
	}
	if (spin == NONE){
		// Se efectueaza o noua rotire a stratului doar 
		// daca nu exista alta in desfasurare
		spin = direction;
	}
}

// Metoda va fi apelata la fiecare frame de fiecare 
// cub in parte pentru fiecare layer din care face parte. 
// Ea va face o rotire doar in cazul in care este nevoie 
// de una.
void RubikLayer::rotateRelativeToPivot(float dt){
	float rotation_step = spin*dt;
	if (isSpinning()){
		// Trebuie sa actualizam unghiul de rotatie
		rotation += rotation_step;
		// Daca s-a ajuns limita oprim rotatia 
		if ((spin==NEGATIVE&&rotation<=-90.0f) || (spin==POSITIVE&&rotation>=90.0f)){
			// Activam posibilitatea de a interschimba layerele
			if (spin==NEGATIVE)
				changes--;
			else 
				changes++;
			spin = NONE;
			rotation = 0;
		}

		// Facem rotatia relativa la pivot
		glTranslatef(-pivot.x, -pivot.y, -pivot.z);
		glRotatef(rotation, rotation_axis.x, rotation_axis.y, rotation_axis.z); 
		glTranslatef(pivot.x, pivot.y, pivot.z);
	}

}

void RubikLayer::addConflictLayer(RubikLayer *layer){
	layers.push_back(layer);
}

/* Functia trebuie apelata implicit la fiecare frame 
 * pentru a dezactiva interschimbarea layerelor 
 * incontinuu. Ele se vor interschimba doar cand se 
 * va completa o rotatie. */ 
void RubikLayer::removeOneChange(){
	if (changes!=0){
		(changes<0)?changes++:changes--;
	}
}

Vector3 RubikLayer::getAxis(){ 
	return rotation_axis; }

int RubikLayer::getChanges(){
	return changes;
}