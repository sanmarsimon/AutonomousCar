#include "Sommet.h"

Sommet::Sommet()
{
    id_ = "null";
    type_ = "null";
    visited_ = false;
}

Sommet::~Sommet()
{
    for (auto& sortant : sortants_) {
        delete sortant;
        sortant = nullptr;
    }
    sortants_.clear();
}

Sommet::Sommet(std::string id, std::string type):
    id_(id),
    type_(type)
{
    visited_ = false;
}

void Sommet::addEntrant(Sommet* entrant)
{
    entrants_.push_back(entrant);
}

void Sommet::addSortant(Sommet* sortant)
{
    sortants_.push_back(sortant);
}

void Sommet::setVisit(bool valeur)
{
    visited_ = valeur;
}

std::string Sommet::getID()
{
    return id_;
}

std::string Sommet::getType()
{
    return type_;
}

std::vector<Sommet*> Sommet::getSortants()
{
    return sortants_;
}

std::vector<Sommet*> Sommet::getEntrants()
{
    return entrants_;
}

bool Sommet::isVisite()
{
    return visited_;
}
