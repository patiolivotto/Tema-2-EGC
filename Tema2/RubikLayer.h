#pragma once
#include "Vector3.h"
#include <vector>
#include "Cube.h"
enum SPIN {NEGATIVE = -1, NONE = 0, POSITIVE = 1};

// Clasa contine detalii despre cuburile care fac 
// parte din acelasi strat care la o apasare a tastei 
// se misca toate deodata 
class RubikLayer{
	public:
		RubikLayer(Vector3 pivot, Vector3 rotation_axis);
		virtual ~RubikLayer();
		void startSpinning(SPIN direction);
		bool isSpinning();
		void addConflictLayer(RubikLayer *layer);
		void rotateRelativeToPivot(float dt);
		void removeOneChange();
		void swapLayer(int &layer);
		Vector3 getAxis();
		int getChanges();
	private:
		Vector3 pivot, rotation_axis;
		// spin zice daca layerul se invarte si daca da 
		// zice si in ce sens se invarte acesta: in sens pozitiv
		// sau in sens negativ
		SPIN spin;
		float rotation;
		std::vector<RubikLayer*> layers;
		// retine nr de interschimbari de layere care trebuie facut
		// daca e negativ trebuie facute in sens trigonometric, 
		// daca e pozitiv trebuie facut in sens invers trigonometric
		int changes;
};