
#ifndef SOMMET_H
#define SOMMET_H

#include <string>
#include <vector>

class Sommet {
public:

	Sommet();
	~Sommet();
	Sommet(std::string id, std::string type);

	void addEntrant(Sommet* entrant);
	void addSortant(Sommet* sortant);
	void setVisit(bool valeur);

	std::string getID();
	std::string getType();
	std::vector<Sommet*> getSortants();
	std::vector<Sommet*> getEntrants();

	bool isVisite();

private:

	std::string id_;
	std::string type_;
	std::vector<Sommet*> sortants_;
	std::vector<Sommet*> entrants_;
	bool visited_;

};
#endif 
