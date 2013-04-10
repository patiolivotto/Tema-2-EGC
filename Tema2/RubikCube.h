#pragma once 
#include <vector>
#include <queue> 
#include <stack>
#include "Vector3.h"
#include "Cube.h"
#include "RubikLayer.h"
#include "Color.h" 

class RubikCube{
	public: 
		RubikCube(); 
		virtual ~RubikCube();
		void createLayers();
		void createCubes();
		void drawCubes();
		void selectNextLayer();
		void spinActiveLayer(SPIN direction);
		void startGame();
		void solveGame();
		void drawText();
	private:
		void initSelectionOrder();
		void initFacesNeighbours();
		void spinLayer(LAYER layer, SPIN direction);
		void addCube(Cube* cube, int layer1, int layer2, int layer3);
		void addCube(Cube* cube, int layer1, int layer2);
		void addCube(Cube* cube, int layer1);
		void printText(float x, float y, char *text, Color color);
		// Retine toate cuburile 
		std::vector<Cube*> cubes;
		// Un vector cu layerele propriu-zise
		std::vector<RubikLayer> cube_layers;
		std::vector<ColorMatrix> faces_colors;
		int active_layer;
		std::queue<int> selection_order;
		int no_moves;
		// Retine daca jocul a inceput sau este inca in stagiul de amestecare
		bool started;
		// Daca e true va salva mutarile intr-o stiva
		bool save_moves; 
		// Stiva in care se salveaza mutarile
		std::stack<std::pair<LAYER, SPIN>> moves;
};