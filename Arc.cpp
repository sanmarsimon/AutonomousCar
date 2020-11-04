#include "Arc.h"

Arc::Arc()
{
    origine_ = nullptr;
    arrivee_ = nullptr;
    distance_ = 0;
}

Arc::~Arc()
{
    delete origine_;
    origine_ = nullptr;
    delete arrivee_; 
    arrivee_ = nullptr;
}

Arc::Arc(Sommet* origine, Sommet* arrivee, int distance):
    origine_(origine),
    arrivee_(arrivee),
    distance_(distance)
{
}

int Arc::getDistance()
{
    return distance_;
}

Sommet* Arc::getOrigine()
{
    return origine_;
}

Sommet* Arc::getArrivee()
{
    return arrivee_;
}
