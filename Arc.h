
#ifndef ARC_H
#define ARC_H

#include <string>
#include "Sommet.h"

class Arc {
public:

	Arc();
	~Arc();

	Arc(Sommet* origine, Sommet* arrivee, int distance);

	int getDistance();
	Sommet* getOrigine();
	Sommet* getArrivee();

private:

	Sommet* origine_;
	Sommet* arrivee_;
	int distance_;

};
#endif

