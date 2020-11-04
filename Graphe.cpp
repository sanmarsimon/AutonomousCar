#include "Graphe.h"
constexpr auto INFINI = 1000000;

Graphe::Graphe()
{
}

Graphe::~Graphe()
{
	for (size_t i = 0; i < stations_.size(); i++) {
		delete stations_[i];
		stations_[i] = nullptr;
	}
	stations_.clear();

	for (size_t i = 0; i < stations_.size(); i++) {
		delete chemins_[i];
		chemins_[i] = nullptr;
	}
	chemins_.clear();
}

Graphe* Graphe::creerGraphe(string nomFichier)
{
	string id;
	string type;

	string origine;
	string arrivee;
	string distance;

	ifstream fichier(nomFichier);
	if (fichier.fail())
		cout << "Problème lors de l'ouverture du fichier" << '\n' << endl;
	else {
		while (fichier.peek() != EOF && fichier.peek() != '\n')
		{
			getline(fichier, id, ',');
			getline(fichier, type, ';');
			Sommet* nouvSommet = new Sommet(id, type);
			stations_.push_back(nouvSommet);
		}
		fichier.get();
		while (fichier.peek() != EOF && fichier.peek() != '\n')
		{
			getline(fichier, origine, ',');
			getline(fichier, arrivee, ',');
			getline(fichier, distance, ';');
			Arc* nouvArc = new Arc(trouverSommet(origine), trouverSommet(arrivee), stoi(distance));
			chemins_.push_back(nouvArc);
		}
	}
	associerSommets();
	return this;
}

void Graphe::lireGraphe()
{
	for (auto& station : stations_) {
		vector<string> voisins = trouverIDVoisins(station);
		cout << "(" << station->getID() << ", " << station->getType();
		if (voisins.size() != 0) {
			cout << ", (" << voisins[0];
			for (size_t i = 1; i < voisins.size(); i++)
				cout << ", " << voisins[i];
			cout << ")";
		}
		cout << ")" << '\n' << endl;
	}
}

vector<Sommet*> Graphe::extractionGraphe(string idSommet, Voiture* voiture)
{
	int distanceMax = 0;
	int distanceParcourue = 0;
	voiture->setAutoRestance(voiture->getAutoMax());

	bool fin = false;
	Sommet* origine = trouverSommet(idSommet);
	vector<Sommet*> chemin = { origine };
	vector<Sommet*> cheminMax = { origine };
	origine->setVisit(true);

	if (origine->getSortants().size() != 0) {
		for (auto& voisin : origine->getSortants()) {
			if (!voisin->isVisite()) {
				rechercherChemin(origine, voisin, voiture, &chemin, &fin);
			}
			distanceParcourue = calculerDistanceChemin(chemin);
			if (distanceMax <= distanceParcourue) {
				distanceMax = distanceParcourue;
				cheminMax = chemin;
			}
			chemin.clear();
			resetVisites();
			fin = false;
			chemin = { origine };
			origine->setVisit(true);
		}
	}
	resetVisites();
	voiture->setAutoRestance(voiture->getAutoMax());
	return cheminMax;
}

