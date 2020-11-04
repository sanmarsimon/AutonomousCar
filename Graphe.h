
#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <map>

#include "Sommet.h"
#include "Arc.h"
#include "Voiture.h"

using namespace std;

class Graphe {
public: 
	Graphe();
	~Graphe();

	Graphe* creerGraphe(string nomFichier);
	void lireGraphe();
	vector<Sommet*> extractionGraphe(string idSommet, Voiture* voiture);
	vector<Sommet*> plusCourtChemin(string idOrigine, string idDestination, Voiture* voiture);

	void lireChemin(vector<Sommet*> chemin);
	Sommet* trouverSommet(string idSommet);
	void associerSommets();
	vector<string> trouverIDVoisins(Sommet* sommet);
	void rechercherChemin(Sommet* origine, Sommet* arrivee, Voiture* voiture, vector<Sommet*>* chemin, bool* fin);
	int calculerDistance(Sommet* origine, Sommet* arrivee);
	int calculerDistanceChemin(vector<Sommet*> chemin);
	void resetVisites();
	void faireLePlein(Sommet* sommet, Voiture* voiture);

private:
	vector<Sommet*> stations_;
	vector<Arc*> chemins_;
};

#endif 