vector<Sommet*> Graphe::plusCourtChemin(string idOrigine, string idDestination, Voiture* voiture)
{
	Sommet* origine = trouverSommet(idOrigine);
	Sommet* destination = trouverSommet(idDestination);

	//Initialisation des distances pour chaque sommet
	map <Sommet*, int> distanceSommet;
	for (auto& station : stations_){
		if (station == origine) {
			distanceSommet.insert(pair<Sommet*, int>(station, 0));
		}
		else
			distanceSommet.insert(pair<Sommet*, int>(station, INFINI));
	}
	//Initalisation des sommets traversés pour chaque sommet
	map <Sommet*, vector<Sommet*>> sommetsPrecedents;
	for (auto& station : stations_) {
		if (station == origine) {
			sommetsPrecedents.insert(pair<Sommet*, vector<Sommet*>>(station, vector<Sommet*>()));
			sommetsPrecedents[station].push_back(station);
		}
		else
			sommetsPrecedents.insert(pair<Sommet*, vector<Sommet*>>(station, vector<Sommet*>()));
	}
	//Initialisation de la file des sommets restants
	map <Sommet*, int> remaining = distanceSommet;
	
	//Initialisation des variables de la boucle
	Sommet* n = origine;
	faireLePlein(n, voiture);

	//Parcours de remaining
	while (!remaining.empty() &&  n != destination && voiture->getAutoRestante() > 0) {
		int distanceMin = INFINI;
		faireLePlein(n, voiture);
		//Sélection de n
		for (auto& node : remaining) {
			if (distanceSommet[node.first] < distanceMin) {
				n = node.first;
				distanceMin = distanceSommet[node.first];
			}
		}
		//Pour chaque voisin, mettre à jour distanceSommet et sommetsPrecedents si possible
		if (n->getSortants().size() != 0) {
			for (auto& adjacent : n->getSortants()) {
				if (distanceSommet[n] + calculerDistance(n, adjacent) < distanceSommet[adjacent]) {
					distanceSommet[adjacent] = distanceSommet[n] + calculerDistance(n, adjacent);
					sommetsPrecedents[adjacent] = sommetsPrecedents[n];
					sommetsPrecedents[adjacent].push_back(adjacent);
				}
			}
		}
		else
			return {origine};

		//Conduire et faire le plein si possible
		voiture->conduireVoiture(distanceSommet[n]);

		//Enlever n de remaining
		remaining.erase(n);
	}

	if (sommetsPrecedents[destination].size() != 0)
		return sommetsPrecedents[destination]; //Retourne le chemin qui permet d'atteindre la destination
	else
		return { origine };	//Retourne l'orginie, ce qui correspond à un échec de l'opération
}

void Graphe::lireChemin(vector<Sommet*> chemin)
{
	cout << chemin[0]->getID();
	if (chemin.size() > 1) {
		for (int i = 1; i < chemin.size(); i++)
			cout << " -> " << chemin[i]->getID();
	}
	cout << '\n' << endl;
}

Sommet* Graphe::trouverSommet(string idSommet)
{
	for (auto& station : stations_) {
		if (station->getID() == idSommet)
			return station;
	}
	return nullptr;
}

void Graphe::associerSommets()
{
	for (auto& station : stations_) {
		for (auto& chemin : chemins_) {
			if (chemin->getOrigine() == station)
				station->addSortant(chemin->getArrivee());
			else if (chemin->getArrivee() == station)
				station->addEntrant(chemin->getOrigine());
		}
	}
}

vector<string> Graphe::trouverIDVoisins(Sommet* sommet)
{
	vector<string> voisins;
	for (auto& entrant : sommet->getEntrants())
		voisins.push_back(entrant->getID());
	for (auto& sortant : sommet->getSortants())
		voisins.push_back(sortant->getID());
	return voisins;
}

void Graphe::rechercherChemin(Sommet* origine, Sommet* arrivee, Voiture* voiture, vector<Sommet*>* chemin, bool* fin)
{
	if (voiture->getAutoRestante() < 0 || *fin) {
		return;
	}
	
	voiture->conduireVoiture(calculerDistance(origine, arrivee));
	chemin->push_back(arrivee);
	arrivee->setVisit(true);

	if (arrivee->getSortants().size() == 0) {
		*fin = true;
	}
	else {
		for (auto& voisin : arrivee->getSortants()) {
			if (!voisin->isVisite()) {
				rechercherChemin(arrivee, voisin, voiture, chemin, fin);
			}
		}
	}

}

int Graphe::calculerDistance(Sommet* origine, Sommet* arrivee)
{
	for (auto& chemin : chemins_)
		if (chemin->getOrigine() == origine && chemin->getArrivee() == arrivee)
			return chemin->getDistance();
	return 0;
}

int Graphe::calculerDistanceChemin(vector<Sommet*> chemin)
{
	int distanceTot = 0;
	for (int i = 0; i < chemin.size() - 1; i++)
		distanceTot += calculerDistance(chemin[i], chemin[i + 1]);
	return distanceTot;
}

void Graphe::resetVisites()
{
	for (auto& station : stations_)
		station->setVisit(false);
}

void Graphe::faireLePlein(Sommet* sommet, Voiture* voiture)
{
	string typeVoiture = voiture->getType();
	string typeSommet = sommet->getType();

	if (typeSommet == "hybrid" || typeSommet == typeVoiture || typeVoiture == "hybdrid") {
		voiture->setAutoRestance(voiture->getAutoMax());
	}

}







